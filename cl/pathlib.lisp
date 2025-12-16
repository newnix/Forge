;;;; Create a Portable Pathname Library as described in:
;;;; https://gigamonkeys.com/book/practical-a-portable-pathname-library

(defun component-present-p (value)
  (and value (not (eql value :unspecific))))

(defun directory-pathname-p (p)
  (and
   (not (component-present-p (pathname-name p)))
   (not (component-present-p (pathname-type p)))
   p))

(defun pathname-as-directory (name)
  "Given a path, ensure a directory path object is generated for use in other functions"
  (let ((pathname (pathname name)))
    (when (wild-pathname-p pathname)
      (error "Can't reliably convert wild pathnames."))
    (if (not (directory-pathname-p name))
	(make-pathname
	 :directory (append (or (pathname-directory pathname) (list :relative))
			    (list (file-namestring pathname)))
	 :name nil
	 :type nil
	 :defaults pathname)
	pathname)))

;;; Use reader conditional expressions to handle differences in implementations for CLISP
;;; since CLISP apparently won't list extension-less files with :type :wild, but requires :type nil
(defun directory-wildcard (dirname)
  "Generates a wildcard directory object given a directory path"
  (make-pathname
   :name :wild
   :type #-clisp :wild #+clisp nil
   :defaults (pathname-as-directory dirname)))

;;; Initial implementation of a directory listing function
(defun list-directory-proto (dirname)
  "Initial implementation of a directory listing function"
  (when (wild-pathname-p dirname)
    (error "Can only list concrete directory names."))
  (directory (directory-wildcard dirname)))

;;; More complete implementation of a directory listing function
(defun list-directory (dirname)
  (when (wild-pathname-p dirname)
    (error "Can only list concrete directory names."))
  (let ((wildcard (directory-wildcard dirname)))

    #+(or sbcl cmu lispworks)
    (directory wildcard)

    #+openmcl
    (directory wildcard :directories t)

    #+allegro
    (directory wildcard :directories-are-files nil)

    #+clisp
    (nconc
     (directory wildcard)
     (directory (clisp-subdirectories-wildcard wildcard)))

    #-(or sbcl cmu lispworks openmcl allegro clisp)
    (error "list-directory not implemented")))

;;; Implement `clisp-subdirectories-wildcard' specifically for CLISP implementations
#+clisp
(defun clisp-subdirectories-wildcard (wildcard)
  "Handle subdirectory wildcard creation for CLISP implementations"
  (make-pathname
   :directory (append (pathname-directory wildcard) (list :wild))
   :name nil
   :type nil
   :defaults wildcard))

;;; Create a function to test whether or not a file exists, returning the appropriate form of the pathname
;;; (directory/file) depending on whether the target path names a file or directory, NIL if it doesn't exist
(defun file-exists-p (pathname)
  "Determine if a given path exists, returning NIL if not, else return the pathname object in the matching file/directory form"
  #+(or sbcl lispworks openmcl) ; These implementations of probe-file do what we want already
  (probe-file pathname)

  #+(or allegro cmu)
  (or (probe-file (pathname-as-directory pathname))
      (probe-file pathname))

  #+clisp
  (or (ignore-errors
       (probe-file (pathname-as-file pathname)))
      (ignore-errors
       (let ((directory-form (pathname-as-directory pathname)))
	 (when (ext:probe-directory directory-form)
	   directory-form))))

  #-(or sbcl cmu lispworks openmcl allegro clisp)
  (error "file-exists-p not implemented"))

;;; This function is mostly useful for CLISP so far, but should be useful to ensure proper pathname forms are passed to functions
(defun pathname-as-file (name)
  "Convert a pathname object to file form, if needed"
  (let ((pathname (pathname name)))
    (when (wild-pathname-p pathname)
      (error "Can't reliably convert wild pathnames.")) ; May be something we can implement later
    (if (directory-pathname-p name)
	(let* ((directory (pathname-directory pathname))
	       (name-and-type (pathname (first (last directory)))))
	  (make-pathname
	   :directory (butlast directory)
	   :name (pathname-name name-and-type)
	   :type (pathname-type name-and-type)
	   :defaults pathname))
	pathname)))

;;; Create a directory walking function, this mostly relies on the functionality we've implemented above,
;;; but accepts some keyword arguments, :directories to call the callback on pathnames of directories as well as regular files,
;;; :test to provide a custom test function that determines if the callback is run on a given dirent (pathname object)
;;; This function will recurse into subdirectories as well
(defun walk-directory (dirname cb &key directories (test (constantly t)))
  "Recursively walk a directory, calling `cb' on each file encountered, including directories if :directories t is passed
   Accepts a custom test to determine if a pathname should be printed with the :test keyword"
  (labels
      ((walk (name)
	 (cond
	   ((directory-pathname-p name)
	    (when (and directories (funcall test name))
	      (funcall cb name))
	    (dolist (x (list-directory name)) (walk x)))
	   ((funcall test name) (funcall cb name)))))
    (walk (pathname-as-directory dirname))))

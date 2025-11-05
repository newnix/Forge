;; Mostly just working through the first 3 chapters of https://gigamonkeys.com/book
(defun hello-world () (format t "hello, world"))
(defun make-cd (title artist rating ripped)
  (list :title title :artist artist :rating rating :ripped ripped))
;; Not ideal, utilizes a global, but fine for now
(defun add-record (cd)
  (push cd *db*))
(defun make-global-db ()
  (defvar *db* nil))
(defun dump-db ()
  (dolist (cd *db*)
    (format t "~{~a:~10t~a~%~}~%" cd)))

;; Create an input prompt
(defun prompt-read (prompt)
  (format *query-io* "~a: " prompt)
  (force-output *query-io*)
  (read-line *query-io*))

;; Use the prompting function and the make-cd function to create interactive additions
(defun prompt-for-cd ()
  (make-cd
   (prompt-read "Title")
   (prompt-read "Artist")
   (or (parse-integer (prompt-read "Rating") :junk-allowed t) 0)
   (y-or-n-p "Ripped? [y/n]")))

;; Create an interactive input loop
(defun add-cds ()
  (loop
    (add-record (prompt-for-cd))
    (if
     (not
      (y-or-n-p "Another? [y/n]: "))
     (return))))

;; Create a function to save the "database" to a file, uses whatever serialized
;; format SBCL (or CL) uses for this listf structure, also utilizes the global var
(defun save-db (filename)
  (with-open-file (out filename
		       :direction :output
		       :if-exists :supersede)
    (with-standard-io-syntax
      (print *db* out))))

;; Load the "database" from a file
(defun load-db (filename)
  (with-open-file (in filename)
    (with-standard-io-syntax
      (setf *db* (read in)))))

;; Query for entries by a specific artist
(defun select-by-artist (artist)
  (remove-if-not
   #'(lambda (cd) (equal (getf cd :artist) artist))
   *db*))

;; Create a generic selection function that dispatches to a named selector
(defun select
    (selector-fn)
  (remove-if-not selector-fn *db*))

;; Rewrite the artist selector function into one that works with the generic select
(defun artist-selector (artist)
  #'(lambda (cd) (equal (getf cd :artist) artist)))

;; Create a title selector
(defun title-selector (title)
  #'(lambda (cd) (equal (getf cd :title) title)))

;; Create a 'where' selector function, containing the functionality of *-selector
(defun where (&key title artist rating (ripped nil ripped-p))
  #'(lambda (cd)
      (and
       (if title (equal (getf cd :title) title) t)
       (if artist (equal (getf cd :artist) artist) t)
       (if rating (equal (getf cd :rating) rating) t)
       (if ripped-p (equal (getf cd :ripped) ripped) t))))

;; Create an update function for the database
(defun update
    (selector-fn &key title artist rating (ripped nil ripped-p))
  ;; Still using globals, but should be possible to create a closure to act as
  ;; a "connection object" with concepts discussed later in the book
  (setf *db*
	(mapcar
	 #'(lambda (row)
	     (when (funcall selector-fn row)
	       (if title (setf (getf row :title) title))
	       (if artist (setf (getf row :artist) artist))
	       (if rating (setf (getf row :rating) rating))
	       (if ripped-p (setf (getf row :ripped) ripped)))
	     row) *db*)))

;; Create a deletion function for the "database"
(defun delete-rows (selector-fn)
  (setf *db* (remove-if selector-fn *db*)))

;; This macro rewrites the following expression backwards, such that
;; (backwards ("hello, world" t format)) => hello, world\nNIL
(defmacro backwards (expr) (reverse expr))

;; Create a comparison generator function, uses quasi-quoting to prevent symbol interpretation, then unquoting to resume interpretation
(defun make-comparison-expr (field value)
  `(equal (getf cd ,field) ,value))

;; Uses the loop macro to loop over possible fields to produce comparators on
(defun make-comparisons-list (fields)
  (loop while fields
	collecting (make-comparison-expr (pop fields) (pop fields))))

(defmacro where (&rest clauses) body...)
  `#'(lambda (cd) (and ,@(make-comparisons-list clauses))))

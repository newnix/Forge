;;;; Chapter 9 of https://gigamonkeys.com/book, should result in a usable unit testing utility

;;; Simple helper to report if a test passed
(defun report-result (result form)
  (format t "~:[FAIL~;pass~] ... ~a: ~a~%" result *test-name* form)
  result)

;;; Rewritten explicitly because we haven't gone over packaging yet
(defmacro with-gensyms ((&rest names) &body body)
  "Enable more hygenic macros by gensym-ing names"
  `(let ,(loop for n in names collect `(,n (gensym)))
     ,@body))

;; This solution wasn't immediately obvious, lisp macros are still somewhat confusing at least with regard to quoting/unquoting
;; previously this was something like:
;; (defmacro run-test (form)
;;   (with-gensyms (result test-form)
;;     `(let (,result ,form) (,test-form (quote ,form))
;;        (report-result ,result ,test-form))))
;; The simple solution makes sense, but I'll need more experience to not over-complicate macros
(defmacro run-test (form)
  `(report-result ,form ',form))


;;; Simple macro to determine if a list of results contains any nil values
(defmacro combine-results (&body forms)
  (with-gensyms (result)
    `(let ((,result t))
       ,@(loop for f in forms collect `(unless ,f (setf ,result nil)))
       ,result)))

;;; Creating a macro that accepts an arbitrary number of tests to evaluate and track whether or not any failed
(defmacro check (&body forms)
  `(combine-results
     ,@(loop for f in forms collect `(report-result ,f ',f))))

;;; Create a macro to wrap `defun` when creating test functions
(defmacro deftest (name params &body body)
  `(defun ,name ,params
     (let ((*test-name* (append *test-name* (list ',name))))
       ,@body)))

;;;; May want to expand on this further in the future, but it seems like a good unit testing foundation

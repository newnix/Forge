;;;; New file to experiment with concepts described in chapter 5+ of
;;;; https://gigamonkeys.com/book

;;; This function requires a callback to provide values rendered as a histogram to STDOUT
;;; A neat consequence of lisp with functions following this form is that we could call it
;;; like so: (apply #'plot #'exp '(min max step))
(defun plot (fn min max step)
  "Loop from min to max incrementing by step to call fn for values to chart"
  (loop for i from min to max by step do ; Evil macro magic, I assume, but it's more similar to natural language than C loops
    (loop repeat (funcall fn i) do (format t "*"))
    (format t "~%")))


;;; Example of how funcall can accept lambda literals
;; (funcall #'(lambda (x y) (+ x y)) 2 3) => 5
;;; More concisely:
;; ((lambda (x y) (+ x y)) 2 3) => 5

;;; This is a demonstration of variable shadowing with let forms
(defun var-shadow-example (x)
  "Provide an initial value and see how the same name can refer to different values based on scope"
  (format t "Parameter: ~a~%" x)
  (let ((x 2))
    (format t "Outer LET: ~a~%" x)
    (let ((x 30))
      (format t "Inner LET: ~a~%" x))
    (format t "Outer LET (again): ~a~%" x))
  (format t "Parameter (again): ~a~%" x))

;;; Helper functions for creating a macro 'do-primes'
;; Brute force testing for whether or not a number is prime
(defun primep (num)
  "Brute force check for whether or not a given integer is prime"
  (when (> num 1)
    (loop for fac from 2 to (isqrt num) never (zerop (mod num fac)))))

;; Compute the next prime number after the given value
(defun next-prime (num)
  "Brute force computation of the next prime number after `num`"
  (loop for n from num when (primep n) return n))

;;; Define the `do-primes` macro, should generally expand to an expression like the following:
;;; (do ((p (next-prime 0) (next-prime (incf p))))
;;;     ((> p 19))
;;;   (format t "~d " p))
;;; when given the following macro call:
;;; (do-primes (p 0 19)
;;;   (format t "~d " p))
;;; NOTE: This form uses destructured arguments to help enforce the correct parameter count,
;;; this also allows an LSP/IDE system to provide a more useful signature
;;; NOTE: This version also leaks implementation details, as it evaluates `end` more than once
(defmacro do-primes-leaky ((var start end) &rest body)
  "Loop over (var start end), only executing the body on prime values"
  `(do ((,var (next-prime ,start) (next-prime (incf ,var))))
       ((> ,var ,end))
     ,@body)))

;;; This is a version of do-primes that only evaluates `end` once
(defmacro do-primes ((var start end) &body body)
"Loop over (vart start end), only executing the body on prime values"
`(do ((ending-value ,end) ; bind the result of evaluating `end` to `ending-value`
      (,var (next-prime ,start) (next-prime (incf ,var))))
     ((> ,var ending-value))
   ,@body))



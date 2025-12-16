;;;; New file to experiment with concepts described in chapter 5+ of
;;;; https://gigamonkeys.com/book

;;; Create a function that takes a quoted form and an optional explanation to display them
;;; First with the description, then the form to be evaluated, then the result of the evaluation
;;; NOTE: This can probably be made more elegant, but allows for better interactive notes/references
(defun explain-and-run (&key form (description nil desc-p))
  "Given a quoted form, :form and optional description, print the description, the form, and the result"
  (if desc-p
      (format t "~&~a~%" description))
  (format t "~&~s => ~a~%" form (eval form)))

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
(explain-and-run :form '(funcall #'(lambda (x y) (+ x y)) 2 3)
		 :description "Example of how the `funcall' function can take lambda literals")

;;; More concisely:
;; ((lambda (x y) (+ x y)) 2 3) => 5
(explain-and-run :form '((lambda (x y) (+ x y)) 2 3)
		 :description "A more concise example of invoking a lambda literal")

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

(explain-and-run :form '(var-shadow-example 23)
		 :description "Demonstrate variable shadowing in functions using `var-shadow-example'")

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

;;; This is a version of do-primes that only evaluates `end` once, however,
;;; it's not hygenic (needs use of gensym) and evaluates the arguments out of the expected order
(defmacro do-primes-leaky2 ((var start end) &body body)
"Loop over (vart start end), only executing the body on prime values"
`(do ((ending-value ,end) ; bind the result of evaluating `end` to `ending-value`
      (,var (next-prime ,start) (next-prime (incf ,var))))
     ((> ,var ending-value))
   ,@body))

;;; Attempt to make a hygenic `do-primes` macro
(defmacro do-primes ((var start end) &body body)
  (let ((ending (gensym)))
    `(do ((,var (next-prime ,start) (next-prime (incf ,var)))
       	  (,ending ,end))
         ((> ,var ,ending))
       ,@body)))

;;; Create a macro to help write hygenic macros
(defmacro with-gensyms ((&rest names) &body body)
  `(let ,(loop for n in names collect `(,n (gensym)))
     ,@body))

;; Create a version of `do-primes` that uses `with-gensyms`
;; NOTE: Might just be a SLIME limitation, but the formatting seems to be extremely important,
;; leading to compilation errors being reported until whitespace is modified
(defmacro do-prime-gensym ((var start end) &body body)
  (with-gensyms (ending)
    `(do ((,var (next-prime ,start) (next-prime (incf ,var)))
        (,ending ,end))
       ((> ,var ,ending))
     ,@body)))

;;; Create a function to retrieve and present the value of a given key in a given hash table
(defun show-val (key table)
"Probe `table` for `key`, displaying the value if present, or else a NOT-FOUND message"
  (multiple-value-bind (val exists) (gethash key table)
    (if exists
        (format nil "~a: ~a" key val)
	; For this to display the name of the requested hash table rather than the value of the binding,
	; I'll have to look into a macro to capture the bound name. Possibly worth grabbing the address
	; like when writing debug logs in C as well, but the way to do that with CL isn't yet obvious
        (format nil "~a: NOT IN ~a" key table))))

;;; Example of a function that uses "destructive" functions to efficiently rewrite an internally generated list
(defun up-to (max)
"Create a list containing all values up to the max value minus 1, uses a recycling idiom for efficiency"
  (let ((result nil))
    (dotimes (i max)
      (push i result))
    (nreverse result)))

;;; Alists: Association lists
;;; Plists: Property lists
;;; Both can be treated as an implementation of a hash table, though neither will be as performant
;;; as an actual hash table for larger collections of data. They may be more performant for sufficiently
;;; "small" collections.
;; An example use of alists:
; (assoc 'a '((a . 1) (b . 2) (c . 3))) -> (A . 1)
; (cdr (assoc 'a '((a . 1) (b . 2) (c . 3)))) -> 1

(explain-and-run :form '(assoc 'a '((a . 1) (b . 2) (c . 3)))
		 :description "Retrieve the key/value pair from the alist literal at 'a")

(explain-and-run :form '(cdr (assoc 'a '((a . 1) (b . 2) (c . 3))))
		 :description "Retrieve the value from the alist literal at key 'a")

;; We can change the equality comparison function with the :test keyword
; (assoc "a" '(("a" . 1) ("b" . 2) ("c" . 3)) :test #'string=) -> ("a" . 1)

(explain-and-run :form '(assoc "a" '(("a" . 1) ("b" . 2) ("c" . 3)) :test #'string=)
		 :description "Get the key/value pair in the alist literal at \"a\", using the function `string=' for comparison")

;; We can generate an alist using the function pairlis, so we could create an alist like so:
;; (pairlis '(a b c d) '(1 2 3 4)) -> ((a . 1) (b . 2) (c . 3) (d . 4)) OR ((d . 4) (c . 3) (b . 2) (a . 1))
;; the ordering is not guaranteed, but the key/value mapping is the same either way

(explain-and-run :form '(pairlis '(a b c d) '(1 2 3 4))
		 :description "Use the function `pairlis' to create an alist from two list literals, result list order not defined")

;; While plists and alists are similar, plists are much less flexible, supporting only the `getf` function to
;; retrieve mappings, returning NIL if a key is not found, though they are simpler. An equivalent plist to
;; the alists described above would be written like so:
; '(a 1 b 2 c 3 d 4)
;; So the lookup using `getf` would be written as such:
; (getf '(a 1 b 2 c 3 d 4) 'a) -> 1

(explain-and-run :form '(getf '(a 1 b 2 c 3 d 4) 'a)
		 :description "Extract the value for key 'a in the plist literal with `getf'")

;;; There's a lot that can be done with CL's file operations, for example, we'll create a function to `cat' a file
(defun my-cat-fn (filepath)
"Attempt to open `filepath', on success, read and print each line before closing the file"
  (let ((in (open filepath :if-does-not-exist nil))) ; `in' is NIL if the file doesn't exist
    (when in ; Only proceed when `in' is not NIL
      (loop for line = (read-line in nil) ; Read a line from the file handle `in', returning NIL if an error/EOF is hit
	    while line do (format t "~a~%" line)) ; Print each line we read and bound to `line'
      (close in)))) ; Ensure the file is closed

(explain-and-run :form '(my-cat-fn "/etc/profile")
                 :description "Read and print the contents of '/etc/profile' using `my-cat-fn', if it exists, closing afterwards")

;;; Create a simplistic account number sequence, so new bank-account objects get an assigned, auto-incrementing ID
(defvar *most-recent-account* 1)

;;; Create a toy bank account class that enforces some amount of correctness with keyword arguments and default initializers
(defclass bank-account ()
  ((account-num
    :initarg :account-num
    :initform (incf *most-recent-account*))
  (balance
    :initarg :balance
    :initform 0)
  (customer-name
    :initarg :customer-name
    :initform (error "Must supply a customer name to create account."))
  (account-type
    :initarg :account-type
    :initform :savings)
   (membership-level)))

;;; Create a custom initializer method to determine membership-level based on the account balance, must be an :after method to inspect
;;; the 'balance slot value
(defmethod initialize-instance :after ((account bank-account) &key)
  (let ((balance (slot-value account 'balance)))
    (setf (slot-value account 'membership-level)
    	(cond
	  ((>= balance 250000) :platinum)
	  ((>= balance 100000) :gold)
	  ((>= balance 50000)  :silver)
	  (t :bronze)))))

;;; Create a generic function and a concrete implementation for getting the balance of a bank-account object or subclassed object
(defgeneric balance (account)
  (:documentation "Retrieve the balance of a given account instance"))

(defmethod balance ((account bank-account))
  (slot-value account 'balance))

;;; Create generic functions for manipulating the account balance
(defgeneric withdraw (account amount)
  (:documentation "Withdraw the specified amount from the given account's balance"))

(defmethod withdraw ((account bank-account) amount)
  (cond
    ((> amount (balance account)) (error "Insufficient funds for transaction!"))
    ((< amount 0) (error "Cannot withdraw negative values"))
    (t  (setf (slot-value account 'balance) (- (balance account) amount)))))

(defgeneric deposit (account amount)
  (:documentation "Deposit the specified amount into the given account's balance"))

(defmethod deposit ((account bank-account) amount)
  (if (< amount 0)
      (error "Cannot deposit negative values"))
  (setf (slot-value account 'balance) (+ (balance account) amount)))

;;; Create generic functions for retrieving additional attributes for the bank accounts (owner, ID, type, level, etc.)

(defgeneric owner (account)
  (:documentation "Retrieve the owner listed on the given account."))

(defmethod owner ((account bank-account))
  (slot-value account 'customer-name))

(defgeneric (setf customer-name) (name account)
  (:documentation "Set the customer-name for the given account instance"))

(defmethod (setf customer-name) (name (account bank-account))
  (setf (slot-value account 'customer-name) name))

(defgeneric account-type (account)
  (:documentation "Retrieve the account type of the given account instance"))

(defmethod account-type ((account bank-account))
  (slot-value account 'account-type))

;;; I didn't read ahead, so now we'll create a "better bank account" class that removes the need for so much boilerplate
;;; NOTE: Since this subclasses the existing `bank-account' class, we get to keep the initializer determining membership level,
;;; and the generic "methods" for managing the slots like (withdraw account amount) still work too. Inheritance can be a mess, but
;;; it's also nice to not need the same sort of tricks as in C
(defclass better-bank-account (bank-account)
  ((customer-name
    :initarg :customer-name
    :initform (error "Must supply a customer name.")
    :accessor customer-name
    :documentation "Owner of the account")
   (balance
    :initarg :balance
    :initform 0
    :reader balance
    :documentation "Current account balance")
   (account-number
    :initform (incf *most-recent-account*)
    :reader account-number
    :documentation "Account number, unique within a bank")
   (membership-level
    :reader membership-level
    :documentation "One of :platinum, :gold, :silver, or :bronze")
   (account-type
    :reader account-type
    :initarg :account-type
    :initform :savings
    :documentation "Account type, :checking, :savings (default), etc.")))


;;; Create a low balance penalty function for accounts, because we're that kind of bank
(defparameter *minimum-balance* 10000)

(defgeneric minimum-balance-check (account)
  (:documentation "Check the balance to see if a low-balance penalty needs to be issued"))

;;; Uses the `with-slots' macro to bind the slot `balance' to the variable 'balance', seems to be similar to `let*' forms
(defmethod minimum-balance-check ((account bank-account))
  (with-slots (balance) account
    (when (< balance *minimum-balance*)
      (decf balance (* balance 0.02)))))

;;;; Getting into the `format' function arguments and related magic, mostly going to be self-documenting examples using `explain-and-run'
(explain-and-run :form '(format t "~{~a~^, ~}" '(1 2 3 4 5))
  :description "Print the list literal, '(1 2 3 4 5) in a human-friendly format")

(explain-and-run :form '(format t "~$" pi)
		 :description "Print pi with default floating-point representation")

(explain-and-run :form '(format t "~5$" pi)
		 :description "Print pi as floating-point with 5 significant digits")

(explain-and-run :form '(format t "~v$" 3 pi)
		 :description "Print pi as floating point using 3 significant digits, specified in the argument list")

(explain-and-run :form '(format t "~#$" pi)
		 :description "Print pi as floating point with 1 significant digit, due to an argument list length of 1")

(explain-and-run :form '(format t "~,5f" pi)
		 :description "Print pi as floating point with 5 significant digits using the `f' directive")

(defparameter *million* 1000000)

(explain-and-run :form '(format t "~d" *million*)
		 :description "Print one million with default integer rules")

(explain-and-run :form '(format t "~:d" *million*)
		 :description "Print one million with comma separators")

(explain-and-run :form '(format t "~@:d" *million*)
		 :description "Print one million with sign and comma separators")

(explain-and-run :form '(format t "~a" *million*)
		 :description "Print one million using the ~aesthetic~ directive")

(explain-and-run :form '(format t "~a" pi)
		 :description "Print pi using the ~aesthetic~ directive")

(explain-and-run :form '(format t "~a" '(1 2 3 4))
                 :description "Print the list literal '(1 2 3 4) using the ~aesthetic~ directive")

;;; I assume something broke the parsing for handling auto-indents, but it's unclear where that error happened,
;;; Interestingly, the insistence on removing indentation will also break the use of C-c C-c to compile/run the
;;; S-expression via SLIME, stating unbalenced parens, which is "fixed" by re-indenting the block manually.
(explain-and-run :form '(format nil "~s" '(1 2 3 4))
  :description "Print the list literal '(1 2 3 4) using the 's' directive, allowing re-reading")


(explain-and-run :form '(format t "~12,'0:d" *million*)
  :description "Print one million with 12 padding characters, padding character set to '0, including comma separators")

(explain-and-run :form '(format nil "~4,'0d-~2,'0d-~2,'0d" 2025 12 15)
  :description "Print a fixed-width date string, using padding as needed")

(explain-and-run
  :form '(format nil "~,,'.,4:d" *million*)
  :description "Print one million with the grouping set to 4 digits, using decimals instead of commas for separation")

(explain-and-run
  :form '(format nil "~x" *million*)
  :description "Print one million with the default hex format")

(explain-and-run :form '(format nil "~o" *million*)
  :description "Print one million with the default octal format")

(explain-and-run :form '(format nil "~b" *million*)
  :description "Print one million with the default binary format")

(explain-and-run :form '(format nil "~32,'0,' ,4:b" *million*)
  :description "Print one million in binary, with padding (to 32 Bits) and space separators between nibbles")

(explain-and-run :form '(format nil "~f" pi)
  :description "Print pi with default floating point rules")

(explain-and-run :form '(format nil "~,4f" pi)
  :description "Print pi with 4 sig figs")

(explain-and-run :form '(format nil "~,4e" pi)
		 :description "Print pi in computerized scientific notation with 4 sig figs")

(explain-and-run :form '(format nil "~e" pi)
		 :description "Print pi in default computerized scientific notation")

(explain-and-run :form '(format nil "~:d = ~r" *million* *million*)
		 :description "Print one million in plain english")

(explain-and-run :form '(format nil "~:d = ~:r" *million* *million*)
		 :description "Print one million as an ordinal description")

(explain-and-run :form '(format nil "~r file~p" *million* *million*)
		 :description "Conditionally pluralize the message based on the value passed")

(explain-and-run :form '(format nil "~:r file~p" *million* 1)
		 :description "Conditionally pluralize the message based on the value passed")

(explain-and-run :form '(format nil "~r file~:p" *million*)
		 :description "Conditionally pluralize the message based on a singular, re-parsed value")

(explain-and-run :form '(format nil "~(~a~)" "ALL CAPS")
		 :description "Print the given string converted to lower-case")

(explain-and-run :form '(format nil "~@r" 2025 )
		 :description "Print 2025 in roman numerals")

(explain-and-run :form '(format nil "~(~@r~)" 2025)
		 :description "Print 2025 in lowercase roman numerals")

(explain-and-run :form '(format nil "~@(~a~)" "hello, world")
		 :description "Print \"hello, world\" with the first \"word\" capitalized")

(explain-and-run :form '(format nil "~@:(~a~)" "hello, world")
  :description "Print \"hello, world\" fully capitalized")

(explain-and-run :form '(format nil "~:(~a~)" "hello, world")
  :description "Print \"hello, world\" with each \"word\" in title-case")

(explain-and-run :form '(format nil "~[cero~;uno~;dos~]" 0)
  :description "Print the value at the given 0-based index in the bracketed list, or nothing if the index is out of bounds")

(explain-and-run :form '(format nil "~[cero~;uno~;dos~]" 3)
  :description "Print the value at index 3 in the bracketed list (expecting nil/\"\")")
()

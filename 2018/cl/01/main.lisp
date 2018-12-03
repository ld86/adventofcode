(defun read-numbers (filename)
  (let ((input (open filename)))
       (loop for line = (read-line input nil)
	    while line collect (parse-integer line))))

(defun solve-one (filename) (apply #'+ (read-numbers filename)))

(defun outer (nums)
  (let
      ((current nums)
       (result 0))
      
    (lambda ()
      (if (not current)
	  (setf current nums))
      (setf result (car current))
      (setf current (cdr current))
      result)))

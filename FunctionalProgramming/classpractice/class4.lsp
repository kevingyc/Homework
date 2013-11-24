(defun avg (&rest args)
(/ (apply #'+ args) (length args)))

(defmacro avgm (&rest args)
`(/ (+ ,@args) ,(length args)))

(defmarco when-nil (tri &rest args)
`(when (not ,tri) ,args))
(defun our-complement (fn)
  #'(lambda (&rest data) (not (apply fn data))))

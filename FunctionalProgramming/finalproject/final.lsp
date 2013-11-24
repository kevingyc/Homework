(defparameter xr '(3 1 4 0 2 g e))
(defparameter sym '(aaa))
(defparameter num '(111))

(defun editor! ()
(instruction))

(defun instruction ()
(format nil " Welcome to use the list editor! you can use the following function :~%
(insert! (position element)) : to insert a element on the specified position in the list.~%
(delete! (position)) : to delete a element on specified position in the list expect symbol.~%
(plusall! (value)) : to add a value to all the element in the list expect symbol.~%
(minusall! (value)) : to minus a value to all the element in the list expect symbol.~%
(multiall! (value)) : to multiply a value to all the element in the list expect symbol.~%
(diviall! (value)) : to divide a value to all the element in the list expect symbol.~%
(display!) : to display the list.~%
(set! (newlist)) : to set the new value of the list. 
                   if the new one and the orginal has different length, the orginal will be replaced.~%
(save! (filename)) : to save the list in the file.~%
(loadfile! (filename)) : to load data from the file.~%
(search! (element)) : to find the element in the list. if didn't find, it will return nil.~%
(replace! (position value)) : to modify a element on the spectified position.~%
(sort! (functionname)) : to sort the list by the function.~%
(recover! (filename)) : to recover the data before edited. 
                        It will only recover one step."))

(defun insert! (nu va)
(setq yr (append (subseq xr 0 nu) (list va) (subseq xr nu)) zr xr xr yr))

(defun delete! (nu)
(setq yr (append (subseq xr 0 nu) (subseq xr (+ nu 1))) zr xr xr yr))

(defun plusall! (va)
(setf yr (mapcar #'(lambda (xr) (if (symbolp xr) xr (+ xr va))) xr) zr xr xr yr))

(defun minusall! (va)
(setf yr (mapcar #'(lambda (xr) (if (symbolp xr) xr (- xr va))) xr) zr xr xr yr))

(defun multiall! (va)
(setf yr (mapcar #'(lambda (xr) (if (symbolp xr) xr (* xr va))) xr) zr xr xr yr))

(defun diviall! (va)
(setf yr (mapcar #'(lambda (xr) (if (symbolp xr) xr (/ xr va))) xr) zr xr xr yr))

(defun display! ()
(format t "~A " xr))

(defun set! (ir) 
(setf zr xr xr ir))

(defun save! (filename)
(setf path (make-pathname :name filename))
(setf str (open path :direction :output :if-exists :supersede))
(format str "~A~%" xr) (close str))

(defun loadfile! (filename)
(setf path (make-pathname :name filename))
(setf str (open path :direction :input))
(setf zr xr xr (read str)))

(defun search! (so)
(format nil "the element is at position : ~A" (search (list so) xr)))

(defun replace! (nu va)
(setf (nth nu xr) va))

(defun sort! (fn)
(do ((co 1 (+ co 1))) ((null xr)) (setf gn (car xr)) 
(if (symbolp gn) (setf sym (cons gn sym)) (setf num (cons gn num)) ) (setf xr (cdr xr)))
(setf sym (cdr (nreverse sym)) num (cdr (nreverse num)))
(setf yr (append (sort num fn) (nreverse sym)) sym '(aa) num '(11) xr yr))

(defun recover! () 
(setf xr zr))
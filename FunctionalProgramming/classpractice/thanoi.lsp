(defun towel-of-hanoi (disks from to spare)
(unless (endp disks)
(towel-of-hanoi (rest disks) from spare to)
(format t "MOVE ~A FROM ~A TO ~A~%" (car disks) from to)
(towel-of-hanoi (rest disks) spare from to)))


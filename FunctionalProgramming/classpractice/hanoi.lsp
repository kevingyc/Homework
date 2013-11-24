(defun towel-of-hanoi (disks from to spare)
(if (endp disks) 
0 (+ (towel-of-hanoi (rest disks) from spare to) 1 (towel-of-hanoi (rest disks) spare from to))))


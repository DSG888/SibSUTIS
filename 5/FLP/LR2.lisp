; Вариант 2

; 1. Преобразующую список в "двойной" список таким образом, чтобы каждый элемент удвоился.
;    Например, (1 a b 3) –> (1 1 a a b b 3 3).
(defun func (x) (cond ((null x) nil) (t (cons (car x) (cons (car x) (func (cdr x)))))))
(func `(1 a b 3))

; 2. Возвращающую список из пар соседних элементов, одинаково отстоящих от начала и конца списка.
;    Например, (1 a b с 2 3 f) –> ((1 f) (a 3) (b 2) (с))
(defun func (x) (cond((null (cdr x)) (list x)) (t (append (list(cons (car x) (last x))) (func (butlast (cdr x)))))))
(func `(1 a b с 2 3 f))

; 3. Удаляющую элементы из первого списка с номерами из второго списка (второй список упорядочен по возрастанию, нумерация элементов должна начинаться с 1).
;    Например, L1=(a s d f g h j k l), L2=(1 4 5 8) –> (s d h j l).
(defun del_idx (x y &optional (n 1)) (cond ((null x) nil) ((null y) x) ((= (car y) n) (del_idx (cdr x) (cdr y) (1+ n))) ((cons (car x) (del_idx (cdr x) y (1+ n))))))
(del_idx `( a s d f g h j k l) `(1 4 5 8))

(define list
  (lambda args
    (if (nullp args)
	(quote ())
	(cons (car args)
	      (apply list (cdr args))))))
(define for-each
  (lambda args
    (print (quote yo))
    (if (nullp args)
	(print (quote error_for_each_no_function))
	(if (nullp (cdr args))
	    (print (quote error_for_each_no_args))
	    (if (nullp (cdr (cdr args)))
		(apply (car args)
		       (car (cdr args)))
		((lambda ()
		   (apply (car args)
			  (car (cdr args)))
		   (apply for-each
			  (cons (car args)
				(cdr (cdr args)))))))))))
	
(define > (lambda (x y) (< y x)))
(define >= (lambda (x y) (not (< x y))))
(define <= (lambda (x y) (not (< y x))))
(define = (lambda (x y) (if (< x y) 0 (not (< y x)))))
(define abs (lambda (x) (if (< x 0) (- 0 x) x)))
(define factorial (lambda (x) (if (< x 2) 1 (* x (factorial (- x 1))))))
(define list-tail
  (lambda (list k)
    (if k
	(list-tail (cdr list)
		   (- k 1))
	list)))
(define list-ref
  (lambda (list k)
    (car (list-tail list k))))
(define append
  (lambda (left right)
    (if (nullp left)
	right
	(cons (car left) (append (cdr left) right)))))
(define reverse
  (lambda (list)
    (if (nullp list)
	(quote ())
	(append (reverse (cdr list))
	      (cons (car list) (quote ()))))))
(define AND
  (lambda (left right)
    (if left (if right 1 0) 0)))
(define OR
  (lambda (left right)
    (if left 1 (if right 1 0))))

(define equal?
  (lambda (obj1 obj2)
    (if (AND (nullp obj1) (nullp obj2))
	1
	(if (AND (listp obj1) (listp obj2))
	    (AND (equal? (car obj1) (car obj2)) (equal? (cdr obj1) (cdr obj2)))
	    (if (OR (AND (intp obj1) (intp obj2))
		    (OR (AND (doublep obj1) (doublep obj2))
			(AND (symbolp obj1) (symbolp obj2))))
		(not (OR (< obj1 obj2) (> obj1 obj2)))
		0)))))
(define assoc
  (lambda (key my_list)
    (if (equal? (car (car my_list)) key)
	(car my_list)
	(assoc key (cdr my_list)))))
(define even?
  (lambda (a)
    (if (intp a)
	(equal? (* (/ a 2) 2) a)
	0)))
(define list-partition
  (lambda (proc my-list)
    (if (nullp my-list)
	(quote (()()))
	((lambda (proc my-list)
	  (define sub-ret
	    (list-partition proc (cdr my-list)))
	  (if (proc (car my-list))
	      (cons (cons (car my-list)
			  (car sub-ret))
		    (cdr sub-ret))
	      (cons (car sub-ret)
		    (list (cons (car my-list)
				(car (cdr sub-ret)))))))
	 proc my-list))))
(define list-sort
  (lambda (binary-proc my-list)
     (if (nullp my-list) 
	my-list
	((lambda ()
	   (define pivot
	     (car my-list))
	   (define partitioned-list
	     (list-partition (lambda (x)
			       (binary-proc x pivot))
			     (cdr my-list)))
	   (define sorted-left
	     (list-sort binary-proc (car partitioned-list)))
	   (define sorted-right
	     (list-sort binary-proc (car (cdr partitioned-list))))
	   (append (append sorted-left (list pivot))
		   sorted-right))))))

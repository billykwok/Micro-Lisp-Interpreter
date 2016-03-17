(define >
  (lambda (x y)
    (< y x)))

(define >=
  (lambda (x y)
    (not (< x y))))

(define <=
  (lambda (x y)
    (not (< y x))))

(define =
  (lambda (x y)
    (if (< x y)
	0
	(not (< y x)))))

(define abs
  (lambda (x)
    (if (< x 0)
	(- 0 x)
	x)))

(define factorial
  (lambda (x)
    (if (< x 2)
	1
	(* x (factorial (- x 1))))))

(define unless
  (lambda (c x)
    (if (not c) x)))

(define and
  (lambda args
    (if (nullp args)
	0
	(not (= (reduce * 1 args) 0)))))

(define or
  (lambda args
    (if (nullp args)
	0
	(not (= (reduce + 0 args) 0)))))

(define xor
  (lambda args
    (if (nullp args)
	0
	(not (= (reduce = (car args) args) 0)))))

(define first
  (lambda args (car args)))

(define list
  (lambda args
    (if (nullp args)
	args
	(cons (car args)
	      (list (cdr args))))))
	      
(define for-each
  (lambda (f l)
    (if (not (nullp (car l)))
	(f (car l)))
    (if (not (nullp (cdr l)))
	(for-each f (cdr l)))))

(define map
  (lambda (f l)
    (if (nullp (cdr l))
	(cons (f (car l))
	      (quote ()))
	(cons (f (car l))
	      (map f (cdr l))))))

(define reduce
  (lambda (f i l)
    (if (nullp (cdr l))
	(f (eval (car l)) i)
	(f (eval (car l)) (reduce f i (cdr l))))))

(define list-tail
  (lambda (l k)
    (if (= k 1)
	l
	(list-tail (cdr l) (- k 1)))))

(define list-ref
  (lambda (l k)
    (car (list-tail l k))))

(define list-size
  (lambda (l)
    (if (nullp (cdr l))
	1
	(+ (list-size (cdr l)) 1))))

(define append
  (lambda (l m)
    (if (nullp l)
	m
	(cons (car l)
	      (append (cdr l) m)))))

(define reverse
  (lambda (l)
    (if (nullp l)
	l
	(append (reverse (cdr l)) (cons (car l) (quote ()))))))

(define list-equal?
  (lambda (x y)
    (if (and (nullp x) (nullp y))
	1
	(if (or (nullp x) (nullp y))
	    0
	    (and (equal? (car x) (car y)) (list-equal? (cdr x) (cdr y)))))))

(define equal?
  (lambda (x y)
    (if (and (listp x) (listp y))
	(list-equal? x y)
	(= x y))))

(define mod
  (lambda (x y)
    (- x (* (/ x y) y))))
    
(define even?
  (lambda (n)
    (= (mod n 2) 0)))
	

(define assoc
  (lambda (o a)
    (if (not (listp a))
	0
	(if (equal? o (car (car a)))
	    (car a)
	    (assoc o (cdr a))))))

(define list-partition-true
  (lambda (p l)
    (if (nullp l)
	l
	(if (p (car l))
	    (cons (car l) (list-partition-true p (cdr l)))
	    (list-partition-true p (cdr l))))))

(define list-partition-false
  (lambda (p l)
    (if (nullp l)
	l
	(if (p (car l))
	    (list-partition-false p (cdr l))
	    (cons (car l) (list-partition-false p (cdr l)))))))

(define list-partition
  (lambda (p l)
    (define t (list-partition-true p l))
    (define f (list-partition-false p l))
    (if (nullp t)
	(if (nullp f)
	    (append (quote (())) (quote (())))
	    (append (quote (())) (cons f (quote ()))))
	(if (nullp f)
	    (append (cons t (quote ())) (quote (())))
	    (append (cons t (quote ())) (cons f (quote ())))))))

(define list-sort
  (lambda (p l)
    (define partition-by-pivot
      (lambda (l)
	(list-partition (p (list-ref l (/ (list-size l) 2)) l) l)))
    (if (listp l)
	(if (< (list-size l) 2)
	    l
	    (append (list-sort p (car (partition-by-pivot l)))
		    (append (cons pivot (quote()))
			    (list-sort p (car (cdr (partition-by-pivot l))))))))))

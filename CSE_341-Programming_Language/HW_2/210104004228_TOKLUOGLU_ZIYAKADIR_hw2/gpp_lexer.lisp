
;;put shell line to interpreter
(defun interpret-shell()
	(loop (format t "~%g++> ") (interpreter (read-line))))



;;control file existances and also if exist start process which controlling line by line
(defun interpret-file (filename)
	(let ((in (open filename :direction :input :if-does-not-exist nil)))		
	  (when in (loop for line = (read-line in nil)
	         	while line do (interpreter line)) 
            (close in))
	  (unless in (format t "ERROR: No such file: '~a'" filename))))


(defun interpreter(seq)

	(let ((lst (input-to-lst seq)))
		(if (string= (car lst) ";;") (print "COMMENT")  
		(map nil #'(lambda (token) (print (tokenize token (get-token-lst)))) lst))
	))


;; match tokens with their keyword
(defun get-token-lst ()

	(let((token-key '("and" "or" "not" "equal" "less" "nil" "list"
	 	 			 "append" "concat" "set" "def" "for" "if" 
	 	 			 "exit" "load" "display" "true" "false" "+" "-" 
	 	 			 "/" "*" "(" ")" ","))
		 (token-value '("KW_AND" "KW_OR" "KW_ NOT" "KW_EQUAL" "KW_LESS" 
					   "KW_NIL" "KW_LIST" "KW_APPEND" "KW_CONCAT" "KW_SET" 
					   "KW_DEF" "KW_FOR" "KW_IF" "KW_EXIT" "KW_LOAD" 
					   "KW_DISPLAY" "KW_TRUE" " KW_FALSE" "OP_PLUS" "OP_MINUS"
					   "OP_DIV" "OP_MULT" "OP_OP" "OP_CP" "OP_COMMA")))
		(pairlis token-key token-value)))

	

(defun tokenize (token lst)

	 ;; Start state of DFA.

	 (let ((c (string (char token 0)))) 
	 (cond ((is-alphap c) (tokenize-identifier token lst))  ;; [a-zA-z] identifier and kw
	 	   ((is-numericp c) (tokenize-value token))			;; [defining pdf value] valuef
	 	   (t (if (tokenize-op token lst) 					;; operator
	 	   (tokenize-op token lst) (progn 
           (format t "Syntax-Error ~a can not be tokenized" token)
		   (ext:exit 0)
		   ))))))	;; else, syntax error.
	 	   									 
;; control identifier 
(defun tokenize-identifier (token lst)

	(assert (is-alphap (string (char token 0))))

	;; Scanning one by one.
	(loop for c across token
      unless (or (is-alphap c) (is-numericp c))
      do (progn
           (format t "~%SYNTAX-ERROR ~a cannot be tokenized" token)
		   (ext:exit 0)
		   ))

	(let ((kw (tokenize-kw token lst)))
		(if (null kw) (format nil "IDENTIFIER") kw)))
	


(defun tokenize-value (token)

  (assert (is-numericp (string (char token 0))))

  ;; Find the position of the first 'b' in the token.
  (let ((b-index (position #\b token)))
    (if (and b-index
             (> b-index 0) ; There are digits before 'b'.
             (< b-index (- (length token) 1)) ; There are digits after 'b'.
             (every #'is-numericp (subseq token 0 b-index)) ; Digits before 'b'.
			 (every #'is-numericp (subseq token (1+ b-index))) ; Digits after 'b'.         
             )
        (format nil "VALUEF")
        (progn
           (format t "~%SYNTAX_ERROR ~a cannot be tokenized ~%" token)
		   (ext:exit 0)
		)
	)
  )
)
; tokenize the Keywords
(defun tokenize-kw (token lst)
  (let ((value (assoc token lst :test #'string=)))
    (if value (format nil "~a" (cdr value)) nil)))

;tokinize the operators
(defun tokenize-op (token lst)
	 (let ((value (assoc token lst :test #'string=)))
		(if value (format nil "~a" (cdr value)) nil)))


(defun list-to-string (lst)
    (format nil "~{~A~}" lst))

;controlling character is open bracket '(' or after bracket ')' according to ASCII code
(defun is-bracketsp (chr)
	(let ((c (char-int (coerce chr 'character))))
		(or (= c 40) (= c 41)))) ;; 40: ( 41: )

; controlling character is 0 according to ASCII code
(defun is-zerop (chr)
	(eq (char-code (coerce chr 'character)) 48))
; controlling character is b according to ASCII code
(defun is-b (chr)
	(eq (char-code (coerce chr 'character)) 98))

; controlling character is semicolon according to ASCII code
(defun is-semicolonp (chr)
	(eq (char-code (coerce chr 'character)) 59))

; controlling character is quomark according to ASCII code
(defun is-quomarkp (chr)
	(eq (char-code (coerce chr 'character)) 34))

; controlling character is numeric
(defun is-numericp (chr)

	(let ((c (char-int (coerce chr 'character))))
		(and (>= c (char-int #\0)) (<= c (char-int #\9)))))
	
;controlling charactes is alphatical character
(defun is-alphap (chr)

	(let ((c (char-int (coerce chr 'character))))
  (or (and (>= c (char-int #\A)) (<= c (char-int #\Z)))
      (and (>= c (char-int #\a)) (<= c (char-int #\z)))))

)

;controlling characters is space 
(defun is-spacep (c) (char= c #\Space))

; 1. main helper function of preliminary of DFA
(defun cleanup (str)

	(let ((trim-lst '(#\Space #\Newline #\Backspace #\Tab #\Return )))
	(string-trim trim-lst str)))

; 2. main helper function of preliminary of DFA
(defun split-seq-with-space (string &key (is-spacep #'is-spacep))


  (loop :for start = (position-if-not is-spacep string)
    :then (position-if-not is-spacep string :start (1+ end))
    :for end = (and start (position-if is-spacep string :start start))
    :when start :collect (subseq string start end)
    :while end))

; This is a peliminary of DFA 
(defun input-to-lst (str)

	(setq str (list-to-string (map 'list #'(lambda (c) 
		(if (is-bracketsp c) (concatenate 'string " " (string c) " ") 
		(string c))) (cleanup str))))

	(let ((lst (loop for idx from 0 to (- (length str) 1)
			    when (char= (aref str idx) #\") collect idx))
		  (idx1 '()) (idx2 '()) (space-idx '()))
	(loop while lst do (setq idx1 (car lst)) 
					do (setq idx2 (car (cdr lst)))
					do (setq lst (cdr (cdr lst)))
					do (setq space-idx
		 	(loop for idx from 0 to (- (length str) 1)
			when (and (> idx idx1) (< idx idx2) (char= (aref str idx) #\Space)) 
			collect idx)))


	(split-seq-with-space (list-to-string
	(loop for idx from 0 to (- (length str) 1)
		if (member idx space-idx) collect #\. else collect (aref str idx)))))
)

(defun gppinterpreter (&optional filename)
	(if filename (interpret-file filename) (interpret-shell))
	)

(if *args* (gppinterpreter (car *args*)) (gppinterpreter))

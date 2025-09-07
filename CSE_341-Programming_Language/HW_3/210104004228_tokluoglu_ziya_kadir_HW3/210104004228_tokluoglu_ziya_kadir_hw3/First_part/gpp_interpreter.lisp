
(defvar *global-tokens* '())
(defvar *global-functions* '())



(defclass AST_Node ()
  ((token :accessor token :initarg :token :initform nil)
   (children :accessor children :initarg :children :initform nil)
   (name :accessor name :initarg :name :initform nil)
   (numerator :accessor item-numerator :initarg :numerator :initform 0)
   (denominator :accessor item-denominator :initarg :denominator :initform 1)))

(defclass MyFunction ()
  ((name :accessor name :initarg :name :initform nil)
   (children :accessor children :initarg :children :initform nil)
   (parameter :accessor parameter :initarg :parameter)
   (parameter_value :accessor parameter_value :initarg :parameter_value)
   (numerator :accessor item-numerator :initarg :numerator :initform 0)
   (denominator :accessor item-denominator :initarg :denominator :initform 1)
   ))


(defun interpret-shell()
  (loop
    (format t "~%g++> ")
    (let ((input (read-line)))
      (if (string= input "q")
          (return)
          (interpreter input)))))


;;control file existances and also if exist start process which controlling line by line
(defun interpret-file (filename)
	(let ((in (open filename :direction :input :if-does-not-exist nil)))		
	  (when in (loop for line = (read-line in nil)
	         	while line do (interpreter line)) 
            (close in))
	  (unless in (format t "ERROR: No such file: '~a'" filename))))


(defun interpreter(seq)
  (let ((lst (input-to-lst seq)))
    (if (string= (car lst) ";;") 
		()
        ;   (format t "COMMENT ~%")
        (map nil #'(lambda (token) 
                     (setq *global-tokens* (append *global-tokens* (list (tokenize token (get-token-lst))))))
             lst))))



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
		(pairlis token-key token-value))
)

	

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
    ; (format t "~%~a~%" token)
		(if (null kw) (make-instance 'AST_Node :token "IDENTIFIER" :name token) kw))
)
	


(defun tokenize-value (token)
  (assert (is-numericp (string (char token 0))))

  ;; Find the position of the first 'b' in the token.
  (let ((b-index (position #\f token)))
    (if (and b-index
             (> b-index 0) ; There are digits before 'b'.
             (< b-index (- (length token) 1)) ; There are digits after 'b'.
             (every #'is-numericp (subseq token 0 b-index)) ; Digits before 'b'.
             (every #'is-numericp (subseq token (1+ b-index))) ; Digits after 'b'.         
             )
        (let ((numerator (parse-integer (subseq token 0 b-index)))
              (denominator (parse-integer (subseq token (1+ b-index)))))
          (make-instance 'AST_Node :token "VALUEF" :numerator numerator :denominator denominator))
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
    (if value (make-instance 'AST_Node :token (cdr value)) nil)))

;tokinize the operators
(defun tokenize-op (token lst)
	 (let ((value (assoc token lst :test #'string=)))
		(if value (make-instance 'AST_Node :token (cdr value)) nil)))


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


	(setq tokens(split-seq-with-space (list-to-string
	(loop for idx from 0 to (- (length str) 1)
		if (member idx space-idx) collect #\. else collect (aref str idx))))))

	; (format t "~{~a~%~}" tokens)

	tokens
)






; (defun separate-children (node)
;   (when node
;     (append (list node)  ; Add the node to the list
;             (mapcan #'separate-children (children node)))))   ; Recursively call separate-children on each child




(defun separate-children (node)
  (when node
    (setf (children node) 
          (remove-if (lambda (child) (string= (token child) "EXP"))
                     (append (list node)  ; Add the node to the list
                             (mapcan #'separate-children (children node)))))))   


;; Define the my_shift function with debug print
(defun my_shift (token stack)
  ; (format t "Shifting token: ~A~%" token)
  (if (null token)
      stack
      (nconc stack (list token))))

;; Function to print the current state of the stack
(defun print-stack (stack)
  (format t "Current stack: ~{~A~^, ~}~%" (mapcar #'token stack))
)

(defun print-node-details (node)
  (format t "Node: ~a, Numerator: ~a, Denominator: ~a~%"
          (token node) (item-numerator node) (item-denominator node))
  (dolist (child (children node))
    (print-node-details child)))



(defun check-reduction (stack)
  (let ((len (length stack)))
    (loop for i from 1 to len do
      (let* ((top-tokens (mapcar #'token (subseq stack (- len i)))))
        (let ((match (match-production-rule top-tokens)))
          (if match (return match)))))))

(defun match-production-rule (tokens)
  ; (format t "Matching production rule for: ~{~A~^, ~}~%" tokens)
  (cond
    ((equal tokens '("OP_OP" "OP_PLUS" "EXP" "EXP" "OP_CP")) 'plus-exp)
    ((equal tokens '("OP_OP" "OP_MINUS" "EXP" "EXP" "OP_CP")) 'minus-exp)
    ((equal tokens '("OP_OP" "OP_MULT" "EXP" "EXP" "OP_CP")) 'mult-exp)
    ((equal tokens '("OP_OP" "OP_DIV" "EXP" "EXP" "OP_CP")) 'div-exp)
    ((equal tokens '("OP_OP" "KW_DEF" "EXP" "EXP" "OP_CP")) 'func-call-void)
    ((equal tokens '("OP_OP" "KW_DEF" "EXP" "EXP" "EXP" "OP_CP")) 'func-call-one)
    ((equal tokens '("OP_OP" "KW_DEF" "EXP" "EXP" "EXP" "EXP" "OP_CP")) 'func-call-two)
    ((equal tokens '("OP_OP" "EXP" "OP_OP" "OP_CP"  "OP_CP")) 'call-func-void)
    ((equal tokens '("OP_OP" "EXP" "EXP" "OP_CP")) 'call-func-one)
    ((equal tokens '("OP_OP" "EXP" "EXP" "EXP" "OP_CP")) 'call-func-two)
    ((equal tokens '("OP_OP" "KW_IF" "OP_OP" "EXP" "OP_CP" "OP_OP" "EXP" "OP_CP" "OP_OP" "EXP" "OP_CP" "OP_CP")) 'if-stat)
    ((equal tokens '("IDENTIFIER")) 'id-exp)
    ((equal tokens '("VALUEF")) 'valuef-exp)
    ; Add cases for other production rules
    (t nil)))

(defun perform-reduction (reduction stack)
  ; (format t "Performing reduction: ~A~%" reduction)
  ; (format t "reduction: ~a~%" reduction)
  (setq stack (reverse stack)) ; Reverse the stack at the start
  (case reduction
    (plus-exp
    (let* ((past_nodes '()))
      (setq past_nodes (append past_nodes (list (pop stack))))

     (let ((right (pop stack))
           (left (pop stack)))

          (setq past_nodes (append past_nodes (list right)))
          (setq past_nodes (append past_nodes (list left)))
          (setq past_nodes (append past_nodes (list (pop stack))))
          (setq past_nodes (append past_nodes (list (pop stack))))
          
       (push (make-instance 'AST_Node
                            :token "EXP"
                            :numerator (+ (* (item-numerator left) (item-denominator right))
                                          (* (item-numerator right) (item-denominator left)))
                            :denominator (* (item-denominator left) (item-denominator right))
                            :children past_nodes
                            )
            stack))
            )
    )
    (minus-exp
    (let* ((past_nodes '()))
      (setq past_nodes (append past_nodes (list (pop stack))))

     (let ((right (pop stack))
           (left (pop stack)))

          (setq past_nodes (append past_nodes (list right)))
          (setq past_nodes (append past_nodes (list left)))
          (setq past_nodes (append past_nodes (list (pop stack))))
          (setq past_nodes (append past_nodes (list (pop stack))))
          
       (push (make-instance 'AST_Node
                            :token "EXP"
                            :numerator (- (* (item-numerator left) (item-denominator right))
                                          (* (item-numerator right) (item-denominator left)))
                            :denominator (* (item-denominator left) (item-denominator right))
                            :children past_nodes
                            )
            stack))
            )
    )

    (mult-exp
    (let* ((past_nodes '()))
      (setq past_nodes (append past_nodes (list (pop stack))))

     (let ((right (pop stack))
           (left (pop stack)))

          (setq past_nodes (append past_nodes (list right)))
          (setq past_nodes (append past_nodes (list left)))
          (setq past_nodes (append past_nodes (list (pop stack))))
          (setq past_nodes (append past_nodes (list (pop stack))))
          
       (push (make-instance 'AST_Node
                            :token "EXP"
                            :numerator (* (item-numerator left) (item-numerator right))
                            :denominator (* (item-denominator left) (item-denominator right))
                            :children past_nodes
                            )
            stack))
            )
    )

    (div-exp
    (let* ((past_nodes '()))
      (setq past_nodes (append past_nodes (list (pop stack))))

     (let ((right (pop stack))
           (left (pop stack)))

          (setq past_nodes (append past_nodes (list right)))
          (setq past_nodes (append past_nodes (list left)))
          (setq past_nodes (append past_nodes (list (pop stack))))
          (setq past_nodes (append past_nodes (list (pop stack))))
          
       (push (make-instance 'AST_Node
                            :token "EXP"
                            :numerator (* (item-numerator left) (item-denominator right))
                            :denominator (* (item-denominator left) (item-numerator right))
                            :children past_nodes
                            )
            stack))
            )
    )

    (id-exp
    (let ((id-node (pop stack)))
      (push (make-instance 'AST_Node
                          :token "EXP"
                          :children (list id-node)
                          :numerator (item-numerator id-node)
                          :denominator (item-denominator id-node)
                          :name (name id-node)
                          )
            stack))
    )
    (valuef-exp
      ; (format t "valuef-exp~%")
      (let ((valuef-node (pop stack)))
        (push (make-instance 'AST_Node
                            :token "EXP"
                            :children (list valuef-node)
                            :numerator (item-numerator valuef-node)
                            :denominator (item-denominator valuef-node))
              stack))
     )

    (func-call-void
      ;  (format t "func-call-void~%")
        ; (print-stack stack)
      (let ((id-node5 (pop stack))
            (id-node4 (pop stack))
            (id-node3 (pop stack))
            (id-node2 (pop stack))
            (id-node1 (pop stack)))

        
        (push (make-instance 'MyFunction
                     :name (name id-node3)
                     :children (reverse (separate-children id-node4))
                     :parameter id-node4
                     :numerator (item-numerator id-node4)
                     :denominator (item-denominator id-node4)
                     )
      *global-functions*))
     )

    (func-call-one
      ;  (format t "func-call-one~%")
      (let ((id-node6 (pop stack))
            (id-node5 (pop stack))
            (id-node4 (pop stack))
            (id-node3 (pop stack))
            (id-node2 (pop stack))
            (id-node1 (pop stack)))
          
        ;  (print-stack (separate-children id-node5))
        (push (make-instance 'MyFunction
                     :name (name id-node3)
                     :children (reverse (separate-children id-node5))
                     :parameter (list id-node4)
                     )
      *global-functions*))
     )

    (func-call-two
      ;  (format t "func-call-two~%")
      (let ((id-node7 (pop stack))
            (id-node6 (pop stack))
            (id-node5 (pop stack))
            (id-node4 (pop stack))
            (id-node3 (pop stack))
            (id-node2 (pop stack))
            (id-node1 (pop stack)))

            ;  (print-stack (separate-children id-node6))
        (push (make-instance 'MyFunction
                     :name (name id-node3)
                     :children (reverse (separate-children id-node6))
                     :parameter (list id-node4 id-node5)
                     )
      *global-functions*))
    )
    
    (call-func-void
      ;  (format t "call-func-void~%")
      (let (
            (id-node5 (pop stack))
            (id-node4 (pop stack))
            (id-node3 (pop stack))
            (id-node2 (pop stack))
            (id-node1 (pop stack)))
        (let ((func (find (name id-node2) *global-functions* :key #'name :test #'string-equal)))
          (if func
              (push (make-instance 'AST_Node
                                   :token "EXP"
                                   :children (children func)
                                   :numerator (item-numerator func)
                                   :denominator (item-denominator func))
                    stack)
              (progn
                (format t "ERROR: Function ~a is not defined~%" (name id-node1))
                (quit)))))
      )

 (call-func-one
  ; (format t "call-func-one ~%")
  (let (
        (id-node4 (pop stack))
        (id-node3 (pop stack))
        (id-node2 (pop stack))
        (id-node1 (pop stack)))

    (let ((func (find (name id-node2) *global-functions* :key #'name :test #'string-equal)))
      ; (print-stack (children func))
      (if func
          (progn
            (let ((amk (children func)))
              (dolist (child amk)
                (when (string= (token child) "IDENTIFIER")
                  (setf (item-numerator child) (item-numerator id-node3))
                  (setf (item-denominator child) (item-denominator id-node3))
                  ; (print-stack amk)
                  ))
              (push (make-instance 'AST_Node
                                   :token "EXP"
                                   :children amk
                                   :numerator (item-numerator (parse amk))
                                   :denominator (item-denominator func))
                    stack)))
          (progn
            (format t "ERROR: Function ~a is not defined~%" (name id-node1))
            (quit)))))
      )

    (call-func-two
      ; (format t "call-func-two ~%")
      (let (
            (id-node5 (pop stack))
            (id-node4 (pop stack))
            (id-node3 (pop stack))
            (id-node2 (pop stack))
            (id-node1 (pop stack)))


          
        (let ((func (find (name id-node2) *global-functions* :key #'name :test #'string-equal)))
          ; (print-stack (children func))
          ; (format t "call-func-two ~%")
          (if func
              (progn
                (let ((amk (children func))
                      (counter 0))
                  (dolist (child amk)
                    (when (string= (token child) "IDENTIFIER")
                      (incf counter)
                      (if (= counter 1)
                          (progn
                            (setf (item-numerator child) (item-numerator id-node3))
                            (setf (item-denominator child) (item-denominator id-node3)))
                          (progn
                            (setf (item-numerator child) (item-numerator id-node4))
                            (setf (item-denominator child) (item-denominator id-node4))))
                      ; (print-stack amk)
                      ))
                  (push (make-instance 'AST_Node
                                      :token "EXP"
                                      :children amk
                                      :numerator (item-numerator (parse amk))
                                      :denominator (item-denominator func))
                        stack)))
              (progn
                (format t "ERROR: Function ~a is not defined~%" (name id-node1))
                (quit)))))
    )  

    (if-stat
      ; (format t "if-stat ~%")
      (let (
            (id-node12 (pop stack))
            (id-node11 (pop stack))
            (id-node10 (pop stack))
            (id-node9 (pop stack))
            (id-node8 (pop stack))
            (id-node7 (pop stack))
            (id-node6 (pop stack))
            (id-node5 (pop stack))
            (id-node4 (pop stack))
            (id-node3 (pop stack))
            (id-node2 (pop stack))
            (id-node1 (pop stack)))

    ; ((equal tokens '("OP_OP" "KW_IF" "OP_OP" "EXP" "OP_CP" "OP_OP" "EXP" "OP_CP" "OP_OP" "EXP" "OP_CP" "OP_CP")) 'if-stat)

          
            (if (zerop (item-numerator id-node4))
                (push (make-instance 'AST_Node
                                    :token "EXP"
                                    :children (children id-node7)
                                    :numerator (item-numerator id-node7)
                                    :denominator (item-denominator id-node7))
                      stack)
                (push (make-instance 'AST_Node
                                    :token "EXP"
                                    :children (children id-node10)
                                    :numerator (item-numerator id-node10)
                                    :denominator (item-denominator id-node10))
                      stack)))
      )


    ;; Add cases for other reductions
    )
  (setq stack (reverse stack)) ; Reverse the stack again at the end
  stack) ; Return the modified stack

;; Main parsing function
(defun parse (tokens)
  (let ((stack '()))
    (dolist (token tokens)
      (setq stack (my_shift token stack))
      ; (print-stack stack)
      (loop
        (let ((reduction (check-reduction stack)))
          ; (format t "reduction: ~a~%" reduction)
          (if reduction
              (progn
                (setq stack (perform-reduction reduction stack))
                ; (print-stack stack)
              )
              (return)))))
    ; (print-stack stack)
    (when (= (length stack) 1)
      (let ((last-node (car stack)))
        ; (format t "~af~a~%" (item-numerator last-node) (item-denominator last-node))
        ; (print-node-details last-node)
        ))
    (when (> (length stack) 1)
      (format t "Syntax error: More than one element in the stack~%")
      (print-stack stack)
      (quit))
    (car stack)))



(defun gppinterpreter (&optional filename)
	(if filename (interpret-file filename) (interpret-shell))
	

(let ((last (parse *global-tokens*)))
  (format t "~af~a~%" (item-numerator last) (item-denominator last))
)
)


(if *args* (gppinterpreter (car *args*)) (gppinterpreter))


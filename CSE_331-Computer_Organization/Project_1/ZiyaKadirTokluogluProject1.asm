	.data

Column:		.word 0
Row:		.word 0
Time:		.word 0

Enter_row:	.asciiz "Please enter the row\n"
Enter_column:	.asciiz "Please enter the column\n"
Enter_time:	.asciiz "Please enter the time of game\n"

Printing_map:	.asciiz "\n\nMap,s Printing \n"
Printing_input:	.asciiz "\nEnter the map (char by char) don't enter just write char"


	.text
	
Main:	
	#initialization variable
	
		#printing Enter row string
		
		la $a0, Enter_row
		li $v0, 4
		syscall
			
		#read row as a integer word
		li $v0, 5
		syscall
		move $s0, $v0
		#s0 holds the row number
		
		
		#printing Enter Column string
		la $a0, Enter_column
		li $v0, 4
		syscall
		
		#read column as a integer word
		li $v0, 5
		syscall
		move $s1, $v0
		#s1 holds column number

		#printing Enter time string
		
		la $a0, Enter_time
		li $v0, 4
		syscall
		
		#read time of game as a integer word
		li $v0, 5
		syscall
		move $s2, $v0
		#s2 holds the time of game
		
		
		#loading '.' to s3
		li $s3, 46
			
		#loading 'O' to s4
		li $s4, 79
			
		#loading 'X'
		li $s5, 88		
		
		
		
		jal Game
		
		j Exit 	
		
Game: 
	move $s6, $ra	   # keeping the ra register because we call inner function
	
	
	addi $t8, $zero, 0 # i = 0
	
	Game_For_loop:
		
		if_game_1:  # i == 0
			bne $zero, $t8, if_game_2 
			
			jal Create_map # creating function
			
			jal Fill_map_user  # filling map from user input 
			
			jal Print_map	   # printing map
			
			j if_game_exit
			
		if_game_2:  # i % 2 == 1
			
			andi $t1, $t8, 1	 
			bne  $t1, 1 , if_game_3
			
			jal Fill_map_bomberman  # filling map from bomberman 
			
			jal Print_map # printing map
		
			j if_game_exit
			
		if_game_3:  # i % 2 == 0
			jal Bomb  # bombing trigered bomb
			
			jal Print_map  # printing map
			
		if_game_exit:
	

	
		addi $t8, $t8, 1  # i++
		bne $t8, $s2, Game_For_loop  # Condition of loop (i != row_number)
		
	move $ra, $s6	  # to return back 
	
	#return calling adress
	jr $ra
	
	
	
Bomb: 

	addi $t0,$zero,0 #i = 0
		
	Bomb_For_loop_1:	
		
		addi $t1, $zero, 0 # k = 0
		
		#put new line
		#li $a0, 10
		#li $v0, 11
		#syscall
		
		Bomb_For_loop_2:	
			mul $t2, $t0, $s1 # (i*column_number)
			add $t2, $t2, $t1 # (i*column_number)+ k
			
			add $t3, $t2, $s7
			
			#reading from array
			lb $t4, 0($t3)
			#this line has to be changed with t4 +
			
			
			
			if_control_bomb_1:
				bne $t4, $s5, exit_control_bomb_1
				sb $s3, 0($t3) # map[i][k] = '.' bomb!!!
				
				if_bomb_1: 
					beq $zero, $t0, if_bomb_2 # controlling i == 0
					nor  $t5, $s1, $zero  # one's complement
					addi $t5, $t5 , 1    # two's complement     * this provides to previous row location *
					add  $t6, $t3, $t5  # map[i -1]		    * with looking previous column number adress *
					lb $t7, 0($t6)      # *map[i -1]
					beq $t7, $s5, if_bomb_2 #map[i-1][k] == 'X'  controlling adress is bomb
					sb  $s3, 0($t6)		#map[i-1][k] = '.' bomb!!!
					
					
				if_bomb_2:
					addi $t5, $s0 , -1	# $t7 = row-1
					beq  $t0, $t5 , if_bomb_3 # i == row -1
					add $t5, $t3, $s1	 # map[i+1]          * this provides to next row location *
					lb  $t6, 0($t5)		 # *map[i+1]         * with looking next column number adress *
					beq $t6, $s5 , if_bomb_3  # map[i+1][k] == 'X'  controlling adress is bomb
					sb  $s3, 0($t5)		 # map[i+1][k] = '.' bomb!!!
					
				if_bomb_3:
					beq $zero, $t1, if_bomb_4 # k == 0
					addi $t6, $t3, -1         # map[][k-1]       * this provides to previous column location *
					lb   $t7, 0($t6)	# *map[][k-1]
					beq $t7, $s5, if_bomb_4   # map[i][k-1] == 'X'  controlling adress is bomb
					sb $s3, 0($t6)    # map[][k -1] = '.' bomb!!!
					
	
				if_bomb_4:
					addi $t5, $s1, -1		 # $t7 = column -1
					beq $t1, $t5, exit_control_bomb_1  # k == column -1
					addi $t5, $t3, 1		 # map[][k + 1]  * this provides to next column location *
					lb $t6 , 0($t5)		 # *map[][k + 1]
					beq $t6, $s5, exit_control_bomb_1   # map[][k + 1] == 'X'  controlling adress is bomb
					sb $s3, 0($t5)		 # map[][k + 1] = '.'  bomb!!!
					
			exit_control_bomb_1:
			
			
			addi $t1, $t1, 1 # k++
			bne $t1, $s1, Bomb_For_loop_2   # Condition of inner loop (k != column_number)
		
		addi $t0, $t0, 1 #i++
		bne $t0, $s0, Bomb_For_loop_1 # Condition of outer loop (i != row_number)

	#return calling adress	
	jr $ra
	
	


Print_map: 

	addi $t0,$zero,0 #i = 0
	
		#printing string "Printing the map"
		la $a0, Printing_map
		li $v0, 4
		syscall
		
		#SLEEP FOR 1 SECOND
		li $v0, 32
		li $a0, 1000
		syscall
		
	Print_For_loop_1:	
		
		addi $t1, $zero, 0 # k = 0
		
		#put new line
		li $a0, 10
		li $v0, 11
		syscall
		
		
	Print_For_loop_2:	
			mul $t2, $t0, $s1 # (i*column_number)
			add $t2, $t2, $t1 # (i*column_number)+ k
			
			add $t3, $t2, $s7
			

			#load char from the maps
			li $v0, 11
			lb $t4, 0($t3)
			
			#controloling the char statement
			beq $t4, $s4, Print_O  # if it is 'O'  print O
			beq $t4, $s5, Print_O  # if it is 'X'  print O
			beq $t4, $s3, Print_dot # if it is '.'
			
		Print_O: #printng 'O'
			move $a0, $s4
			j Print
		Print_dot: #printing '.'
			move $a0, $s3
		Print:  #print char 
			syscall
		
			addi $t1, $t1, 1 # k++
			bne $t1, $s1, Print_For_loop_2   # Condition of inner loop (k != column_number)
		
		addi $t0, $t0, 1 #i++
		bne $t0, $s0, Print_For_loop_1  # Condition of outer loop (i != row_number)
	
	#return calling adress	
	jr $ra
	
	

Fill_map_bomberman:
		
	addi $t0,$zero,0 #i = 0
		
	Fill_map_bomberman_For_loop_1:	
		
		addi $t1, $zero, 0 # k = 0
		

		
	Fill_map_bomberman_For_loop_2:	
			mul $t2, $t0, $s1 # (i*column_number)
			add $t2, $t2, $t1 # (i*column_number)+ k
			
			add $t3, $t2, $s7
			
			#reading from array
			lb $t4, 0($t3)
			
			
			#loading 'X'
			li $t6, 88
			
		if_bomberman:		
				beq $s3, $t4, bomberman_state_1 #if map[i][k] == '.'
				beq $s4, $t4, bomberman_state_2 # if map[i][k] == 'O'
				j if_bomberman_exit # exit of if
				
		bomberman_state_1:	
				sb $s4 ,0($t3)      #plant the bomb
				j if_bomberman_exit # exit of if
		bomberman_state_2:
				sb $s5 ,0($t3)      #trigger the exist bomb
				j if_bomberman_exit # exit of if
		if_bomberman_exit:		
			
			
			addi $t1, $t1, 1 # k++
			bne $t1, $s1, Fill_map_bomberman_For_loop_2  # Condition of inner loop (k != column_number)
		
		addi $t0, $t0, 1 #i++
		bne $t0, $s0, Fill_map_bomberman_For_loop_1  # Condition of outer loop (i != row_number)
	
	#return calling adress	
	jr $ra
		


	
Fill_map_user:
		
		#printing string "Printing the map"
		la $a0, Printing_input
		li $v0, 4
		syscall
		
	addi $t0,$zero,0 #i = 0
		
	Fill_map_user_For_loop_1:	
		
		
		addi $t1, $zero, 0 # k = 0
		
		#put new line
		li $a0, 10
		li $v0, 11
		syscall
		
		
	Fill_map_user_For_loop_2:	
			mul $t2, $t0, $s1 # (i*column_number)
			add $t2, $t2, $t1 # (i*column_number)+ k
			
			add $t3, $t2, $s7
			
			#entering the char from user
			li $v0,12
			syscall
			move $t4, $v0
			
			sb $t4, 0($t3)  # fill the map with one by one char 
			
			addi $t1, $t1, 1 # k++
			bne $t1, $s1, Fill_map_user_For_loop_2  # Condition of inner loop (k != column_number)
		
		addi $t0, $t0, 1 #i++
		bne $t0, $s0, Fill_map_user_For_loop_1   # Condition of outer loop (i != row_number)
	
	#return calling adress	
	jr $ra
		
	
Create_map: 	
		#multiplication of row and column
		mul $t2, $s0, $s1
			
		#two's complement
		nor $t2, $t2, $zero
		addi $t2, $t2, 1
		
		#allocate the map space like returning 2 dimensional array		
		add $sp, $sp, $t2
		
		# always keep the 2 dimensional array in s7 register 
		move $s7, $sp
		
		#return calling adress
		jr $ra
	
Exit:








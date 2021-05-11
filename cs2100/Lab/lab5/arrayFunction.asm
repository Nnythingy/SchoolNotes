# arrayFunction.asm
       .data 
array: .word 8, 2, 1, 6, 9, 7, 3, 5, 0, 4
newl:  .asciiz "\n"

       .text
main:
	# Print the original content of array
	# setup the parameter(s)
	la $a0, array
	addi $a1, $zero, 10
	# call the printArray function
	jal printArray

	# Ask the user for two indices
	li   $v0, 5         	# System call code for read_int
	syscall           
	addi $t0, $v0, 0    	# first user input in $t0
 
	li   $v0, 5         	# System call code for read_int
	syscall           
	addi $t1, $v0, 0    	# second user input in $t1

	# Call the findMin function
	# setup the parameter(s)
	la $v0, array
	addi $s0, $t0, 0
	sll $s0, $s0, 2
	add $a0, $v0, $s0
	addi $s1, $t1, 0
	sll $s1, $s1, 2
	add $a1, $v0, $s1
	# call the function
	jal findMin

	# Print the min item
	# place the min item in $t3	for printing
	addi $t6, $v0, 0	#saving the address result
	lw $t3, 0($t6)

	# Print an integer followed by a newline
	li   $v0, 1   		# system call code for print_int
	addi $a0, $t3, 0    # print $t3
	syscall       		# make system call

	li   $v0, 4   		# system call code for print_string
	la   $a0, newl    	# 
	syscall       		# print newline

	#Calculate and print the index of min item
	
	# Place the min index in $t3 for printing
	la $a0, array
	sub $t3, $t6, $a0
	srl $t3, $t3, 2

	# Print the min index
	# Print an integer followed by a newline
	li   $v0, 1   		# system call code for print_int
	addi $a0, $t3, 0	# print $t3
	syscall       		# make system call
	
	li   $v0, 4   		# system call code for print_string
	la   $a0, newl    	# 
	syscall       		# print newline
	
	# End of main, make a syscall to "exit"
	li   $v0, 10   		# system call code for exit
	syscall	       	# terminate program
	

#######################################################################
###   Function printArray   ### 
#Input: Array Address in $a0, Number of elements in $a1
#Output: None
#Purpose: Print array elements
#Registers used: $t0, $t1, $t2, $t3
#Assumption: Array element is word size (4-byte)
printArray:
	addi $t1, $a0, 0	#$t1 is the pointer to the item
	sll  $t2, $a1, 2	#$t2 is the offset beyond the last item
	add  $t2, $a0, $t2 	#$t2 is pointing beyond the last item
l1:	
	beq  $t1, $t2, e1
	lw   $t3, 0($t1)	#$t3 is the current item
	li   $v0, 1   		# system call code for print_int
     	addi $a0, $t3, 0    	# integer to print
     	syscall       		# print it
	addi $t1, $t1, 4
	j l1				# Another iteration
e1:
	li   $v0, 4   		# system call code for print_string
     	la   $a0, newl    	# 
     	syscall       		# print newline
	jr $ra			# return from this function


#######################################################################
###   Student Function findMin   ### 
#Input: Lower Array Pointer in $a0, Higher Array Pointer in $a1
#Output: $v0 contains the address of min item 
#Purpose: Find and return the minimum item 
#              between $a0 and $a1 (inclusive)
#Registers used: $t0, $t1, $t2, $s0, $s1, $s2, $v0
#Assumption: Array element is word size (4-byte), $a0 <= $a1
findMin:
	addi $t0, $a0, 0	# saving address of low
	addi $t1, $a1, 4	# saving address of high +4
	lw $s0, 0($t0)		# saving address[low]
l2:	
	slt $t2, $t0, $t1	# checking if address(low) < address(high) +4
	beq $t2, $zero, end
	lw $s1, 0($t0)		# saving current value
	slt $s2, $s0, $s1	# checking if current value is smaller than current min
	bne $s2, $zero, update
	addi $s0, $s1, 0
	addi $v0, $t0, 0
update: 
	addi $t0, $t0, 4	# address of next value
	j l2
end:	
	jr $ra			# return from this function

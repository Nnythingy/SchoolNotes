# arrayCount.asm
  .data 
arrayA: .word 11, 0, 31, 22, 9, 17, 9, 6   # arrayA has 8 values
count:  .word 999             # dummy value

  .text
main:
    # code to setup the variable mappings
    la $t0, arrayA
    la $t8, count
    lw $t9, 0($t8)

    # code for reading in the user value X
    li	$v0, 5
    syscall
    addi $a1, $v0, 0
    addi $a1, $a1, -1

    # code for counting multiples of X in arrayA
	addi $a2, $zero, 0 #current count
	addi $s0, $zero, 0 #iter
	addi $s1, $zero, 8 #number of items in arrayA
loop: 	lw $s2, 0($t0)
	and $t5, $s2, $a1 #finding remainder ##changeeeeeee
	bne $zero, $t5, skip
	addi $a2, $a2, 1 #add 1 to counter if multiple
skip:	addi $s0, $s0, 1
	addi $t0, $t0, 4
	bne $s0, $s1, loop
	
    # code for printing result
    li   $v0, 1    # system call code for print_int
    addi   $a0, $a2, 0    # integer to print
    addi $t9, $a2, 0
    sw $t9, 0($t8)
    syscall        # print the integer

    # code for terminating program
    li  $v0, 10
    syscall

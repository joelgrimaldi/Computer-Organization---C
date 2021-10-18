#############################################################################	
#############################################################################
## Assignment 3: Your Name Goes Here!
#############################################################################
#############################################################################

#############################################################################
#############################################################################
## Data segment
#############################################################################
#############################################################################	
		.data
matrix_a:	.word 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16
matrix_b:	.word 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16
swap:	        .word 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0	
result:	        .word 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0
	
newline:        .asciiz "\n"
tab:	        .asciiz "\t"
		

#############################################################################	
#############################################################################
## Text segment
#############################################################################
#############################################################################
	
		.text		       # this is program code
		.align 2	       # instructions must be on word boundaries
		.globl main	       # main is a global label
	        .globl matrix_swap
	        .globl matrix_multiply
	        .globl matrix_print

#############################################################################	
main:
#############################################################################
		# alloc stack and store $ra
		sub $sp, $sp, 4
		sw $ra, 0($sp)

	        # load matrix A, swap and N into arg regs
	        la $a0, matrix_a
	        la $a1, swap
                li $a2, 4
	        jal matrix_swap
	
		# load A, B and C and N into arg regs
		la $a0, swap
		la $a1, matrix_b
		la $a2, result
	        li $a3, 4
		jal matrix_multiply

		la $a0, result
		jal matrix_print

		# restore $ra, free stack and return
		lw $ra, 0($sp)
		add $sp, $sp, 4
		jr $ra

##############################################################################
matrix_swap: 
##############################################################################
# does matrix swap for a specific 4x4 matrix like assignment 1.
# This is a leaf function and can be done without any stack allocation.
# It is ok if you use the stack.	


	        jr $ra

	
##############################################################################
matrix_multiply: 
##############################################################################
# mult matrices swap and B together of square size N and store in result.
	

		# alloc stack and store regs.
		sub $sp, $sp, 24
	        sw $ra, 0($sp)
	        sw $a0, 4($sp)
	        sw $a1, 8($sp)
	        sw $s0, 12($sp)
	        sw $s1, 16($sp)
	        sw $s2, 20($sp)

	        #setup for i loop

	        #setup for j loop

	        #setup for k loop

                # compute swap[i][k] address and load into $t3

                # compute B[k][j] address and load into $t4

		# invoke mul instruction

	        # increment k and jump back or exit

	        #increment j and jump back or exit

	        #increment i and jump back or exit

		# retore saved regs from stack
		lw $s2, 20($sp)
	        lw $s1, 16($sp)
		lw $s0, 12($sp)
		lw $a1, 8($sp)
		lw $a0, 4($sp)
	        lw $ra, 0($sp)
	
		# free stack and return
		add $sp, $sp, 24
		jr $ra


##############################################################################
matrix_print:
##############################################################################
		# alloc stack and store regs.
		sub $sp, $sp, 16
	        sw $ra, 0($sp)
	        sw $s0, 4($sp)
	        sw $s1, 8($sp)
		sw $a0, 12($sp)

		li $t0, 4 # size of array
	
		# do two for loops here

	        # setup to jump back and return

	        lw $ra, 0($sp)
	        lw $s0, 4($sp)
	        lw $s1, 8($sp)
		lw $a0, 12($sp)
		add $sp, $sp, 16
		jr $ra
	

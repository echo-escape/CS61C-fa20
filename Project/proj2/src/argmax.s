.globl argmax

.text
# =================================================================
# FUNCTION: Given a int vector, return the index of the largest
#	element. If there are multiple, return the one
#	with the smallest index.
# Arguments:
# 	a0 (int*) is the pointer to the start of the vector
#	a1 (int)  is the number of elements in the vector
# Returns:
#	a0 (int)  is the first index of the largest element
# Exceptions:
# - If the length of the vector is less than 1,
#   this function terminates the program with error code 77.
# =================================================================
argmax:

    # Prologue
    addi sp, sp, -12
    sw ra, 0(sp)
    sw s0, 4(sp)
    sw s1, 8(sp)

    mv t0, x0       # t0为循环的索引值
    mv s0, a0
    mv s1, a1

    li t1, 1
    blt s1, t1, exit_error

    mv t3, x0   # t3储存最大数字的索引

loop_start:
    beq t0, s1, loop_end
    slli t1, t0, 2
    add t2, s0, t1
    lw t1, 0(t2)    # t1为要比较的数字

    slli t5, t3, 2
    add t2, s0, t5
    lw t4, 0(t2)    # t4目前找到的最大索引的数字

    blt t4, t1, loop_continue

    addi t0, t0, 1
    mv a0, s0
    mv a1, s1
    j loop_start


loop_continue:
    addi t3, t0, 0
    addi t0, t0, 1
    mv a0, s0
    mv a1, s1
    j loop_start


exit_error:
    li a0, 78
    li a1, 93
    ecall


loop_end:
    mv a0, t3

    # Epilogue
    lw ra, 0(sp)
    lw s0, 4(sp)
    lw s1, 8(sp)
    addi sp, sp, 12

    ret

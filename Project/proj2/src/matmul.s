.globl matmul

.text
# =======================================================
# FUNCTION: Matrix Multiplication of 2 integer matrices
# 	d = matmul(m0, m1)
# Arguments:
# 	a0 (int*)  is the pointer to the start of m0 
#	a1 (int)   is the # of rows (height) of m0
#	a2 (int)   is the # of columns (width) of m0
#	a3 (int*)  is the pointer to the start of m1
# 	a4 (int)   is the # of rows (height) of m1
#	a5 (int)   is the # of columns (width) of m1
#	a6 (int*)  is the pointer to the the start of d
# Returns:
#	None (void), sets d = matmul(m0, m1)
# Exceptions:
#   Make sure to check in top to bottom order!
#   - If the dimensions of m0 do not make sense,
#     this function terminates the program with exit code 72.
#   - If the dimensions of m1 do not make sense,
#     this function terminates the program with exit code 73.
#   - If the dimensions of m0 and m1 don't match,
#     this function terminates the program with exit code 74.
# =======================================================
matmul:

    # Error checks
    li t0, 1
    blt a1, t0, exit_error_72
    blt a2, t0, exit_error_72
    
    blt a4, t0, exit_error_73
    blt a5, t0, exit_error_73

    bne a2, a4, exit_error_74

    # Prologue
    addi sp, sp, -32
    sw ra, 0(sp)
    sw s0, 4(sp)
    sw s1, 8(sp)
    sw s2, 12(sp)
    sw s3, 16(sp)
    sw s4, 20(sp)
    sw s5, 24(sp)
    sw s6, 28(sp)

    mv s0, a0       # 矩阵m0
    mv s1, a1       # m0_rows
    mv s2, a2       # m0_cols
    mv s3, a3       # 矩阵m1
    mv s4, a4       # m1_rows
    mv s5, a5       # m1_cols
    mv s6, a6       # 矩阵c

    li t0, 0        # 外层循环
    li t1, 0        


outer_loop_start:
    beq t0, s1, outer_loop_end


inner_loop_start:
    beq t1, s5, inner_loop_end

    mul t2, t0, s2
    slli t2, t2, 2
    add t3, s0, t2      # t3 point m0
    slli t2, t1, 2
    add t4, t2, s3      # t4 point m1

    

    # 传参
    mv a0, t3
    mv a1, t4
    mv a2, s2
    li a3, 1
    mv a4, s5

    addi sp, sp, -8
    sw t0, 0(sp)
    sw t1, 4(sp)

    call dot

    mv t2, a0

    lw t0, 0(sp)
    lw t1, 4(sp)
    addi sp, sp, 8  

    mul t3, t0, s5
    add t3, t3, t1
    slli t3, t3, 2
    add t3, s6, t3
    sw t2, 0(t3)

    addi t1, t1, 1
    j inner_loop_start


inner_loop_end:
    addi t0, t0, 1
    li t1, 0
    j outer_loop_start


outer_loop_end:


    # Epilogue
    lw ra, 0(sp)
    lw s0, 4(sp)
    lw s1, 8(sp)
    lw s2, 12(sp)
    lw s3, 16(sp)
    lw s4, 20(sp)
    lw s5, 24(sp)
    lw s6, 28(sp)
    addi sp, sp, 32
    
    
    ret


exit_error_72:
    li a0, 72
    li a7, 93
    ecall


exit_error_73:
    li a0, 73
    li a7, 93
    ecall


exit_error_74:
    li a0, 74
    li a7, 93
    ecall

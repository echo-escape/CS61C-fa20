.globl dot

.text
# =======================================================
# FUNCTION: Dot product of 2 int vectors
# Arguments:
#   a0 (int*) is the pointer to the start of v0
#   a1 (int*) is the pointer to the start of v1
#   a2 (int)  is the length of the vectors
#   a3 (int)  is the stride of v0
#   a4 (int)  is the stride of v1
# Returns:
#   a0 (int)  is the dot product of v0 and v1
# Exceptions:
# - If the length of the vector is less than 1,
#   this function terminates the program with error code 75.
# - If the stride of either vector is less than 1,
#   this function terminates the program with error code 76.
# =======================================================
dot:

    # Prologue
    addi sp, sp, -24
    sw ra, 0(sp)
    sw s0, 4(sp)
    sw s1, 8(sp)
    sw s2, 12(sp)
    sw s3, 16(sp)
    sw s4, 20(sp)

    mv t0, x0       # 循环
    mv s0, a0       # 数组0
    mv s1, a1       # 数组1
    mv s2, a2       # 数组长度
    mv s3, a3       # 数组0步长
    mv s4, a4       # 数组1步长

    mv t6, x0       # 储存结果

    li t1, 1
    blt s2, t1, exit_error_75
    blt s3, t1, exit_error_76
    blt s4, t1, exit_error_76


loop_start:
    beq t0, s2, loop_end

    mul t1, t0, s3      # t1数组0偏移量
    slli t1, t1, 2
    mul t2, t0, s4      # t2数组1偏移量
    slli t2, t2, 2
    add t1, s0, t1
    add t2, s1, t2
    lw t3, 0(t1)
    lw t4, 0(t2)
    mul t5, t3, t4
    add t6, t5, t6
    addi t0, t0, 1
    j loop_start


exit_error_75:
    li a0, 75
    li a7, 93
    ecall


exit_error_76:
    li a0, 76
    li a7, 93
    ecall


loop_end:
    mv a0, t6

    # Epilogue
    lw ra, 0(sp)
    lw s0, 4(sp)
    lw s1, 8(sp)
    lw s2, 12(sp)
    lw s3, 16(sp)
    lw s4, 20(sp)
    addi sp, sp, 24

    
    ret

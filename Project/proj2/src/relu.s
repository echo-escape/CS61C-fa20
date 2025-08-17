.globl relu

.text
# ==============================================================================
# FUNCTION: Performs an inplace element-wise ReLU on an array of ints
# Arguments:
# 	a0 (int*) is the pointer to the array
#	a1 (int)  is the number of elements in the array
# Returns:
#	None
# Exceptions:
# - If the length of the vector is less than 1,
#   this function terminates the program with error code 78.
# ==============================================================================
relu:
    # Prologue
    addi sp, sp, -12
    sw ra, 0(sp)
    sw s0, 4(sp)
    sw s1, 8(sp)    

    mv t0, x0
    mv s0, a0
    mv s1, a1

    li t1, 1
    blt s1, t1, exit_error


loop_start:
    beq t0, s1, loop_end        # 判断是否要循环下去
    slli t1, t0, 2              # 偏移量 t1 = t0 * 4
    add t2, s0, t1              # 当前位置
    lw t3, 0(t2)                # 加载数字

    bge t3, x0, loop_continue

    sw x0, 0(t2)
    j loop_start              # jal 是调用函数，j才是循环

loop_continue:
    addi t0, t0, 1
    j loop_start

exit_error:
    # 错误处理: 以代码 78 终止程序
    li a0, 78           # a0 = exit code
    li a7, 93           # a7 = syscall code for exit
    ecall

loop_end:
    # Epilogue
    lw ra, 0(sp)
    lw s0, 4(sp)
    lw s1, 8(sp)
    addi sp, sp, 12

	ret

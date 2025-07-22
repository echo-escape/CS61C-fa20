.globl factorial

.data
n: .word 0

.text
main:
    la t0, n
    lw a0, 0(t0)
    jal ra, factorial

    addi a1, a0, 0
    addi a0, x0, 1
    ecall # Print Result

    addi a1, x0, '\n'
    addi a0, x0, 11
    ecall # Print newline

    addi a0, x0, 10
    ecall # Exit

factorial:
    # YOUR CODE HERE
    beq a0, x0, return_one
    addi t0, x0, 1

loop:
    mul t0, t0, a0
    addi a0, a0, -1
    bgt a0, x0, loop

    add a0, t0, x0
    jr ra

return_one:
    addi a0, x0, 1

    jr ra


    
        



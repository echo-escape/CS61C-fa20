.globl write_matrix

.text
# ==============================================================================
# FUNCTION: Writes a matrix of integers into a binary file
# FILE FORMAT:
#   The first 8 bytes of the file will be two 4 byte ints representing the
#   numbers of rows and columns respectively. Every 4 bytes thereafter is an
#   element of the matrix in row-major order.
# Arguments:
#   a0 (char*) is the pointer to string representing the filename
#   a1 (int*)  is the pointer to the start of the matrix in memory
#   a2 (int)   is the number of rows in the matrix
#   a3 (int)   is the number of columns in the matrix
# Returns:
#   None
# Exceptions:
# - If you receive an fopen error or eof,
#   this function terminates the program with error code 93.
# - If you receive an fwrite error or eof,
#   this function terminates the program with error code 94.
# - If you receive an fclose error or eof,
#   this function terminates the program with error code 95.
# ==============================================================================
write_matrix:

    # Prologue
    addi sp, sp, -24
    sw ra, 0(sp)
    sw s0, 4(sp)
    sw s1, 8(sp)
    sw s2, 12(sp)
    sw s3, 16(sp)
    sw s4, 20(sp)

    mv s0, a0           # filepath
    mv s1, a1           # s1 point to matrix
    mv s2, a2           # s2 is rows
    mv s3, a3           # s3 is cols
    li s4, 0            # s4 is descriptor

    mv a1, s0           # fopen and check
    li a2, 1
    jal fopen
    li t0, -1
    beq a0, t0, exit_error_93
    mv s4, a0

    mv a1, s4           # write rows and cols
    addi sp, sp, -8           
    sw s2, 0(sp)
    sw s3, 4(sp)
    mv a2, sp
    li a3, 2    
    li a4, 4    
    jal fwrite
    li t0, 2
    bne a0, t0, exit_error_94
    addi sp, sp, 8

    mv a1, s4          # write matrix
    mv a2, s1
    mul a3, s2, s3
    li a4, 4    
    jal fwrite
    mul t0, s2, s3
    bne a0, t0, exit_error_94

    mv a1, s4          # close
    jal fclose
    li t0, 0
    bne a0, t0, exit_error_95



    # Epilogue
    lw ra, 0(sp)
    lw s0, 4(sp)
    lw s1, 8(sp)
    lw s2, 12(sp)
    lw s3, 16(sp)
    lw s4, 20(sp)
    addi sp, sp, 24


    ret


exit_error_93:
    li a1, 93
    jal exit2


exit_error_94:
    li a1, 94
    jal exit2


exit_error_95:
    li a1, 95
    jal exit2

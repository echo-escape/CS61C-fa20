.globl abs
.text

abs:
    bge a0, x0, end_abs

    sub a0, x0, a0

end_abs:
    ret
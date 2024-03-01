.global rstr_s

# Reverse a string iteratively

strlen_s:
    addi sp, sp, -16
    sd ra, (sp)
    
    li t0, 0 # len = 0
    while:
        lb t1, (a1)
        beq t1, zero, done
        addi t0, t0, 1
        addi a1, a1, 1
        j while
    done:
        mv a0,t0
        
    ld ra, (sp)
    addi sp, sp, 16
    ret

rstr_s:
    addi sp, sp, -32
    sd ra, (sp)

    sd a0, 8(sp)
    
    call strlen_s
    mv t0, a0       # t0 = strlen(a1)

    ld a0, 8(sp)

    addi a1, a1, -1 # a1 is at \0, move previous character and iterate
    
    li t1, 0
    loop:
        beq t1, t0, return
        lb t2, (a1)     # temp = src[len-i]
        sb t2, (a0)     # dest[i] = t2
        addi a0, a0, 1
        addi a1, a1, -1
        addi t1, t1, 1
        j loop   
    return:
        sb zero, (a0)
        ld ra, (sp)
        addi sp, sp, 32    
        ret
    

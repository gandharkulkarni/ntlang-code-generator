.global rstr_rec_s

# Reverse a string recursively
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

rstr_rec:
    addi sp, sp, -32
    sd ra, (sp)

    add t2, a1, t0  
    lb t3, (t2)     # t3 = src[i]

    add t4, a0, t1
    beq t3, zero, terminate_str
    
    sb t3, (t4)
    
    addi t0, t0, -1
    addi t1, t1, 1
    call rstr_rec
    j return
    terminate_str:
        sb zero, (t4)
    return:
    ld ra, (sp)
    addi sp, sp, 32
    ret
    


rstr_rec_s:
    addi sp, sp, -16
    sd ra, (sp)

    sd a0, 8(sp)
    sd a1, 16(sp)

    call strlen_s
    mv t0, a0       # t0 = strlen(src)
    addi t0, t0, -1 # len-1

    ld a0, 8(sp)
    ld a1, 16(sp)

    mv t1, zero     # t1 = 0

    call rstr_rec

    ld ra, (sp)
    addi sp, sp, 16
    ret

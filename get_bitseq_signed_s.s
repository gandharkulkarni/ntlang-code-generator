.global get_bitseq_signed_s
.global get_bitseq_s

get_bitseq_signed_s:
    addi sp, sp, -16
    sd ra, (sp)
    
    sub t0, a2, a1  # len =  end- start
    addi t0, t0, 1  # len +=1

    li t1, 32
    sub t1, t1, t0  # t1 - shift_amt

    sd t1, 8(sp)
    
    call get_bitseq_s
    mv t0, a0

    ld t1, 8(sp)
    sllw t0, t0, t1
    sra t0, t0, t1

    mv a0, t0

    ld ra, (sp)
    addi sp, sp, 16 
    ret

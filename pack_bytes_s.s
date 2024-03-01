.global pack_bytes_s

pack:
    addi sp, sp, -16
    sd ra, (sp)
    
    slli t0, t0, 8
    or t0, t0, a0

    ld ra, (sp)
    addi sp, sp, 16
    ret

pack_bytes_s:
    addi sp, sp, -16
    sd ra, (sp)
    
    li t0, 0
    mv t0, a0

    mv a0, a1
    call pack

    mv a0, a2
    call pack
     
    mv a0, a3
    call pack
    
    mv a0, t0

    ld ra, (sp)
    addi sp, sp, 16
    ret


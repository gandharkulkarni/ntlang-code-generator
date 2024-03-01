.global unpack_bytes_s

unpack_bytes_s:
    li t0, 0
    li t1, 4
    for:
        beq t0, t1, done    # break if i==4
        
        andi t4, a0, 0xFF    

        slli t2, t0, 2
        add t2, a1, t2
        sb t4, (t2)

        srli a0, a0, 8
        
        addi t0, t0, 1
        j for
    done:
    mv a0, a1
    ret

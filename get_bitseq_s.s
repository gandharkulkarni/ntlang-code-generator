.global get_bitseq_s

get_bitseq_s:
    sub t0, a2, a1  # len  = end - start
    addi t0, t0, 1  # len  = len + 1

    srl t1, a0, a1  # val = num >> start

    li t3, 1
    sll t2, t3, t0
    addi t2, t2, -1

    li t3, 32
    beq t0, t3, mask
    j done
    mask:
        li t2, 0xFFFFFFFF
    done:
    and t1, t1, t2
    mv a0, t1
    ret

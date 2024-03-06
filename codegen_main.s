.global main
.global atoi
.global printf

.data
result_string:
    .string "%d (0x%X)\n"

.text

main:

    addi sp, sp, -128
    sd ra, 0(sp)

    # Initializing stack values as 0
    li t0, 0 
    sd t0, 40(sp)
    sd t0, 48(sp)
    sd t0, 56(sp)
    sd t0, 64(sp)
    sd t0, 72(sp)
    sd t0, 80(sp)
    sd t0, 88(sp)
    sd t0, 96(sp) 

    li t0, 1
    sub a0, a0, t0              # argc = argc - 1

    # Save argv to a1
    addi a1, a1, 8

    li a2, 0
    li a4, 5
    
    loop:
        
        slli t6, a2, 3          # i = i* 8
        add t6, a1, t6          # t6 = base + i
        ld a3, (t6)             # load a3 =  args[i]

        sd a0, 8(sp)             # store a0 on stack
        sd a1, 16(sp)            # store a1 on stack
        sd a2, 24(sp)
        sd a4, 32(sp)
        
        mv a0, a3
        call atoi

        ld a2, 24(sp)
        ld a4, 32(sp)
        
        slli t1, a4, 3          # i = i* 8
        add t0, sp, t1          # t7 = sp + i*8
        sd a0, (t0)             # store a0 at new stack location
        
        addi a2, a2, 1
        addi a4, a4, 1
        ld a0, 8(sp)             # restore a0 from stack
        ld a1, 16(sp)            # restore a1 from stack
        
        beq a2, a0, end_loop    # end_loop if i==argc
        j loop

        
    
    end_loop:    
        
    ld a0, 40(sp)
    ld a1, 48(sp)
    ld a2, 56(sp)
    ld a3, 64(sp)
    ld a4, 72(sp)
    ld a5, 80(sp)
    ld a6, 88(sp)
    ld a7, 96(sp)


    call codegen_func_s

    mv a2, a1
    mv a1, a0
    la a0, result_string

    call printf
    
    ld ra, 0(sp)
    addi sp, sp, 128

    ret
    

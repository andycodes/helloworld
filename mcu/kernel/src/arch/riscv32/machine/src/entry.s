.equ STACK_SIZE, 8192

.global _entry

_entry:
    # set up a stack for C.
    # with a 2048-byte stack per CPU.
    # sp = stacks + (hartid * 2048)
    la sp, stacks
    li a0, 1024*2
    csrr a1, mhartid
    addi a1, a1, 1
    mul a0, a0, a1
    add sp, sp, a0
    call start              

park:
    wfi
    j park

stacks:
    .skip STACK_SIZE                # 分配堆疊空間


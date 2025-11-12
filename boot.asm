[bits 16]

global start

start:
    cli

    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax

    mov sp, 0x7C00

    sti

    extern main_c
    call main_c

    cli
    hlt
    jmp $

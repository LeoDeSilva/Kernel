[org 0x7c00]
 
KERNEL_OFFSET equ 0x1000 
mov [BOOT_DRIVE], dl ; store boot drive from DL in BOOT_DRIVE

mov bp, 0x9000 ; setup the stack
mov sp, bp

mov bx, MSG_REAL_MODE
call print_string

call load_kernel
call switch_to_pm

jmp $


%include "print_string.asm"
%include "print_string_pm.asm"
%include "disk_load.asm"
%include "print_hex.asm"
%include "switch_to_pm.asm"
%include "gdt.asm"

[bits 16]
load_kernel:
    mov bx, MSG_LOAD_KERNEL
    call print_string

    mov bx, KERNEL_OFFSET ; setup parameters for disk_load routine
    mov dh, 15 ; load the first 15 sectors (excluding boot sector) to address KERNEL_OFFSET
    mov dl, [BOOT_DRIVE]
    call disk_load

    mov bx, MSG_LOADED_KERNEL
    call print_string

    ret

[bits 32]

BEGIN_PM:
    mov ebx, MSG_PROT_MODE
    call print_string_pm

    call KERNEL_OFFSET ; jump to address of loaded kernel code 
    jmp $

BOOT_DRIVE db 0
MSG_REAL_MODE db "Started in 16-bit Real Mode.", 0
MSG_PROT_MODE db "Successfully landed in 32-bit protected mode.", 0
MSG_LOAD_KERNEL db "Loading Kernel into memory.", 0
MSG_LOADED_KERNEL db "Loaded Kernel into memory.", 0
TESTING db "testing...",0 

times 510-($-$$) db 0
dw 0xaa55
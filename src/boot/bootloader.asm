[org 0x7c00]

KERNEL_OFFSET equ 0x1000
mov [BOOT_DRIVE], dl

mov bp, 0x9000
mov sp, bp

call load_kernel
call enter_protected_mode

jmp $

%include "print_string.asm"
%include "protected_mode.asm"
%include "disk.asm"
%include "gdt.asm"

[bits 16]
load_kernel:
    mov bx, KERNEL_OFFSET
    mov dh, 15 ; load 15 sectors excluding bootsec
    mov dl, [BOOT_DRIVE]
    call disk_read

    ret

[bits 32]
PROTECTED_MODE_EP:
    call KERNEL_OFFSET
    jmp $

BOOT_DRIVE: db 0

times 510-($-$$) db 0
dw 0xaa55

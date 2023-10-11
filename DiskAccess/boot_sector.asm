[org 0x7c00]

mov [BOOT_DRIVE], dl ; BIOS stores our boot drive in DL

mov bp, 0x8000 
mov sp, bp

mov bx, 0x9000 ; Load 2 sectors to 0x0000(ES):0x9000 (BX) from the boot-disk
mov dh, 3 
mov dl, [BOOT_DRIVE]

call disk_load

mov dx, [0x9000] ; Print out the first loaded word 
call print_hex 

mov dx, [0x9000 + 512] ; Print first word from second sector
call print_hex

mov dx, [0x9000 + 1024] ; Print first word from second sector
call print_hex

jmp $

%include "debug.asm"
%include "disk.asm"

BOOT_DRIVE: db 0

times 510-($-$$) db 0
dw 0xaa55

; as bios will load only the first 512-byte sector from the disk
; adding more sectors by repeating numbers the disk_load can be tested
times 256 dw 0xdada
times 256 dw 0xface
times 256 dw 0xbaba

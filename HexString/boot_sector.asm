[org 0x7c00]

mov dx, [HEX_BYTE]
call print_hex

jmp $

%include "debug.asm"

HEX_BYTE
  dw 0xfad0

times 510-($-$$) db 0
dw 0xaa55

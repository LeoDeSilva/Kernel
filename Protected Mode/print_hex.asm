print_hex:
  pusha
  mov bx, HEX_OUT
  
  mov cl, dh
  call print_byte
  add bx, 2 ; add 2 last 2 bits of HEX_OUT

  mov cl, dl
  call print_byte

  mov bx, HEX_OUT
  call print_string
  popa
  ret

print_byte:
  pusha

  mov al, cl
  shr al, 4 ;; 4 MSB of byte
  call print_nibble
  inc bx

  mov al, cl
  and al, 0x0f ;; 4 LSB of byte
  call print_nibble

  popa
  ret

print_nibble:
  pusha
  add al, '0'

  cmp al, '9' ;; if char > digit repr, begin letters 
  jg hex_letter
  jmp skip_hex_letter

  hex_letter:
    add al, 7

  skip_hex_letter:
  mov [bx+2], al

  popa
  ret

HEX_OUT:
  db '0x0000', 0

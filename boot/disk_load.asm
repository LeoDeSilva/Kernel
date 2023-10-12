;TODO: Fix DISC READ ERROR
[bits 16]
; load DH sectors to ES:BX from Drive DL
disk_load: 
  push dx ; store dx pm stack to recall how many sectors to be read

  mov ah, 0x02

  mov al, dh   ; read DH sectors
  mov ch, 0x00 ; select cylinder 0
  mov dh, 0x00 ; select head 0
  mov cl, 0x02 ; start reading from second sector (after boot sector)

  int 0x13
  jc disk_error

  pop dx 
  cmp dh, al ; if AL (sectors read) != DH (sectors expected)
  jne disk_error 


  ret

disk_error:
  mov bx, DISK_ERROR_MSG
  call print_string
  jmp $

DISK_ERROR_MSG: db "Disk Read Error!", 0

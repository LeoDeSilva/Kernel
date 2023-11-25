; ### int 0x13 description ###
; ah:    0x02
; al:    number of sectors to read
; ch:    track/cylinder number
; cl:    sector number (0x02 - read after boot sector)
; dh:    head number
; dl:    drive number
; es:bx: pointer to buffer

; Return:
;   ah: status
;   al: number of sectors read
;   cf: 0 (successful), 1 (error)

; bx: buffer pointer (offset)  
; dh: number of sectors to read
; dl: drive number
disk_read:
    push dx 
    
    mov ah, 0x02

    mov al, dh 
    mov ch, 0x00
    mov dh, 0x00
    mov cl, 0x02 
    
    int 0x13
    jc .disk_error

    pop dx
    cmp dh, al 
    jne .disk_error

    ret

    .disk_error
        mov bx, DISK_ERROR_MSG
        call print_string
        jmp $

DISK_ERROR_MSG: db "Couldn't Read Disk!", 0

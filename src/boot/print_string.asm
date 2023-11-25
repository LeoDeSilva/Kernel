; 16-Bit Real Mode
[bits 16]

; bx: address of the first char of a null terminated string
print_string:
    pusha
    mov ah, 0x0e
    .print_string_loop:
        mov al, [bx] 
        
        cmp al, 0
        je .print_string_end

        int 0x10
        inc bx

        jmp .print_string_loop

    .print_string_end:
        popa
        ret

; 32-Bit Protected Mode 
[bits 32]

VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f 

; ebx: address of the first char of a null terminated string
print_string_pm:
    pusha
    mov edx, VIDEO_MEMORY

    .print_string_pm_loop:
        mov al, [ebx]
        mov ah, WHITE_ON_BLACK

        cmp al, 0
        je .print_string_pm_end

        mov [edx], ax 
        add ebx, 1 
        add edx, 2

        jmp .print_string_pm_loop

    .print_string_pm_end:
        popa
        ret

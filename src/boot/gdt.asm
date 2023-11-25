; structure as defined in the book "Writing an OS From Scratch"
; code and data segments overlap - nullifies privilage levels 
; (can be remedied in C) however a simple structure to define and understand

gdt_start:
    null_descriptor: 
        dd 0x0
        dd 0x0

    code_descriptor:
        ; base = 0x0, limit = 0xfffff
        ; 1st flags: (present)1 (privilege)00 (descriptor type)1 -> 1001b
        ; type flags: (code)1 (conforming)0 (readable)1 accessed(0) -> 1010b
        ; 2nd flags: (granularity)1 (32 bit default)1 (64 bit seg)0 (AVL)0 -> 1100b

        dw 0xffff ; limit (bits 0-15)
        dw 0x0 ; base (bits 0-15)
        db 0x0 ; base (16-23)
        db 10011010b ; 1st flags, type flags
        db 11001111b ; 2nd flags, Limit (bits 16-19)
        db 0x0 ; base (bits 24-31)

    data_descriptor:
        ; Same as code semgnet save type flags
        ; type flags: (code)0 (expand down)0 (writable)1 (accessed)0 -> 0010b
        dw 0xffff ; limit (bits 0-15)
        dw 0x0 ; base (bits 0-15)
        db 0x0 ; base (bits 16-23)
        db 10010010b ; 1st flags, type flags
        db 11001111b ; 2nd flags, limit (bits 16-19)
        db 0x0 ; base (bits 24-31)

gdt_end: 

gdt_descriptor:
    dw gdt_end - gdt_start - 1 ; size of GDT (always less 1 of true size)
    dd gdt_start ; start address of GDT

; define constants for GDT segment descriptor offsets 
; thus can set segment registers e.g. NULL: 0x0, CODE: 0x08, DATA: 0x10
CODESEG equ code_descriptor - gdt_start
DATASEG equ data_descriptor - gdt_start


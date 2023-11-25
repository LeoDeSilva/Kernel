[bits 16]

enter_protected_mode:
    cli ; clear interrupts until vector table initialised    
    lgdt [gdt_descriptor]

    ; set first bit of cr0 to switch to pm
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax

    jmp CODESEG:start_protected_mode ; far jump to flush cache 

[bits 32]

start_protected_mode:
    mov ax, DATASEG ; set segment registers to DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000
    mov esp, ebp

    call PROTECTED_MODE_EP

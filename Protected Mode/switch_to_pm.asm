[bits 16]

switch_to_pm:
    cli ; clear interrupts until pm interrupt vector setup
    lgdt [gdt_descriptor]

    mov eax, cr0 ; set bit 1 of cr0 to swtich to pm
    or eax, 0x1
    mov cr0, eax

    jmp CODE_SEG:init_pm ; far jump to flush cache

[bits 32]

init_pm:
    mov ax, DATA_SEG      ; Now in PM , our old segments are meaningless ,
    mov ax, DATA_SEG ; set segment registers to DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000 ; update stack positions to top of free space
    mov esp, ebp

    call BEGIN_PM
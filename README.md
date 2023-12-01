# README
A C kernel and bootloader extending on the book "Writing an Operating System from Scratch". An exploration for a project that will ultimately become my NEA (Non Exam Assessment) for Computer Science A Level.

# Reminders
* [x] TODO: remove print_hex function from print_string.asm
* [ ] Implement memset function into mem.h (already defined in ./Honeycomb) & used for initializing 2d array with {{0}}
* [x] Rewrite VGA Driver and io.h into functions like VGA_char_set() VGA_fill() and readline() or kprint() etc.  
* [ ] Logically plan file structure from the ground up, combining header files into a single std.h file
* [x] Reimpliment cursor logic, scrolling and printing: handling cursor dissapearing when scrolling with ENTER
* [x] Logically implement driver & display colours
* [ ] Implement ELF File format & Write to disk functions
    * [ ] Rewrite CLI commands as 'bin/ls' files

# Known Issues
* Cursor dissapears when scrolling screen on bottom line triggered by Enter - include offset check
* Reimplement screen and io drivers, reorganise file structure & implement colours
* Organise and better structure filesystem with libc, libararies abstracting the drivers and cpu  

## Implementation
* drivers
    * VGA.h
        * VGA_set_char()
        * VGA_fill_screen()
        * VGA_set_col()
    * keyboard.h
    * PIT.h
        * PIT_get_ticks()
        * PIT_create_event(*(void)fptr(), int)
    * ports.h
        * inb()
        * outb()
    * events.h
        * EVENT_get_events()
        * Event_get_count()
        * EVENT_add_event()
        * Event_next_event()
* lib
    * stdlib.h
        * io.h
            * readline()
            * kprint()
        * mem.h
            * memcpy()
            * memset()
        * types.h
            * to_string()
            * to_char()
    * libc.h 
        * *low level abstractions rather than utility functions*
        * e.g. execvm() sys calls
* boot
    * bootloader.asm
    * disk_read.asm
    * gdt.asm
    * kernel_entry.asm?
    * protected_mode.asm
    * print_string.asm 
* cpu
    * interrupt.asm
    * idt.h
    * isr.h
* kernel
    * kernel.c

```C
int readline() {
    for (;;) {
        while (EVENT_get_count() > 0) {
            union Event e = EVENT_next_event();
            if (e.type != NIL) { ... }
        }
    }
    return 0;
}

int main() {
    VGA_set_col(WHITE_ON_BLUE);

    PIT_create_event(&update, 10);

    for (;;) {
        char in_line[256] = readline();
        kprint(in_line);
        kprint(to_string('!'));
    }
}
```


C_SOURCES = $(wildcard src/kernel/*.c)
HEADERS = $(wildcard src/kernel/*.h)
OBJ = $(C_SOURCES:.c=.o)

CFLAGS = -g -m32 -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs\
		 -Wall -Wextra -Werror

all: os-image

run: all
	qemu-system-x86_64 -drive format=raw,file=os-image

os-image: src/boot/bootloader.bin src/kernel/kernel.bin
	cat $^ > os-image
	qemu-img resize -f raw os-image +20K

src/kernel/kernel.bin : src/boot/kernel_entry.o ${OBJ}
	i686-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary -e main

%.o : %.c ${HEADERS}
	i686-elf-gcc ${CFLAGS} -ffreestanding -c $< -o $@ 

%.o : %.asm 
	nasm $< -f elf -o $@

%.bin : %.asm
	nasm $< -f bin -I 'src/boot/' -o $@

clean: 
	find . -type f -name '*.bin' | xargs rm
	find . -type f -name '*.o' | xargs rm

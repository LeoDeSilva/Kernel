# create list of C files and their .o object counterparts
C_SOURCES = $(wildcard kernel/*.c drivers/*.c cpu/*.c libc/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h cpu/*.h libc/*.h)
OBJ = $(C_SOURCES:.c=.o cpu/interrupt.o)

all: os-image

run: all
	qemu-system-x86_64 os-image

os-image: boot/boot_sector.bin kernel/kernel.bin
	cat $^ > os-image
	qemu-img resize os-image +20K

kernel/kernel.bin : boot/kernel_entry.o ${OBJ}
	i686-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary -e main

%.o : %.c ${HEADERS}
	i686-elf-gcc -ffreestanding -c $< -o $@ 

%.o : %.asm 
	nasm $< -f elf -o $@

%.bin : %.asm
	nasm $< -f bin -I 'boot/' -o $@

clean: 
	rm -fr *.bin *.o *.dis os-image *.map 
	rm -fr kernel/*.o boot/*.bin drivers/*.o kernel/*.dis kernel/*.bin cpu/*.o libc/*.o

kernel/kernel.dis: kernel/kernel.bin
	ndisasm -b 32 $> > $@

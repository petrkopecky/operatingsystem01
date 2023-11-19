# $@ = target file
# $< = first dependency
# $^ = all dependencies


C_SOURCES = $(wildcard kernel/*.c drivers/*.c cpu/*.c)
HEADERS = $(wildcard kernel/*.h  drivers/*.h cpu/*.h)


#C_SOURCES = $(wildcard kernel/kernel.c )
#HEADERS = $(wildcard kernel/kernel.h )

OBJ_FILES = ${C_SOURCES:.c=.o cpu/interrupt.o}

# First rule is the one executed when no parameters are fed to the Makefile
all:clean run

# Notice how dependencies are built as needed
kernel.bin: boot/kernel_entry.o ${OBJ_FILES}
#ld -no-PIE -m elf_i386 -o $@ -T linker.lds -Ttext 0x1000 $^ --oformat binary
	ld  -m elf_i386 -o $@ -T linker.lds -Ttext 0x1000 $^ --oformat binary

os-image.bin: boot/mbr.bin kernel.bin
	cat $^ > $@


%.o: %.asm
	nasm $< -f elf -o $@

#kernel.o: kernel/kernel.c
#gcc -m32 -fno-PIC  -ffreestanding -c $< -o $@
#gcc -m32 -fno-PIC -ffreestanding -c $< -o $@

%.o: %.c ${HEADERS}	
	gcc -m32 -fno-PIC -ffreestanding -c $< -o $@

# Disassemble
#kernel.dis: kernel.bin
#	ndisasm $< > $@

%.bin: %.asm
	nasm $< -f bin -o $@



run: os-image.bin
	bochs -qf ./bochs.cfg -rc ./bochsrc

echo: os-image.bin
	echo $<

clean:
	$(RM) *.bin *.o *.dis *.elf
	$(RM) kernel/*.o
	$(RM) boot/*.o boot/*.bin
	$(RM) drivers/*.o
	$(RM) cpu/*.o

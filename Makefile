build: boot.asm boot.c linker.ld
	nasm -f elf32 boot.asm -o boot.o

	gcc -m16 -Os -ffreestanding -fno-pic -c boot.c -o boot_c.o

	ld -m elf_i386 -T linker.ld -o boot.bin boot.o boot_c.o

run: build
	qemu-system-i386 -fda boot.bin

img: build
	dd if=boot.bin of=boot.img bs=512 count=1 conv=notrunc

clean:
	rm -f *.o boot.bin boot.img
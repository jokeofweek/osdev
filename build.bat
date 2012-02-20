nasm -f aout -o start.o start.asm
gcc -c kernel.c -o kernel.o
C:\djgpp\bin\ld -T link.ld -o kernel.bin start.o kernel.o

del images\boot.img
copy images\original.img images\boot.img

imdisk.exe -a -f images\boot.img -s 1440K -m K:

copy kernel.bin K:\

imdisk.exe -D -m K:

pause
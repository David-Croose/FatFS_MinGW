all:
	gcc -g -o demo.exe diskio.c ff.c ffsystem.c ffunicode.c driver/ramdisk.c main.c -I./driver/ -I.

test:
	gcc -g -o test.exe diskio.c ff.c ffsystem.c ffunicode.c driver/ramdisk.c -I./driver/ -I. -I./test

clean:
	rm -f demo test

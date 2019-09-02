.PHONY: all test clean

all:
	gcc -g -o demo.exe -Wall diskio.c ff.c ffsystem.c ffunicode.c driver/ramdisk.c main.c -I./driver/ -I.

test:
	gcc -g -o test.exe -Wall diskio.c ff.c ffsystem.c ffunicode.c driver/ramdisk.c test/test.c -I./driver/ -I. -I./test

clean:
	rm -f demo.exe test.exe


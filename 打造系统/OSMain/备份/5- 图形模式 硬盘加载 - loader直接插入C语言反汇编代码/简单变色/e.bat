gcc -m32 -fno-asynchronous-unwind-tables -s -c -o write.o write.c 
objconv -fnasm write.o -o write.asm

all:
	rm -f main.exe
	gcc -Isrc/Include -Lsrc/lib -o main main.c gfx/gfx.c cpu/cpu.c -lmingw32 -lSDL2main -lSDL2 
	./main.exe

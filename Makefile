# =================
# VARIABLES SECTION
# =================

CC       = gcc							# compiler
CFLAGS   = -Wall -g -lmingw32 -lSDL2main -lSDL2 -std=c99			# compilation flags

EXE		= chip
SRCS   	 = main.c gfx/gfx.c cpu/cpu.c	# source code
OBJS	= main.o gfx.o cpu.o
LIBR 	 = -Isrc/Include -Lsrc/lib -lmingw32 -lSDL2main -lSDL2 
.PHONY: all clean


# gfx/gfx.o: gfx/gfx.c
# 	$(CC) -c gfx/gfx.c
# cpu/cpu.o: cpu/cpu.c
# 	$(CC) -c cpu/cpu.c
# main.o: main.c
# 	$(CC) -c main.c

all: $(OBJ)
	$(CC)  -o $(EXE)  $(SRCS)  $(LIBR) -g
	rm -f $(OBJS) 
	./chip.exe

clean:
	rm -f $(OBJS) 


# # =================
# # VARIABLES SECTION
# # =================

# CC       = gcc							# compiler
# CFLAGS   = -Wall -g -lmingw32 -lSDL2main -lSDL2 -std=c99			# compilation flags

# SRCS   	 = main main.c gfx/gfx.c cpu/cpu.c	# source code
# OBJS     = main.o 						# object files (compiled source code)
# TARGETS  = main.exe						# final executable to produce





# # ===============
# # TARGETS SECTION
# # Note: general idea is to specify intermediate requirements to get to end goal. 
# #
# #
# # Ex: I need file A. File A -> File B. File B -> File C, File D. 
# # File C changed since last time. So recreate file B from C and D. 
# # Then, recreate file A from B.
# # ===============


# # Meaning: update main (executable) when main.o calculations.o (object files) change
# # $@ is the target (in this case: main.exe)
# # $^ are ALL the dependencies (in this case: main.o cpu.o gfx.o)
# main.exe: $(OBJS)
# 	$(CC) $(CFLAGS) -o $@ $^


# main.o:
# 	$(CC) $(CFLAGS) -c $(SRCS)
# # Syntax: target: dependencies
# # Meaning: when we run `make all`, get up to date `main.exe` (dependency)
# all: $(TARGETS)
# 	gcc -Isrc/Include -Lsrc/lib -g -o main main.c gfx/gfx.c cpu/cpu.c -lmingw32 -lSDL2main -lSDL2 

# # Meaning: clean up all object files and executables
# clean:
# 	rm -f $(OBJS) $(TARGETS)

# # Meaning: don't look for files named clean and all. I'm treating them as commands
# .PHONY: all clean
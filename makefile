CFLAGS=-std=c++17 -Wall -Wextra -Werror
all:
	g++ src/main.cpp src/chip8.cpp src/input.cpp src/cpu.cpp src/display.cpp src/memory.cpp src/graphics.cpp src/audio.cpp src/emulator.cpp -o chip8 $(CFLAGS) -I/${CURDIR}/deps/SDL2 -D_REENTRANT -lSDL2 -I/${CURDIR}/include
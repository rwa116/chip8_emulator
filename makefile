CFLAGS=-std=c++17 -Wall -Wextra -Werror
all:
	g++ src/main.cpp src/chip8.cpp src/cpu.cpp src/display.cpp src/memory.cpp src/graphics.cpp src/emulator.cpp -o chip8 $(CFLAGS) `sdl2-config --cflags --libs` -I/${CURDIR}/include
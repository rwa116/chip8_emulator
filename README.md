# C++ Chip-8 Interpreter

This repository contains an implementation of a Chip-8 Interpreter and is written in C++. 

<div>
<img alt="sp_inv" src="https://github.com/rwa116/chip8_emulator/assets/90480990/8509f4c2-de30-409c-a47d-3b1f49603d33.gif" width="400"/>
<img alt="ufo" src="https://github.com/rwa116/chip8_emulator/assets/90480990/6573aa1f-3ee7-458c-9728-1541dbfbc6f4.gif" width="400" />
</div>

# Dependencies

This project uses SDL2 for graphics display, audio output, and key input. The SDL2 library is included in this repository in the `deps/` subdirectory.
This project uses make for build management, and g++ for compilation.

# Using the Interpreter

To build the interpreter simply run `./make` from the main project directory.

After this you can use `./chip8 <path_to_rom>` to run a rom. 

Some games and test roms are icluded in the `roms/` and `/tests/` subdirectories. All roms are taken from other public repositories are are not my own: 
https://github.com/Timendus/chip8-test-suite, and https://github.com/kripod/chip8-roms.


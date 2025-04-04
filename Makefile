CFLAGS = -Wall -Wextra -pedantic -std=c99
LDFLAGS = -lSDL2 -lSDL2_ttf

gb-emulator: src/main.c
	gcc -g src/bus.c src/cart.c src/cpu_proc.c src/cpu_util.c src/cpu.c src/emu.c src/instructions.c src/main.c src/ppu.c src/timer.c -o gb-emulator $(CLFAGS) $(LDFLAGS) `sdl2-config --cflags --libs`

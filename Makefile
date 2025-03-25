CFLAGS = -Wall -Wextra -pedantic -std=c99
LDFLAGS = -lSDL2 -lSDL2_ttf

gb-emulator: src/main.c
	gcc src/bus.c src/cart.c src/cpu.c src/emu.c src/main.c src/ppu.c src/timer.c -o gb-emulator $(CLFAGS) $(LDFLAGS) `sdl2-config --cflags --libs`
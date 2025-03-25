#include "../includes/cart.h"
#include "../includes/cpu.h"
#include "../includes/emu.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

/*
    Emulator components:

    |Cartridge|
    |CPU|
    |Address Bus|
    |PPU|
    |Timer|

*/

static emu_context ctx;

int emu_run(int argc, char **argv) {
    if(argc < 2) {
        printf("Usage: emu run <rom_file\n");
        return -1;
    }

    if(!cart_load(argv[1])) {
        printf("Failed to load ROM file: %s\n", argv[1]);
        return -1;
    }

    printf("Running...\n");
    SDL_Init(SDL_INIT_VIDEO);
    printf("SDL_Init\n");
    TTF_Init();
    printf("TTF_Init\n");

    cpu_init();

    ctx.running = true;
    ctx.paused = false;
    ctx.ticks = 0;

    while(ctx.running) {
        if(ctx.paused) {
            SDL_Delay(10);
            continue;
        }
        if(!cpu_step()) {
            printf("CPU stopped!\n");
            return -1;
        }
        ctx.ticks++;
    }

    return 0;
}
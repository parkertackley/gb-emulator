#pragma once

#include "common.h"
#include "instructions.h"

// CPU registers -> https://gbdev.io/pandocs/CPU_Registers_and_Flags.html
typedef struct {
    uint8_t a;
    uint8_t f;
    uint8_t b;
    uint8_t c;
    uint8_t d;
    uint8_t e;
    uint8_t h;
    uint8_t l;
    uint16_t pc;
    uint16_t sp;
} cpu_registers;

// CPU struct
typedef struct {
    cpu_registers regs;
    
    uint16_t fetched_data;
    uint16_t mem_dest;
    bool dest_is_mem;
    uint8_t cur_opcode;
    instruction *cur_inst;

    bool halted;
    bool stepping;
} cpu_context;

void cpu_init();
bool cpu_step();

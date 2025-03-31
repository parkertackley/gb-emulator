#pragma once

#include "common.h"

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

typedef struct {
    cpu_registers regs;
    uint16_t fetch_data;
    uint16_t mem_dest;
    uint8_t cur_opcode;

    bool halted;
    bool stepping;
} cpu_context;

void cpu_init();
bool cpu_step();

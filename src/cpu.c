#include "../includes/cpu.h"
#include "../includes/bus.h"
#include "../includes/emu.h"

cpu_context ctx = {0};

// Set program counter to 0x100 (0x0000-0x00FF reserved for boot ROM)
void cpu_init() {
    ctx.regs.pc = 0x100;
}

// Fetch current opcode from PC, increment PC,
//    decode instruction from the corresponding to the fetched opcode 
static void fetch_instruction() {
    ctx.cur_opcode = bus_read(ctx.regs.pc++);
    ctx.cur_inst = instruction_by_opcode(ctx.cur_opcode);

}

// Fetches operand for the current instruction based on addressing mode
static void fetch_data() {
    ctx.mem_dest = 0;
    ctx.dest_is_mem = false;

    switch(ctx.cur_inst->mode) {
        // Implicit: no operands needed
        case AM_IMP:    return;

        // Single register operation
        case AM_R:
            ctx.fetched_data = cpu_read_reg(ctx.cur_inst->reg_1);
            return;
        
        // Register + 8-bit immediate: Load 8-bit immediate (D8) into register (R)
        case AM_R_D8:
            ctx.fetched_data = bus_read(ctx.regs.pc);
            emu_cycles(1);
            ctx.regs.pc++;
            return;
        
        // 16-bit immediate: take raw 16-bit (D16) ex. JP D16
        case AM_D16: {
            uint16_t lo = bus_read(ctx.regs.pc);
            emu_cycles(1);

            uint16_t hi = bus_read(ctx.regs.pc + 1);
            emu_cycles(1);

            ctx.fetched_data = lo | (hi << 8);

            ctx.regs.pc += 2;
            
            return;
        }
        default:
            printf("Unknown addressing mode! %d\n", ctx.cur_inst->mode);
            exit(-7);
            return;
    }
}

// Executes instruction (durr)
static void execute() {
    IN_PROC proc = inst_get_processor(ctx.cur_inst->type);

    if(!proc) {
        fprintf(stderr, "No implementation!\n");
        exit(-5);
    }

    // Execute logic for function pointed to by proc
    //      ex.
    //          for JP instruction, proc(&ctx) == proc_jp(&ctx)
    proc(&ctx);

}

bool cpu_step() {
    if(!ctx.halted) {
        uint16_t pc = ctx.regs.pc;

        fetch_instruction();
        fetch_data();

        printf("Executing instruction: %02X     PC: %04X\n", ctx.cur_opcode, pc);
        
        if(ctx.cur_inst == NULL) {
            printf("Unknown instruction! %02X\n", ctx.cur_opcode);
            exit(-7);
        }

        execute();
    }
    return true;
}

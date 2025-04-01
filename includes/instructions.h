#include "common.h"

// Addressing mode -> https://gbdev.io/gb-opcodes/optables/
typedef enum {
    AM_IMP,
    AM_R_D16,
    AM_R_R,
    AM_MR_R,
    AM_R,
    AM_R_D8,
    AM_R_MR,
    AM_R_HLI,
    AM_R_HLD,
    AM_HLI_R,
    AM_HLD_R,
    AM_R_A8,
    AM_A8_R,
    AM_HL_SPR,
    AM_D16,
    AM_D8,
    AM_D16_R,
    AM_MR_D8,
    AM_MR,
    AM_A16_R,
    AM_R_A16
} addr_mode;

// Return registers -> https://gbdev.io/pandocs/CPU_Instruction_Set.html
typedef enum {
    RT_NONE,
    // 8-bit registers
    RT_A,
    RT_F,
    RT_B,
    RT_C,
    RT_D,
    RT_E,
    RT_H,
    RT_L,
    // 16-bit general purpose registers
    RT_AF,
    RT_BC,
    RT_DE,
    RT_HL,
    RT_SP,
    RT_PC
} reg_type;

// Game Boy CPU (SM83) instruction set -> https://gbdev.io/gb-opcodes/optables/
typedef enum {    
    IN_NONE,
    IN_NOP,
    IN_LD,
    IN_INC,
    IN_DEC,
    IN_RLCA,
    IN_ADD,
    IN_RRCA,
    IN_STOP,
    IN_RLA,
    IN_JR,
    IN_RRA,
    IN_DAA,
    IN_CPL,
    IN_SCF,
    IN_CCF,
    IN_HALT,
    IN_ADC,
    IN_SUB,
    IN_SBC,
    IN_AND,
    IN_XOR,
    IN_OR,
    IN_CP,
    IN_RET,
    IN_JP,
    IN_POP,
    IN_CALL,
    IN_PUSH,
    IN_RST,
    IN_CB,
    IN_RETI,
    IN_PREFIX,
    IN_LDH,
    IN_JPHL,
    IN_DI,
    IN_EI,
    IN_ERR,
    // Prefixed ($CB $xx)
    IN_RLC,
    IN_RRC,
    IN_RL,
    IN_RR,
    IN_SLA,
    IN_SRA,
    IN_SWAP,
    IN_SRL,
    IN_BIT,
    IN_RES,
    IN_SET
} in_type;

// A condition code -> https://rgbds.gbdev.io/docs/v0.9.1/gbz80.7
typedef enum {
    CT_NONE,
    CT_Z,
    CT_NZ,
    CT_C,
    CT_NC
} cond_type;

// Intruction instance
typedef struct {
    in_type type;
    addr_mode mode;
    reg_type reg_1;
    reg_type reg_2;
    cond_type cond;
    uint8_t param;
} instruction;

instruction *instruction_by_opcode(uint8_t opcode);

char *inst_name(in_type t);

#include "common.h"

typedef struct {

} in_type;

typedef struct {

} addr_mode;

typedef struct {

} reg_type;

typedef struct {

} cond_type;


typedef struct {
    in_type type;
    addr_mode mode;
    reg_type reg_1;
    reg_type reg_2;
    cond_type cond;
    uint8_t param;
} instruction;
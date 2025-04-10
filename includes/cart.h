#pragma once

#include "common.h"

// Cartridge header
typedef struct {
    uint8_t entrypoint[4];
    uint8_t logo[0x30];
    char title[16];
    uint16_t new_lic_code;
    uint8_t sgb_flag;
    uint8_t cartridge_type;
    uint8_t rom_size;
    uint8_t ram_size;
    uint8_t destination_code;
    uint8_t old_lic_code;
    uint8_t version_number;
    uint8_t header_checksum;
    uint16_t global_checksum;
} rom_header;

bool cart_load(char *cart);
uint8_t cart_read(uint16_t address);
void cart_write(uint16_t, uint8_t value);

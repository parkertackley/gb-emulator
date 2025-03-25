#pragma once

#include "common.h"

uint8_t bus_read(uint16_t address);
void bus_write(uint16_t, uint8_t value);

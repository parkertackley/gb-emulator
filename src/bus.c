#include "../includes/bus.h"
#include "../includes/cart.h"

uint8_t bus_read(uint16_t address) {
    if(address < 0x8000) {
        return cart_read(address);
    }

    printf("(bus_read) No implementation!\n");
    exit(-5);

}

void bus_write(uint16_t address, uint8_t value) {
    if(address < 0x8000) {
        cart_write(address, value);
    }

    fprintf(stderr, "(bus_write) No implementation!\n");
    exit(-5);
}

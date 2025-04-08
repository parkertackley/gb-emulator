#include "../includes/cart.h"

// Cartridge object
typedef struct {
    char filename[1024];
    uint32_t rom_size;
    uint8_t *rom_data;
    rom_header *header;
} cart_content;

// Init the cartridge content object
static cart_content ctx;

static const char *ROM_TYPE[] = {
    "ROM ONLY",
    "MBC1",
    "MBC1+RAM",
    "MBC1+RAM+BATTERY",
    "MBC2",
    "MBC2+BATTERY",
    "ROM+RAM",
    "ROM+RAM+BATTERY",
    "MMM01",
    "MMM01+RAM",
    "MMM01+RAM+BATTERY",
    "MBC3+TIMER+BATTERY",
    "MBC3+TIMER+RAM+BATTERY",
    "MBC3",
    "MBC3+RAM",
    "MBC3+RAM+BATTERY",
    "MBC5",
    "MBC5+RAM",
    "MBC5+RAM+BATTERY",
    "MBC5+RUMBLE",
    "MBC5+RUMBLE+RAM",
    "MBC5+RUMBLE+RAM+BATTERY",
    "MBC6",
    "MBC7+SENSOR+RUMBLE+RAM+BATTERY",
    "POCKET CAMERA",
    "BANDAI TAMA5",
    "HuC3",
    "HuC1+RAM+BATTERY"
};

static const char *LIC_CODE[0xA5] = {
    [0x00] = "None",
    [0x01] = "Nintendo Research & Development",
    [0x08] = "Capcom",
    [0x13] = "EA (Electronic Arts)",
    [0x18] = "Hudson Soft",
    [0x19] = "B-AI",
    [0x20] = "KSS",
    [0x22] = "Planning Office WADA",
    [0x24] = "PCM Complete",
    [0x25] = "San-X",
    [0x28] = "Kemco",
    [0x29] = "SETA Corporation",
    [0x30] = "Viacom",
    [0x31] = "Nintendo",
    [0x32] = "Bandai",
    [0x33] = "Ocean Software/Acclaim Entertainment",
    [0x34] = "Konami",
    [0x35] = "HectorSoft",
    [0x37] = "Taito",
    [0x38] = "Hudson Soft",
    [0x39] = "Banpresto",
    [0x41] = "Ubi Soft1",
    [0x42] = "Atlus",
    [0x44] = "Malibu Interactive",
    [0x46] = "Angel",
    [0x47] = "Bullet-Proof Software",
    [0x49] = "Irem",
    [0x50] = "Absolute",
    [0x51] = "Acclaim Entertainment",
    [0x52] = "Activision",
    [0x53] = "Sammy USA Corporation",
    [0x54] = "Konami",
    [0x55] = "Hi Tech Expressions",
    [0x56] = "LJN",
    [0x57] = "Matchbox",
    [0x58] = "Mattel",
    [0x59] = "Milton Bradley Company",
    [0x60] = "Titus Interactive",
    [0x61] = "Virgin Games Ltd.",
    [0x64] = "Lucasfilm Games",
    [0x67] = "Ocean Software",
    [0x69] = "EA (Electronic Arts)",
    [0x70] = "Infogrames",
    [0x71] = "Interplay Entertainment",
    [0x72] = "Broderbund",
    [0x73] = "Sculptured Software",
    [0x75] = "The Sales Curve Limited",
    [0x78] = "THQ",
    [0x79] = "Accolade",
    [0x80] = "Misawa Entertainment",
    [0x83] = "lozc",
    [0x86] = "Tokuma Shoten",
    [0x87] = "Tsukuda Original",
    [0x91] = "Chunsoft Co.",
    [0x92] = "Video System",
    [0x93] = "Ocean Software/Acclaim Entertainment",
    [0x95] = "Varie",
    [0x96] = "Yonezawa/s'pal",
    [0x97] = "Kaneko",
    [0x99] = "Pack-In-Video",
    [0xA4] = "Konami (Yu-Gi-Oh!)"
};

const char *get_lic_name() {
    if(ctx.header->new_lic_code <= 0xA4)
        return LIC_CODE[ctx.header->old_lic_code];

    return "UNKNOWN";
}

const char *cart_type_name() {
    if(ctx.header->cartridge_type <= 0x22)
        return ROM_TYPE[ctx.header->old_lic_code];

    return "UNKNOWN";
}

bool cart_load(char *cart) {
    // Load name of the cart into the Cartridge content (ctx) filename
    snprintf(ctx.filename, sizeof(ctx.filename), "%s", cart);

    // Open the cartridge file, return if cartridge could not be opened
    FILE *fp = fopen(cart, "r");
    if(!fp) {
        printf("Could not open cartridge: %s\n", cart);
        return false;
    }
    printf("%s opened!\n", ctx.filename);

    // Get size of ROM/cart by going to the end of the ROM
    fseek(fp, 0, SEEK_END);
    ctx.rom_size = ftell(fp);
    rewind(fp);

    // Allocate the size of ROM and read data into the cartridge object, close the file
    ctx.rom_data = malloc(ctx.rom_size);
    fread(ctx.rom_data, ctx.rom_size, 1, fp);
    fclose(fp);

    // Go to start of the header
    ctx.header = (rom_header *)(ctx.rom_data + 0x100);
    ctx.header->title[15] = 0;

    // Printing details of the cartridge
    printf("Cartridge loaded...\n");
    printf("\tTitle     : %s\n", ctx.header->title);
    printf("\tType      : %2.2X (%s)\n", ctx.header->cartridge_type, cart_type_name());
    printf("\tROM Size  : %d KB\n", 32 << ctx.header->rom_size);
    printf("\tRAM Size  : %2.2X\n", ctx.header->ram_size);
    printf("\tLIC Code  : %2.2X (%s)\n", ctx.header->old_lic_code, get_lic_name());
    printf("\tROM Vers  : %2.2X\n", ctx.header->version_number);

    // Verifying the checksum (from Pan Docs, part 16)
    uint8_t checksum = 0;
    for(uint16_t address = 0x0134; address <= 0x014C; address++) {
        checksum = checksum - ctx.rom_data[address] - 1;
    }
    printf("\tChecksum  : %2.2X (%s)\n", ctx.header->header_checksum, (checksum & 0xFF) ? "PASSED" : "FAILED");

    return true;

}

uint8_t cart_read(uint16_t address) {
    return ctx.rom_data[address];
}

void cart_write(uint16_t address, uint8_t value) {
    fprintf(stderr, "No implementation!\n");
    exit(-5);
}

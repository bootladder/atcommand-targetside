#ifndef WRISTBAND_V2_5_BOOTLOADER_1_0_PRINTING_HELP_H
#define WRISTBAND_V2_5_BOOTLOADER_1_0_PRINTING_HELP_H

#include <stdint.h>

#define PRINT_STRING(a) printbuf((uint8_t *)a , sizeof(a));

void log_debug_string(const char * a);
void log_debug_stringln(const char * a);

void printbuf(uint8_t * buf, int size);
void printbuf_until_newline_or_zero(uint8_t * buf);

#endif //WRISTBAND_V2_5_BOOTLOADER_1_0_PRINTING_HELP_H

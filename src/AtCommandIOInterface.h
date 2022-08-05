#ifndef ABCD_PRINTING_HELP_H
#define ABCD_PRINTING_HELP_H

#include <stdint.h>
typedef void (printer_func_t ) (uint8_t *);
void AtCommandIOInterface_SetPrinterFunc(printer_func_t f);

void at_command_log_debug_string(const char * a);
void at_command_log_debug_stringln(const char * a);

#endif

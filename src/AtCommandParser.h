
#ifndef ABCD_ATCOMMANDPARSER_H
#define ABCD_ATCOMMANDPARSER_H

#include <stdint.h>
#include "AtCommandHandler.h"

uint8_t AtCommandParser_AddCommandEntry(AtCommandHandler_t * handler);
AtCommandHandler_t * AtCommandParser_ParseLine(uint8_t * line);
void AtCommandParser_DeleteCommandHandlerTable(void);

#endif

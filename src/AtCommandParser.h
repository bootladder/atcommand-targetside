//
// Created by steve on 4/27/22.
//

#ifndef WRISTBAND_V2_5_FACTORYTEST_1_0_ATCOMMANDPARSER_H
#define WRISTBAND_V2_5_FACTORYTEST_1_0_ATCOMMANDPARSER_H

#include <stdint.h>
#include "AtCommandHandler.h"


uint8_t AtCommandParser_AddCommandEntry(AtCommandHandler_t * handler);

AtCommandHandler_t * AtCommandParser_ParseLine(uint8_t * line);
#endif //WRISTBAND_V2_5_FACTORYTEST_1_0_ATCOMMANDPARSER_H

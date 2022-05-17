//
// Created by steve on 4/27/22.
//

#ifndef WRISTBAND_V2_5_FACTORYTEST_1_0_ATCOMMANDHANDLER_H
#define WRISTBAND_V2_5_FACTORYTEST_1_0_ATCOMMANDHANDLER_H

#include <stdint.h>

typedef uint8_t (*AtCommandHandler_CommandFunc_t)(void);
typedef uint8_t (*AtCommandHandler_ReadFunc_t)(void);
typedef uint8_t (*AtCommandHandler_WriteFunc_t)( uint8_t ** args);

typedef struct {
    uint8_t * command_template;
    uint8_t * command_description;
    AtCommandHandler_CommandFunc_t command_func;
    AtCommandHandler_ReadFunc_t read_func;
    AtCommandHandler_WriteFunc_t write_func;
} AtCommandHandler_t;

uint8_t AtCommandHandler_ExecuteAtCommand(AtCommandHandler_t * cmdptr,uint8_t * line);

#endif //WRISTBAND_V2_5_FACTORYTEST_1_0_ATCOMMANDHANDLER_H

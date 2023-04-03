//
// Created by steve on 4/27/22.
//

#ifndef WRISTBAND_V2_5_FACTORYTEST_1_0_AT_COMMAND_HANDLERS_H
#define WRISTBAND_V2_5_FACTORYTEST_1_0_AT_COMMAND_HANDLERS_H

#include <stdint.h>

//set FTM mode
uint8_t at_command_handler_setftm_read(void);
uint8_t at_command_handler_setftm_write(uint8_t **args);


//set debug
uint8_t at_command_handler_setdebug_read(void);
uint8_t at_command_handler_setdebug_write(uint8_t **args);

uint8_t at_command_handler_led_write(uint8_t **line);

//Charge Control Unit (CCU) related commands

uint8_t at_command_handler_pwrctrl(uint8_t **line);
uint8_t at_command_handler_pwrfault(uint8_t **line);
uint8_t at_command_handler_uartctl(uint8_t * line);
uint8_t at_command_handler_selband(uint8_t **line);
uint8_t at_command_handler_bandpres(uint8_t **line);
uint8_t at_command_handler_bookgpio(uint8_t **line);

// FROM MFT SHEET
uint8_t at_command_handler_bandid_read(uint8_t **line);
uint8_t at_command_handler_bandid_write(uint8_t **line);


#endif //WRISTBAND_V2_5_FACTORYTEST_1_0_AT_COMMAND_HANDLERS_H

//
// Created by steve on 5/17/22.
//
#include <stdint.h>
#include <stdio.h>
#include "AtCommandParser.h"
#include "AtCommandHandler.h"

static uint8_t at_command_handler_test_1_write(uint8_t ** args){
    printf("test_1_write\n");
    return 0;
}
static uint8_t at_command_handler_test_1_read(){
    printf("test_1_read\n");
    return 0;
}

void testcase_dummy_1(void){

    static AtCommandHandler_t atch_test_1;
    atch_test_1.command_template = "AT*TEST1";
    atch_test_1.command_description = "*TEST1: (0-1)";
    atch_test_1.write_func = at_command_handler_test_1_write;
    atch_test_1.read_func = at_command_handler_test_1_read;
    AtCommandParser_AddCommandEntry(&atch_test_1);

    uint8_t * line;
    AtCommandHandler_t * cmd;
    line = "AT*TEST1?\n";
    cmd = AtCommandParser_ParseLine(line);
    AtCommandHandler_ExecuteAtCommand(cmd, line);

    line = "AT*TEST1=1\n";
    cmd = AtCommandParser_ParseLine(line);
    AtCommandHandler_ExecuteAtCommand(cmd, line);
    printf("done\n");

}
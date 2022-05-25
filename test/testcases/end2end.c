#include <stdint.h>
#include <stdio.h>
#include "AtCommandParser.h"
#include "AtCommandHandler.h"

static uint32_t test_1_write_callcount = 0;
static uint32_t test_1_read_callcount = 0;



static uint8_t at_command_handler_test_1_write(uint8_t ** args){
    test_1_write_callcount++;
    printf("test_1_write\n");
    return 0;
}
static uint8_t at_command_handler_test_1_read(){
    test_1_read_callcount++;
    printf("test_1_read\n");
    return 0;
}

static AtCommandHandler_t atch_test_1;
void _setup_mock_commandhandlers(){
    atch_test_1.command_template = "AT*TEST1";
    atch_test_1.command_description = "*TEST1: (0-1)";
    atch_test_1.write_func = at_command_handler_test_1_write;
    atch_test_1.read_func = at_command_handler_test_1_read;
}


void testcase_dummy_1(void){

    _setup_mock_commandhandlers();
    AtCommandParser_DeleteCommandHandlerTable();

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

    printf("PASSk\n");
}


void testcase_end2end_allhandlerfuncsdefined_allhandlerfuncscalled(void){

    _setup_mock_commandhandlers();
    AtCommandParser_DeleteCommandHandlerTable();

    AtCommandParser_AddCommandEntry(&atch_test_1);


    // Send command lines
    uint8_t * line;
    AtCommandHandler_t * cmd;
    line = "AT*TEST1?\n";
    cmd = AtCommandParser_ParseLine(line);
    AtCommandHandler_ExecuteAtCommand(cmd, line);

    if(0 == test_1_read_callcount){
        printf("FAIL");
    }

    line = "AT*TEST1=1\n";
    cmd = AtCommandParser_ParseLine(line);
    AtCommandHandler_ExecuteAtCommand(cmd, line);
    printf("done\n");

    if(0 == test_1_write_callcount){
        printf("FAIL");
    }

    printf("PASS");
}


void testcase_dummy_2(void){

    _setup_mock_commandhandlers();
    AtCommandParser_DeleteCommandHandlerTable();

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

    printf("PASSk\n");
}
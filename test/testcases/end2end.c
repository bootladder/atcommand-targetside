#include <stdint.h>
#include <stdio.h>
#include "AtCommandParser.h"
#include "AtCommandHandler.h"


////////////////////////////////////////////////
static AtCommandHandler_t atch_test_1;

static uint32_t test_1_write_callcount = 0;
static uint32_t test_1_read_callcount = 0;
static uint32_t test_1_command_callcount = 0;

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

static uint8_t at_command_handler_test_1_command(void){
    test_1_command_callcount++;
    printf("test_1_command\n");
    return 0;
}

////////////////////////////////////////////////


static void _setup_mock_commandhandlers(){
    atch_test_1.command_template = "AT*TEST1";
    atch_test_1.command_description = "*TEST1: (0-1)";
    atch_test_1.write_func = at_command_handler_test_1_write;
    atch_test_1.read_func = at_command_handler_test_1_read;
    atch_test_1.command_func = at_command_handler_test_1_command;
}

static void _init_testcase(void){
    _setup_mock_commandhandlers();
    AtCommandParser_DeleteCommandHandlerTable();
}


void testcase_writecommand_invalidparameters_parserreturnsnull(void){
    _init_testcase();

    AtCommandParser_AddCommandEntry(&atch_test_1);

    uint8_t * line;
    AtCommandHandler_t * cmd;


    line = "AT*TEST1=_%@345ds--_\n";
    cmd = AtCommandParser_ParseLine(line);
    uint8_t ret = AtCommandHandler_ExecuteAtCommand(cmd, line);

    if(1 != ret){
        printf("FAIL\n");
        return;
    }

}

void testcase_end2end_allhandlerfuncsdefined_allhandlerfuncscalled_assert_all_called(void){
    _init_testcase();
    AtCommandParser_AddCommandEntry(&atch_test_1);

    uint8_t * line;
    AtCommandHandler_t * cmd;


    // Send command lines
    line = "AT*TEST1?\n";
    cmd = AtCommandParser_ParseLine(line);
    AtCommandHandler_ExecuteAtCommand(cmd, line);

    line = "AT*TEST1=1\n";
    cmd = AtCommandParser_ParseLine(line);
    AtCommandHandler_ExecuteAtCommand(cmd, line);

    line = "AT*TEST1\n";
    cmd = AtCommandParser_ParseLine(line);
    AtCommandHandler_ExecuteAtCommand(cmd, line);


    // ASSERTS
    if(0 == test_1_write_callcount){
        printf("FAIL");
        return;
    }
    if(0 == test_1_read_callcount){
        printf("FAIL");
        return;
    }
    if(0 == test_1_command_callcount){
        printf("FAIL");
        return;
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
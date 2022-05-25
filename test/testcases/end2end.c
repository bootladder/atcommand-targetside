#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "AtCommandParser.h"
#include "AtCommandHandler.h"


static uint8_t * line;
static AtCommandHandler_t * atch;

#define _ASSERT_MSG(exp, msg) \
    if(false == (exp)){ \
    printf("FAIL: ");printf(msg);printf("\n"); \
    return; \
    }


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
    line = 0;
    atch = 0;
    _setup_mock_commandhandlers();
    AtCommandParser_DeleteCommandHandlerTable();
}

void testcase_commandlinewithcarriagereturn_is_valid(void) {
    _init_testcase();

    AtCommandParser_AddCommandEntry(&atch_test_1);

    line = "AT*TEST1\r\n";
    atch = AtCommandParser_ParseLine(line);
    _ASSERT_MSG(0 != atch, "parser should not return null")

    uint8_t ret = AtCommandHandler_ExecuteAtCommand(atch, line);
    _ASSERT_MSG(0 == ret, "executing should pass")
}

void testcase_invalidcommandtemplate(void) {
    _init_testcase();

    AtCommandParser_AddCommandEntry(&atch_test_1);

    line = "AT*NOTACOMMAND\n";
    atch = AtCommandParser_ParseLine(line);

    _ASSERT_MSG(0 == atch, "Invalid command template should fail at ParseLine")
}

void testcase_nocommandsadded_parsingshouldfail(void) {
    _init_testcase();

    line = "AT*NOTACOMMAND\n";
    atch = AtCommandParser_ParseLine(line);

    _ASSERT_MSG(0 == atch, "Parsing line with empty table should fail")
}

// THIS NEEDS WORK
// TODO DEFINE INVALID AT COMMANDS
void testcase_writecommand_invalidparameters_parserreturnsnull(void){
    _init_testcase();

    AtCommandParser_AddCommandEntry(&atch_test_1);

    line = "AT*TEST1=_%@345ds--_\n";
    atch = AtCommandParser_ParseLine(line);
    uint8_t ret = AtCommandHandler_ExecuteAtCommand(atch, line);

//    _ASSERT_MSG(0 != ret)
}

void testcase_end2end_allhandlerfuncsdefined_allhandlerfuncscalled_assert_all_called(void){
    _init_testcase();
    AtCommandParser_AddCommandEntry(&atch_test_1);

    // Send command lines
    line = "AT*TEST1?\n";
    atch = AtCommandParser_ParseLine(line);
    AtCommandHandler_ExecuteAtCommand(atch, line);

    line = "AT*TEST1=1\n";
    atch = AtCommandParser_ParseLine(line);
    AtCommandHandler_ExecuteAtCommand(atch, line);

    line = "AT*TEST1\n";
    atch = AtCommandParser_ParseLine(line);
    AtCommandHandler_ExecuteAtCommand(atch, line);

    _ASSERT_MSG(test_1_write_callcount > 0, "write func should have been called")
    _ASSERT_MSG(test_1_read_callcount > 0, "read func should have been called")
    _ASSERT_MSG(test_1_command_callcount > 0, "command func should have been called")
}


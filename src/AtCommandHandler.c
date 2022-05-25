//
// Created by steve on 4/27/22.
//
#include <memory.h>
#include "AtCommandHandler.h"
#include "printing_help.h"

static uint8_t call_read_func(AtCommandHandler_t * cmdptr){
    log_debug_stringln("ITS A READ");

    if(0 == cmdptr->read_func){
        log_debug_stringln("NO READ FUNCTION DEFINED. EXIT");
        return 22;
    }

    return cmdptr->read_func();
}

static uint8_t call_write_func(AtCommandHandler_t * cmdptr, uint8_t * line){
    // Local variables for convenience
    uint8_t * commandtemplate = cmdptr->command_template;
    uint8_t len_of_cmd_tmpl = strlen((const char*)commandtemplate);

    log_debug_stringln("ITS A WRITE");

    if(0 == cmdptr->write_func){
        log_debug_stringln("NO WRITE FUNCTION DEFINED. EXIT");
        return 23;
    }

    // parse parameters by comma positions
    // all data is ASCII bytes.  the handler func will handle
    // string conversion to other types if necessary

    uint8_t * arg_postiions_within_line[8] = {0}; //support up to 8 args comma separated

    // THE FIRST ARG IS AFTER THE =
    // Address of the byte after the =
    arg_postiions_within_line[0] = &line[len_of_cmd_tmpl + 1];

    // counting arg_index at 1 because 0 is loaded above ^
    uint8_t arg_index = 1;

    // WE ARE ASSUMING NO COMMAS BESIDES ARG DELIMITERS!!!
    for(int i=0; i<strlen((const char*)line); i++){
        if(line[i] == ','){
            arg_postiions_within_line[arg_index++] = &line[i+1]; //address of the byte after the ,
        }
    }

    return cmdptr->write_func(arg_postiions_within_line);
}

static uint8_t call_command_func(AtCommandHandler_t * cmdptr){
    log_debug_stringln("ITS A COMMAND");

    if(0 == cmdptr->command_func){
        log_debug_stringln("NO COMMAND FUNCTION DEFINED. EXIT");
        return 21;
    }

    cmdptr->command_func();
    return 0;
}


static uint8_t handle_test_command(AtCommandHandler_t *cmdptr) {
    if(cmdptr->command_description == 0){
        log_debug_stringln("NO DESCRIPTION SPECIFIED FOR THIS COMMAND");
    }
    printbuf_until_newline_or_zero(cmdptr->command_description);
    return 0;
}

uint8_t AtCommandHandler_ExecuteAtCommand(AtCommandHandler_t * cmdptr, uint8_t * line)
{
    log_debug_stringln("AtCommandHandler_ExecuteAtCommand");

    // Local variables for convenience
    uint8_t * commandtemplate = cmdptr->command_template;
    uint8_t len_of_cmd_tmpl = strlen((const char*)commandtemplate);

    // The character after the command template
    // determines what command handler to call
    uint8_t char_after_command_template = line[len_of_cmd_tmpl];

    // This is used to check for the ? after =? in a test command
    uint8_t second_char_after_command_template = line[len_of_cmd_tmpl+1];


    // Check if it's a read ie. ?
    if(char_after_command_template == '?'){
        return call_read_func(cmdptr);
    }

    // Check if it's a Write OR a Test command
    if(char_after_command_template == '='){

        if(second_char_after_command_template == '?'){
            return handle_test_command(cmdptr);
        }

        return call_write_func(cmdptr, line);
    }

    // Check if it's a command, ie. no ? or = or =?
    // ie. if the line ends after the command
    if(char_after_command_template == '\n' || char_after_command_template == '\r'){
        return call_command_func(cmdptr);
    }


    log_debug_stringln("SOMETHING WRONG HAPPENDE BAD AT COMMAND");
    return 1;
}

#include "commandlineprotocol.h"

#include <string.h>
#include "printing_help.h"
#include "AtCommandParser.h"
#include "prepare_help_message.h"


static uint32_t number_of_commands_processed = 0;  // for debugging

void commandlineprotocol_processLine(uint8_t * line){
    number_of_commands_processed++;

    //TODO VALIDATE LINE BEFORE PASSING TO PARSER



    ////////////////////////////////////////////////
    if(0 == strncmp(line, "help", 4)){
        uint8_t * helpmsg = prepare_help_message();
        PRINT_STRING("Helzzzzsszp!\n")
        printbuf_until_zero(helpmsg);
    }


    ////////////////////////////////////////////////
    else if(0 == strncmp(line, "AT", 2)){
        log_debug_stringln("AT COMMAND!\n");
        AtCommandHandler_t * cmdptr = AtCommandParser_ParseLine(line);

        if(0 == cmdptr){
            log_debug_stringln("INVALID AT COMMAND\n");
            return;
        }

        uint8_t result = AtCommandHandler_ExecuteAtCommand(cmdptr, line);
        if(result == 0){
            PRINT_STRING("OK\n")
        } else {
            PRINT_STRING("FAIL\n")
        }
    }

    else{
        log_debug_stringln("Invalid Command!\n");
    }
}

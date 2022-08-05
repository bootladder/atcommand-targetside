#include "AtCommandProcessLine.h"

#include <string.h>
#include "AtCommandIOInterface.h"
#include "AtCommandParser.h"
#include "AtCommandHelpMessage.h"


static uint32_t number_of_commands_processed = 0;  // for debugging

void AtCommandProcessLine_ProcessLine(uint8_t * line){
    number_of_commands_processed++;

    //TODO VALIDATE LINE BEFORE PASSING TO PARSER



    ////////////////////////////////////////////////
    if(0 == strncmp(line, "help", 4)){
        AtCommandHelpMessage_Render();
        uint8_t * helpmsg = AtCommandHelpMessage_Get();
        at_command_log_debug_stringln("Helzzzzsszp!\n");
        at_command_log_debug_stringln(helpmsg);
    }


    ////////////////////////////////////////////////
    else if(0 == strncmp(line, "AT", 2)){
        at_command_log_debug_stringln("AT COMMAND!\n");
        AtCommandHandler_t * cmdptr = AtCommandParser_ParseLine(line);

        if(0 == cmdptr){
            at_command_log_debug_stringln("INVALID AT COMMAND\n");
            return;
        }

        uint8_t result = AtCommandHandler_ExecuteAtCommand(cmdptr, line);
        if(result == 0){
            at_command_log_debug_stringln("OK\n");
        } else {
            at_command_log_debug_stringln("FAIL\n");
        }
    }

    else{
        at_command_log_debug_stringln("Invalid Command!\n");
    }
}

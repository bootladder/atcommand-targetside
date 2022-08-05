#include <memory.h>
#include "AtCommandParser.h"

// TABLE OF POINTERS TO COMMAND HANDLERS
// NOTE THIS IS STATIC AND GLOBAL
// PROBABLY SHOULD ALLOW USER TO SUPPLY THE TABLE OF POINTERS

static AtCommandHandler_t * atcommandhandlers[NUM_ATCOMMANDHANDLERS];
static int num_atcommandhandlers = 0;


AtCommandHandler_t * AtCommandParser_GetCommandEntryAtIndex(uint8_t index){
    return atcommandhandlers[index];
}

uint8_t AtCommandParser_AddCommandEntry(AtCommandHandler_t * handler){
    for(int i=0; i<NUM_ATCOMMANDHANDLERS; i++){
        if(atcommandhandlers[i] == 0){
            atcommandhandlers[i] = handler;
            num_atcommandhandlers++;
            return 0;
        }
    }
    return 1;  //FAIL
}
AtCommandHandler_t * AtCommandParser_ParseLine(uint8_t * line){

    // SCAN FOR A MATCH
    for(int i=0; i<NUM_ATCOMMANDHANDLERS; i++) {

        // skip null entries
        if(atcommandhandlers[i] == 0){
            continue;
        }

        if (0 == strncmp(
                atcommandhandlers[i]->command_template,
                line,
                strlen(atcommandhandlers[i]->command_template))) {

            return atcommandhandlers[i];
        }
    }
    return 0;  //NULL
}

void AtCommandParser_DeleteCommandHandlerTable(void){
    for(int i=0; i<NUM_ATCOMMANDHANDLERS; i++){
        atcommandhandlers[i] = 0;
    }
    num_atcommandhandlers = 0;
}
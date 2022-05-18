//
// Created by steve on 4/27/22.
//

#include <memory.h>
#include "AtCommandParser.h"

// TABLE OF POINTERS TO COMMAND HANDLERS
// NOTE THIS IS STATIC AND GLOBAL
// PROBABLY SHOULD ALLOW USER TO SUPPLY THE TABLE OF POINTERS
#define NUM_ATCOMMANDHANDLERS 64
static AtCommandHandler_t * atcommandhandlers[NUM_ATCOMMANDHANDLERS];

uint8_t AtCommandParser_AddCommandEntry(AtCommandHandler_t * handler){
    for(int i=0; i<NUM_ATCOMMANDHANDLERS; i++){
        if(atcommandhandlers[i] == 0){
            atcommandhandlers[i] = handler;
            return 0;
        }
    }
    return 1;  //FAIL
}
AtCommandHandler_t * AtCommandParser_ParseLine(uint8_t * line){

    // SCAN FOR A MATCH
    for(int i=0; i<NUM_ATCOMMANDHANDLERS; i++) {
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
}
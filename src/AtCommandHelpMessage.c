
#include "AtCommandHelpMessage.h"
#include "string.h"


static uint8_t help_message_buffer[4096];

uint8_t * AtCommandHelpMessage_Get(void){
    return help_message_buffer;
}

void AtCommandHelpMessage_Render(void){

    memset(help_message_buffer,0, 4096);

        for(int  i=0; i< 10; i++){
                help_message_buffer[i] = '0' + i;
        }
}

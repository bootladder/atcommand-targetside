//
// Created by steve on 8/5/22.
//

#include "prepare_help_message.h"
#include "string.h"


static uint8_t help_message_buffer[4096];

uint8_t * prepare_help_message(void){

    memset(help_message_buffer,0, 4096);

        for(int  i=0; i< 10; i++){
                help_message_buffer[i] = '0' + i;
        }
        return help_message_buffer;
}

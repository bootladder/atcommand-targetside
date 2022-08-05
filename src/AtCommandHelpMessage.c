
#include "AtCommandHelpMessage.h"
#include "AtCommandParser.h"
#include "string.h"


static uint8_t help_message_buffer[4096];
static uint8_t one_at_command_buffer[256];



static void _render_one_at_command_handler(AtCommandHandler_t * atcmd){
    memset(one_at_command_buffer, 0, 256);

    strcat(one_at_command_buffer, "\nNAME: " );
    strcat(one_at_command_buffer, atcmd->command_template );
    strcat(one_at_command_buffer, "\nDESC: " );
    strcat(one_at_command_buffer, atcmd->command_description );
    strcat(one_at_command_buffer, "\n" );
}

uint8_t * AtCommandHelpMessage_Get(void){
    return help_message_buffer;
}

void AtCommandHelpMessage_Render(void){

    memset(help_message_buffer, 0, 4096);

    for(int i=0; i<NUM_ATCOMMANDHANDLERS; i++){
        AtCommandHandler_t  * atcmd = AtCommandParser_GetCommandEntryAtIndex(i);
        if(atcmd == 0)
            continue;

        _render_one_at_command_handler(atcmd);

        strcat(help_message_buffer, one_at_command_buffer);

    }

}

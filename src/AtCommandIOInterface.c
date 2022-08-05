#include "AtCommandIOInterface.h"

typedef struct {
    printer_func_t  * printerFunc;
    uint8_t printer_func_call_count;
} atcommandiointerface_state_t;

static atcommandiointerface_state_t state = {0};


void AtCommandIOInterface_SetPrinterFunc(printer_func_t f){
    state.printerFunc = f;
}

void log_debug_string(const char * a){
    if(state.printerFunc == 0){
        // do something
    }

    else{
        state.printerFunc(a);
    }


}
void log_debug_stringln(const char * a){
    if(state.printerFunc == 0){
        // do something
    }

    else{
        state.printerFunc(a);
    }
}


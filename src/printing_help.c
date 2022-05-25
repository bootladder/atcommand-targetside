#include "printing_help.h"
#include <stdio.h>

#ifdef ATCOMMAND_DEBUG
void printbuf(uint8_t * buf, int size){
}

void printbuf_until_newline_or_zero(uint8_t * buf){
}

void log_debug_string(const char * a){}
void log_debug_stringln(const char * a){
    printf(a);
}

#else

void log_debug_string(const char * a){}
void log_debug_stringln(const char * a){}

void printbuf(uint8_t * buf, int size){}
void printbuf_until_newline_or_zero(uint8_t * buf){}

#endif


#include <stdio.h>

#include "gen_table_of_testcases_and_signatures.h"
void main(void){
    printf("my awesome tests\n");
    for(int i=0; i<_GEN_NUM_TEST_CASES; i++){
        _gen_table_of_testcases[i]();
    }
    printf("done\n");
}
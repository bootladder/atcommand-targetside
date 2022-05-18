//
// Created by steve on 5/17/22.
//

#ifndef ATCOMMAND_TARGETSIDE_GEN_TABLE_OF_TESTCASES_AND_SIGNATURES_H
#define ATCOMMAND_TARGETSIDE_GEN_TABLE_OF_TESTCASES_AND_SIGNATURES_H

void testcase_dummy_1(void);

#define _GEN_NUM_TEST_CASES 1

typedef void (*testcase_t)(void);
testcase_t _gen_table_of_testcases[_GEN_NUM_TEST_CASES] ={
        testcase_dummy_1
};

#endif //ATCOMMAND_TARGETSIDE_GEN_TABLE_OF_TESTCASES_AND_SIGNATURES_H

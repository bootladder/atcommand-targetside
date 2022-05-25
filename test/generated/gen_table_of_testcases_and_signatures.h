
#ifndef ATCOMMAND_TARGETSIDE_GEN_TABLE_OF_TESTCASES_AND_SIGNATURES_H
#define ATCOMMAND_TARGETSIDE_GEN_TABLE_OF_TESTCASES_AND_SIGNATURES_H

#define VOIDVOIDSIG(a) void a(void);
typedef void (*testcase_t)(void);

VOIDVOIDSIG(testcase_commandlinewithcarriagereturn_is_valid)
VOIDVOIDSIG(testcase_invalidcommandtemplate)
VOIDVOIDSIG(testcase_writecommand_invalidparameters_parserreturnsnull)
VOIDVOIDSIG(testcase_end2end_allhandlerfuncsdefined_allhandlerfuncscalled_assert_all_called)
VOIDVOIDSIG(testcase_dummy_2)


#define _GEN_NUM_TEST_CASES 5

testcase_t _gen_table_of_testcases[_GEN_NUM_TEST_CASES] = {
  testcase_commandlinewithcarriagereturn_is_valid,
  testcase_invalidcommandtemplate,
  testcase_writecommand_invalidparameters_parserreturnsnull,
  testcase_end2end_allhandlerfuncsdefined_allhandlerfuncscalled_assert_all_called,
  testcase_dummy_2,
};



#endif



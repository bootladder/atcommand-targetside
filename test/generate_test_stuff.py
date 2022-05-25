import sys
import os
from parse import parse

print("Generating Test Stuff")
print()


if len(sys.argv) < 3:
  print("Need argument for directory with test cases and path to output file")
  sys.exit(1)

testcasedir=sys.argv[1]
pathtogeneratedheaderoutputfile = sys.argv[2]
print("Looking for test cases in: %s" % testcasedir)
print("Generated header file path: %s" % pathtogeneratedheaderoutputfile)

filesinsidetestcasedir = []
for f in os.listdir(testcasedir):
  if os.path.isfile(os.path.join(testcasedir, f)):
    print("FILE ", f)
    filesinsidetestcasedir.append(f)

testcasesignatures = []
with open("/tmp/generate_test_stuff.py.log",'w') as log:
  
  log.write("hello")

  for filename in filesinsidetestcasedir:
    with open(testcasedir+filename) as thisfile:
      for line in thisfile:
        if "void testcase_" in line:
          print("LINE: ", line)
          funcsigmatches = parse('{}oid {}(void){}', line)
          print("SYMBOL: ", parse('{}oid {}(void){}', line))
          testcasesignatures.append(funcsigmatches[1])

print("SIGS")
for tcs in testcasesignatures:
  print(tcs)


# render the templated .h file with the list

templateblock_testcasefuncsigs = ""
for tcs in testcasesignatures:
  templateblock_testcasefuncsigs += "VOIDVOIDSIG(%s)\n" % (tcs)


num_testcases = len(testcasesignatures)

templateblock_table_of_testcases = "testcase_t _gen_table_of_testcases[_GEN_NUM_TEST_CASES] = {\n"
for tcs in testcasesignatures:
  templateblock_table_of_testcases += ("  " + tcs + ",\n")

templateblock_table_of_testcases += "};\n"



######

headerfiletemplate = """
#ifndef ATCOMMAND_TARGETSIDE_GEN_TABLE_OF_TESTCASES_AND_SIGNATURES_H
#define ATCOMMAND_TARGETSIDE_GEN_TABLE_OF_TESTCASES_AND_SIGNATURES_H

#define VOIDVOIDSIG(a) void a(void);
typedef void (*testcase_t)(void);

%s

#define _GEN_NUM_TEST_CASES %d

%s


#endif


""" %\
(templateblock_testcasefuncsigs, num_testcases, templateblock_table_of_testcases)


print(headerfiletemplate)

print("Writing the generated header file to: " + pathtogeneratedheaderoutputfile)
with open(pathtogeneratedheaderoutputfile, 'w+') as outputfile:
  outputfile.write(headerfiletemplate)
  
print("Done")

print("Generating Test Stuff")
print()

import sys
testcasedir=sys.argv[1]
print("Looking for test cases in: %s" % testcasedir)

with open("/tmp/generate_test_stuff.py.log",'w') as log:
  
  log.write("hello")

# for each file in testcases/
  # for each line
    # if it is a signature of a test case
    # add to list

# render the templated .h file with the list


print("Done")

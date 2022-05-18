SET(TARGET_NAME atcommand-targetside-unittests)

# runs at cmake time
EXEC_PROGRAM(
#        "echo cmake sucks > /tmp/cmakesucks"
        "python generate_test_stuff.py hello"
        OUTPUT_VARIABLE cmakesucks
)

include_directories(generated)

SET(SRCS
        testmain.c
        testcases/end2end.c

        ${CMAKE_SOURCE_DIR}/src/AtCommandParser.c
        ${CMAKE_SOURCE_DIR}/src/AtCommandHandler.c
        ${CMAKE_SOURCE_DIR}/src/printing_help.c
        )


add_executable(${TARGET_NAME} ${SRCS})

# Generate Table of Testcases and List of signatures
add_custom_command(TARGET ${TARGET_NAME} PRE_BUILD
#        COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/generate_test_stuff.py
        COMMAND pwd
        )

add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
        COMMAND cat /tmp/cmakesucks && rm /tmp/cmakesucks
        )

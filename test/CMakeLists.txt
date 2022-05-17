SET(TARGET_NAME atcommand-targetside-unittests)

include_directories(generated)

SET(SRCS
        testmain.c
        testcases/end2end.c

        ${CMAKE_SOURCE_DIR}/src/AtCommandParser.c
        ${CMAKE_SOURCE_DIR}/src/AtCommandHandler.c
        ${CMAKE_SOURCE_DIR}/src/printing_help.c
        )


add_executable(${TARGET_NAME} ${SRCS})
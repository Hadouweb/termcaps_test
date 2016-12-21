cmake_minimum_required(VERSION 3.0)
project(lexer)

include_directories(includes)
add_subdirectory(libft)
#add_subdirectory(unit_test)

set(SRCS
    srcs/main.c
    srcs/error.c
    srcs/key_func.c
    srcs/debug.c
    srcs/init.c
    srcs/move.c
    srcs/print.c
    srcs/update_cursor.c
    srcs/util.c)

set(HEADERS includes/mytermcaps.h)

add_executable(termcaps ${SRCS} ${HEADERS})

target_link_libraries(termcaps ft termcap)
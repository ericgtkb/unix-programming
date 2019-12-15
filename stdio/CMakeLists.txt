add_executable(in2out in2out.c)
add_executable(stdin2stdout stdin2stdout.c)

target_link_libraries(in2out unixprog)
target_link_libraries(stdin2stdout unixprog)

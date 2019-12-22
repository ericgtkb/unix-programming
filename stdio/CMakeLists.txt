add_executable(stdin2stdout stdin2stdout.c)
target_link_libraries(stdin2stdout unixprog)

add_executable(lineinlineout lineinlineout.c)
target_link_libraries(lineinlineout unixprog)
add_executable(tempfiles tempfiles.c)
target_link_libraries(tempfiles unixprog)

add_executable(mkstemp mkstemp.c)
target_link_libraries(mkstemp unixprog)

add_executable(memstream memstream.c)
target_link_libraries(memstream unixprog)

add_executable(streambuf streambuf.c)
target_link_libraries(streambuf unixprog)


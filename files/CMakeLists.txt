add_executable(ls ls.c)
target_link_libraries(ls unixprog)

add_executable(testerror testerror.c)
target_link_libraries(testerror unixprog)

add_executable(filetype filetype.c)
target_link_libraries(filetype unixprog)

add_executable(access access.c)
target_link_libraries(access unixprog)


add_executable(ls ls.c)
target_link_libraries(ls unixprog)

add_executable(testerror testerror.c)
target_link_libraries(testerror unixprog)


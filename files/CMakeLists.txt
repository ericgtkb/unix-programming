add_executable(ls ls.c)
add_executable(testerror testerror.c)

target_link_libraries(ls unixprog)
target_link_libraries(testerror unixprog)

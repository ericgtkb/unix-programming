add_executable(ls ls.c)
target_link_libraries(ls unixprog)

add_executable(testerror testerror.c)
target_link_libraries(testerror unixprog)

add_executable(filetype filetype.c)
target_link_libraries(filetype unixprog)

add_executable(access access.c)
target_link_libraries(access unixprog)

add_executable(umask umask.c)
target_link_libraries(umask unixprog)

add_executable(chmod chmod.c)
target_link_libraries(chmod unixprog)

add_executable(unlink unlink.c)
target_link_libraries(unlink unixprog)


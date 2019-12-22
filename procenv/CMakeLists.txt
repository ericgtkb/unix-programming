add_executable(classichelloworld classichelloworld.c)
target_link_libraries(classichelloworld unixprog)

add_executable(exithandlers exithandlers.c)
target_link_libraries(exithandlers unixprog)

add_executable(printargv printargv.c)
target_link_libraries(printargv unixprog)

add_executable(printenv printenv.c)
target_link_libraries(printenv unixprog)


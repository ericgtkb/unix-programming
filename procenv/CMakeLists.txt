add_executable(classichelloworld classichelloworld.c)
target_link_libraries(classichelloworld unixprog)

add_executable(exithandlers exithandlers.c)
target_link_libraries(exithandlers unixprog)

add_executable(printargv printargv.c)
target_link_libraries(printargv unixprog)

add_executable(printenv printenv.c)
target_link_libraries(printenv unixprog)

add_executable(jump jump.c)
target_link_libraries(jump unixprog)

add_executable(resourcelimits resourcelimits.c)
target_link_libraries(resourcelimits unixprog)


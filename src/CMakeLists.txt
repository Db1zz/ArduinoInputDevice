file (GLOB_RECURSE project_SRCS *.cpp *.cxx *.cc *.C *.c *.h *.hpp)
set (project_BIN ${PROJECT_NAME})

add_library(staticlib STATIC ${project_SRCS})
target_link_libraries(staticlib ${project_LIBS})
set_target_properties(staticlib PROPERTIES VERSION "${APPLICATION_VERSION_MAJOR}.${APPLICATION_VERSION_MINOR}" OUTPUT_NAME ${project_BIN} CLEAN_DIRECT_OUTPUT 1)
install(TARGETS staticlib DESTINATION lib)

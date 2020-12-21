cmake_minimum_required(VERSION 3.16.0)

project(idsort VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(parseopt)
add_subdirectory(analyzer)

add_executable(
        idsort
        main.cpp
)

add_library(
        modes
        sortm.cpp
)

target_link_libraries(
        modes
        parseopt
        analyzer
)

target_include_directories(
        modes
        PRIVATE
        flow
)

target_link_libraries(
        idsort
        modes
)

install(
        TARGETS idsort
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
)

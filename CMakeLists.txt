cmake_minimum_required(VERSION 3.25)
project(equinox C)

set(CMAKE_C_STANDARD 11)

file(GLOB_RECURSE SRC ${PROJECT_SOURCE_DIR}/src/*.c)

add_library(equinox STATIC ${SRC})
target_include_directories(equinox PRIVATE src PUBLIC include)

file(GLOB_RECURSE TEST ${PROJECT_SOURCE_DIR}/test/*.c)

add_executable(test ${TEST})
target_link_libraries(test equinox)

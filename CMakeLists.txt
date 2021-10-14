cmake_minimum_required(VERSION 3.0.0)
project(sdlb VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(sdlb src/main.c)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

target_link_libraries(sdlb SDL2main SDL2 m)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

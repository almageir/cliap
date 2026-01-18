cmake_minimum_required(VERSION 3.21)
project(basic_usage_example)

if(NOT TARGET cliap)
    include(FetchContent)
    FetchContent_Declare(
        cliap
        GIT_REPOSITORY https://github.com/almageir/cliap.git
        GIT_TAG        master
    )
    option(CLIAP_STANDALONE_BUILD off)
    FetchContent_MakeAvailable(cliap)
endif()

add_executable (basic_usage_example main.cpp)
target_link_libraries(basic_usage_example PRIVATE cliap::cliap)
cmake_minimum_required(VERSION 3.21)

project (cliap VERSION 0.1.0 LANGUAGES C CXX)

include(CMakeDependentOption)

set(CLIAP_MAIN_PROJECT OFF)
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
    set(CLIAP_MAIN_PROJECT ON)
endif()

cmake_dependent_option(CLIAP_BUILD_TESTS
    "Enable cliap tests" ON
    "CLIAP_MAIN_PROJECT" OFF)

add_library(cliap STATIC)
add_library(cliap::cliap ALIAS cliap)

target_sources(cliap
    PRIVATE
        include/cliap/arg.h
        include/cliap/parser.h
        src/parser.cpp
    PUBLIC
        FILE_SET HEADERS
    FILES
        include/cliap/cliap.h
)

target_compile_features(cliap PUBLIC cxx_std_17)
set_target_properties(cliap PROPERTIES CXX_EXTENSIONS NO)

target_include_directories(cliap
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/>
)

if(CLIAP_BUILD_TESTS)
    include(FetchContent)
    find_package(Git REQUIRED)
    add_subdirectory(test)
endif()


include(GNUInstallDirs)
install(TARGETS cliap
    EXPORT cliapTargets
    FILE_SET HEADERS
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT cliapTargets
    NAMESPACE cliap::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/cliap
)

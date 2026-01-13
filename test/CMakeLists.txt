include(CTest)

if (CLIAP_BUILD_TESTS)
    add_executable(cliap_test "cliap_test.cpp")

    FetchContent_Declare(doctest
        URL https://raw.githubusercontent.com/doctest/doctest/master/doctest/doctest.h
        DOWNLOAD_NO_EXTRACT 1
    )
    FetchContent_MakeAvailable(doctest)

    target_include_directories(cliap_test PRIVATE ${doctest_SOURCE_DIR})
    target_link_libraries(cliap_test PRIVATE cliap::cliap)
    add_custom_target(check ALL COMMAND cliap_test)
endif()

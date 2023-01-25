set(TEST_MAIN 
    "unit_tests")
set(TEST_SOURCES
    "testmain.cpp")
set(TEST_HEADERS 
    "testmain.hpp")

add_executable(${TEST_MAIN} ${TEST_SOURCES} ${TEST_HEADERS})
find_package(Catch2 CONFIG REQUIRED)
target_link_libraries(${TEST_MAIN} PRIVATE Catch2::Catch2 Catch2::Catch2WithMain)
target_link_libraries(${TEST_MAIN} PUBLIC HelloWorld)

find_package(Catch2 CONFIG REQUIRED)
include(CTest)
include(Catch)
catch_discover_tests(${TEST_MAIN})
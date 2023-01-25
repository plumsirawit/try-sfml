add_library(HelloWorld STATIC
    "helloworld.cpp"
    "helloworld.hpp")

target_include_directories(HelloWorld PUBLIC
    "./")

if (${ENABLE_WARNINGS})
    target_set_warnings(TARGET HelloWorld ENABLE ON AS_ERROR OFF)
endif()
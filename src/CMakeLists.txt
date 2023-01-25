add_library(HelloWorld STATIC
    "helloworld.cpp"
    "helloworld.hpp")

target_include_directories(HelloWorld PUBLIC
    "./")

add_compile_definitions(CMAKE_SOURCE_DIR="${CMAKE_SOURCE_DIR}")
add_executable(Main "main.cpp")
add_executable(ClickerGame "clicker.cpp" "clicker.hpp")
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
target_link_libraries(Main PRIVATE sfml-system sfml-network sfml-graphics sfml-window)
target_link_libraries(ClickerGame PRIVATE sfml-system sfml-network sfml-graphics sfml-window)

if (${ENABLE_WARNINGS})
    target_set_warnings(TARGET HelloWorld ENABLE ON AS_ERROR OFF)
endif()
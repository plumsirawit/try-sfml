#include "testmain.hpp"

TEST_CASE("Hello, world is returned correctly", "[hello]") {
  REQUIRE(get_helloworld() == "Hello, world!");
}
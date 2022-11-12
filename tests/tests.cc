#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif

#include "catch.hpp"
#include <string>

#include "utilities.hpp"

TEST_CASE("Default Test", "[default]") {
  REQUIRE(true);
}

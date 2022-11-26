#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif

#include "catch.hpp"
#include <string>
#include <map>
#include <vector>
#include <wikigraph.hpp>

#include "utilities.hpp"

TEST_CASE("Intake test", "constructor") {
  // python >:)
  std::map<std::string, std::vector<std::string>> expected = 
  {
    {"A", {"B", "C"}},
    {"C", {"D"}},
    {"this has spaces", {"B"}},
    {"\"article\"", {"D"}}
  };

  WikiGraph w("./datasets/test.tsv");
  std::cout << __LINE__ << std::endl;
  REQUIRE(expected == w.getMap());
}

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
    {"B", {}},
    {"C", {"D"}},
    {"D", {}},
    {"this has spaces", {"B"}},
    {"\"article\"", {"D"}},
  };

  WikiGraph w("./datasets/input_test.tsv");
  REQUIRE(expected == w.getMap());
}

TEST_CASE("Dijkstras simple", "dijkstras") {
  std::vector<std::string> expected = {
    "A", "B", "C", "D", "E"
  };
  std::cout << "elems:" << std::endl;
  WikiGraph w("./datasets/line_graph.tsv");
  for (const auto& v : w.getPathDijkstras("A", "E")) {
    std::cout << v << " ";
  }
  std::cout << std::endl;
  REQUIRE(expected == w.getPathDijkstras("A", "E"));
}

TEST_CASE("Dijkstra's picks the bests path", "dijkstras") {

}

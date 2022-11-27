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
  std::vector<std::string> expectedAE = {
    "A", "B", "C", "D", "E"
  };
  std::vector<std::string> expectedCD = {
    "C", "D"
  };
  WikiGraph w("./datasets/line_graph.tsv");
  REQUIRE(expectedAE == w.getPathDijkstras("A", "E"));
  REQUIRE(expectedCD == w.getPathDijkstras("C", "D"));
}

TEST_CASE("Dijkstra's picks the best path", "dijkstras") {
  std::vector<std::string> expectedAE = {
    "A", "E"
  };
  std::vector<std::string> expectedAD = {
    "A", "B", "D"
  };
  WikiGraph w("./datasets/diff_paths.tsv");
  REQUIRE(expectedAE == w.getPathDijkstras("A", "E"));
  REQUIRE(expectedAD == w.getPathDijkstras("A", "D"));
}

TEST_CASE("BFS simple", "BFS") {
  std::vector<std::string> expectedAE = {
    "A", "B", "C", "D", "E"
  };
  std::vector<std::string> expectedCD = {
    "C", "D"
  };
  WikiGraph w("./datasets/line_graph.tsv");
  REQUIRE(expectedAE == w.getPathBFS("A", "E"));
  REQUIRE(expectedCD == w.getPathBFS("C", "D"));
}

TEST_CASE("BFS picks the best path", "BFS") {
  std::vector<std::string> expectedAE = {
    "A", "E"
  };
  std::vector<std::string> expectedAD = {
    "A", "B", "D"
  };
  WikiGraph w("./datasets/diff_paths.tsv");
  REQUIRE(expectedAE == w.getPathBFS("A", "E"));
  REQUIRE(expectedAD == w.getPathBFS("A", "D"));
}
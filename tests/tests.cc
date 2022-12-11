#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif

#include "catch.hpp"
#include <string>
#include <map>
#include <vector>
#include <wikigraph.hpp>
#include <time.h>
#include <iostream>

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

TEST_CASE("Dijkstra's handles cycles", "BFS") {
  std::vector<std::string> expectedAE = {
    "A", "E"
  };
  std::vector<std::string> expectedAD = {
    "A", "B", "D"
  };
  WikiGraph w("./datasets/cycle.tsv");
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

TEST_CASE("BFS handles cycles", "BFS") {
  std::vector<std::string> expectedAE = {
    "A", "E"
  };
  std::vector<std::string> expectedAD = {
    "A", "B", "D"
  };
  WikiGraph w("./datasets/cycle.tsv");
  REQUIRE(expectedAE == w.getPathBFS("A", "E"));
  REQUIRE(expectedAD == w.getPathBFS("A", "D"));
}

TEST_CASE("BFS matches Dijkstra's given random real data", "real") {
  WikiGraph w("./datasets/links.tsv");
  srand(time(NULL));

  auto pages = w.getPages();
  
  // perform 5 random searches
  // make sure both algorithms match each other
  for (int i = 0; i < 5; ++i) {
    auto start = pages[rand() % pages.size()];
    auto end = pages[rand() % pages.size()];
    std::cout << start << " to " << end;

    
    std::vector<std::string> bfs_path, dijkstra_path;

    // if one of them cannot find a path, the other should be the same
    try {
      bfs_path = w.getPathBFS(start, end);
      std::cout << " (" << bfs_path.size() << ")";
    } catch (std::runtime_error e) {
      std::cout << " (no path)";
      REQUIRE_THROWS(w.getPathDijkstras(start, end));
    }

    try {
      dijkstra_path = w.getPathDijkstras(start, end);
    } catch (std::runtime_error e) {
      REQUIRE_THROWS(w.getPathBFS(start, end));
    }

    std::cout << std::endl;

    // there may be multiple shortest paths through the data,
    // but we want to ensure that they are both the shortest
    REQUIRE(bfs_path.size() == dijkstra_path.size());
  }
}

TEST_CASE("Pagerank simple", "prk") {
  WikiGraph w("datasets/easypagerank.tsv");
  auto ranked = w.rankPages();
  for (const auto& rank : ranked) {
    std::cout << rank.title << "    " << rank.rank << std::endl;
  }
}
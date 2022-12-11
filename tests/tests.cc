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

bool reasonablyEqual(const double& a, const double& b) {
  return std::abs(a - b) < 0.001;
}

TEST_CASE("Intake test", "[constructor]") {
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

// ------------- BFS Test Cases -------------

TEST_CASE("BFS simple", "[BFS]") {
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

TEST_CASE("BFS handles cycles", "[BFS]") {
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

// ------------- Brandes Test Cases -------------

TEST_CASE("Page Centrality for two middle Nodes", "[Brandes]") {
  /* A -> B
     |    |
     v    v
     C -> D
  */
  WikiGraph w{"./datasets/centrality/basic_two_cent_nodes.tsv"};
  REQUIRE(w.getBetweenCentrality("A") == 0.0);
  REQUIRE(w.getBetweenCentrality("D") == 0.0);
  REQUIRE(w.getBetweenCentrality("B") == w.getBetweenCentrality("C"));
  REQUIRE(w.getBetweenCentrality("B") > 0.0); // isn't the only shortest path!
  REQUIRE(w.getBetweenCentrality("B") < 1.0); // isn't the only shortest path!
  REQUIRE(w.getBetweenCentrality("C") > 0.0); // isn't the only shortest path!
  REQUIRE(w.getBetweenCentrality("C") < 1.0); // isn't the only shortest path!
}

TEST_CASE("Page centrality no central nodes", "[Brandes]") {
  WikiGraph w{"./datasets/centrality/no_central_node.tsv"}; 
  REQUIRE(w.getBetweenCentrality("A") == 0.0);
  REQUIRE(w.getBetweenCentrality("B") == 0.0);
  REQUIRE(w.getBetweenCentrality("C") == 0.0);
  REQUIRE(w.getBetweenCentrality("D") == 0.0);
}

TEST_CASE("Page centrality single central nodes", "[Brandes]") {
  WikiGraph w{"./datasets/centrality/single_central_node.tsv"}; 
  REQUIRE(w.getBetweenCentrality("A") == 0.0);
  REQUIRE(w.getBetweenCentrality("B") == 0.0);
  REQUIRE(w.getBetweenCentrality("C") == 0.0);
  REQUIRE(w.getBetweenCentrality("D") > 1.0); // is central for many paths.
  REQUIRE(w.getBetweenCentrality("E") == 0.0);
  REQUIRE(w.getBetweenCentrality("F") == 0.0);
  REQUIRE(w.getBetweenCentrality("G") == 0.0);
}

TEST_CASE("Page centrality two central equal central nodes", "[Brandes]") {
  WikiGraph w{"./datasets/centrality/two_eq_cent_nodes.tsv"}; 
  REQUIRE(w.getBetweenCentrality("A") == 0.0);
  REQUIRE(w.getBetweenCentrality("B") == 0.0);
  REQUIRE(w.getBetweenCentrality("C") == 0.0);
  REQUIRE(w.getBetweenCentrality("D") > 1.0); // is central for many paths.
  REQUIRE(w.getBetweenCentrality("E") == 0.0);
  REQUIRE(w.getBetweenCentrality("F") == 0.0);
  REQUIRE(w.getBetweenCentrality("G") == 0.0);
  REQUIRE(w.getBetweenCentrality("H") > 1.0); // is central for many paths.
  REQUIRE(w.getBetweenCentrality("D") == w.getBetweenCentrality("H"));
}

TEST_CASE("Pagerank Two pages all connected should be equal", "[Pagerank]") {
  WikiGraph w("datasets/pagerank/two_page_all.tsv");
  REQUIRE(reasonablyEqual(w.getPageRank("a"), 0.5));
  REQUIRE(reasonablyEqual(w.getPageRank("b"), 0.5));
}

TEST_CASE("Pagerank Three pages all connected should be equal", "[Pagerank]") {
  WikiGraph w("datasets/pagerank/three_page_all.tsv");
  REQUIRE(w.getPageRank("a") == w.getPageRank("b"));
  REQUIRE(w.getPageRank("b") == w.getPageRank("c"));
  REQUIRE(w.getPageRank("a") == w.getPageRank("c"));

  REQUIRE(reasonablyEqual(w.getPageRank("a"), 1.0 / 3.0));
  REQUIRE(reasonablyEqual(w.getPageRank("b"), 1.0 / 3.0));
  REQUIRE(reasonablyEqual(w.getPageRank("c"), 1.0 / 3.0));
}

TEST_CASE("Pagerank Two pages directed", "[Pagerank]") {
  WikiGraph w("datasets/pagerank/two_page_dir.tsv");
  double a_page_rank = w.getPageRank("a");
  double b_page_rank = w.getPageRank("b");
  REQUIRE(a_page_rank < b_page_rank);
  // Note: values were calculated from this website: 
  // https://computerscience.chemeketa.edu/cs160Reader/_static/pageRankApp/index.html
  REQUIRE(reasonablyEqual(a_page_rank, 0.3508));
  REQUIRE(reasonablyEqual(b_page_rank, 0.6491));
}

// ------------- Page Rank Test Cases -------------


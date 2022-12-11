#include <iostream>

#include "utilities.hpp"
#include <iomanip>

#include "wikigraph.hpp"

int main(int argc, char* argv[]) {
  // TODO: Setup I/O
  /**
   * Usage: algorithm flag, start page, end page
   * ex -b "start" "end" (BFS)
   *    -d "start" "end" (Dijkstra's)
   *    -p "start" "end" (PageRank)
  */
  // WikiGraph w{"./datasets/links.tsv"};
  WikiGraph w{"./datasets/links.tsv"};

  // auto C_B = w.getCentralityMap();

  // w.centralityMapToFile(C_B, "wikigraph_centrality_map.tsv");

  // auto C_B_sort = w.getSortedCentrality();

  // std::cout << "The top ten most central articles are: " << std::endl;
  // for (size_t i = 0; i < 10; ++i) {
  //   auto pair = C_B_sort[i];
  //   auto article = pair.first;
  //   auto centrality = pair.second;
  //   std::cout << article << " : " << std::setprecision(2) << std::fixed << centrality << std::endl;
  // }

  auto ranked_pages = w.rankPages();

  auto page_rank_sorted = w.getSortedPageRank();

  std::cout << "The ten highest ranked articles are: " << std::endl;
  for (size_t i = 0; i < 10; ++i) {
    auto pair = page_rank_sorted[i];
    auto article = pair.first;
    auto centrality = pair.second;
    std::cout << article << " : " << std::setprecision(5) << std::fixed << centrality << std::endl;
  }

  return 0;
}
#include <iostream>

#include "utilities.hpp"
#include <iomanip>

#include "wikigraph.hpp"

int main(int argc, char* argv[]) {
  // TODO: Setup I/O

  (void) argc;
  (void) argv;
  
  /**
   * This should likely take in the filename of our data as input.
   * Using flags, we can request what the user would like to determine
   *  - Need to be able to request BFS search of path for the time being.
   * We should construct helper functions in order to clean / parse the data.
   * Then construct the WikiGraph from the data.
   * Call BFS search on it from the given input
   *  - Maybe -f [from_page] -t [to_page]
  */
  WikiGraph w{"./datasets/links.tsv"};

  // auto C_B = w.getCentralityMap();

  // w.centralityMapToFile(C_B, "wikigraph_centrality_map.tsv");

  // auto C_B_sort = w.sortCentralityMap(C_B);

  // std::cout << "The top ten most central articles are: " << std::endl;
  // for (size_t i = 0; i < 10; ++i) {
  //   auto pair = C_B_sort[i];
  //   auto article = pair.first;
  //   auto centrality = pair.second;
  //   std::cout << article << " : " << std::setprecision(2) << std::fixed << centrality << std::endl;
  // }

  auto ranked_pages = w.rankPages();

  size_t i = 0;
  for (const auto& ranked_page : ranked_pages) {
    std::cout << ranked_page.first << " " << ranked_page.second << std::endl;
    if (i++ == 100) {
      break;
    }
  }


  return 0;
}
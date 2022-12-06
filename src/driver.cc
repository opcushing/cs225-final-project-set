#include <iostream>

#include "utilities.hpp"

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

  auto C_B = w.getCentralityMap();

  // w.centralityMapToFile(C_B, "wikigraph_centrality_map.tsv");

  std::string most_central_page;
  double max_centrality = 0.0;
  for (const auto& pair : C_B) {
    const auto& page = pair.first;
    const auto& centrality = pair.second;
    if (centrality > max_centrality) {
      max_centrality = centrality;
      most_central_page = page;
    }
  }

  std::cout << "The most central page is: " << most_central_page << "\n";
  std::cout << "with a centrality value of: " << max_centrality << std::endl;

  return 0;
}
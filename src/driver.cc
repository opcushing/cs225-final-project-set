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

  // std::vector<std::string> page_path = w.getPathBFS("Advertising", "Silicon");

  // for (const auto& page : page_path) {
  //   std::cout << page << " -> ";
  // }
  // std::cout << "[Finished]" << std::endl;

  std::cout << "Beep Boop" << std::endl;

  auto C_B = w.getCentralityMap();

  for (const auto& pair : C_B) {
    std::cout << pair.second << std::endl;
  }

  return 0;
}
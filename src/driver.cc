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
  WikiGraph w{"./dataset/links.tsv"};

  std::vector<std::string> page_path = w.getPathBFS("11th_century", "8th_century");

  for (const auto& page : page_path) {
    std::cout << page << std::endl;
  }

  return 0;
}
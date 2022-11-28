#include <iostream>

#include "utilities.hpp"

#include "wikigraph.hpp"

int main(int argc, char* argv[]) {
  // TODO: Setup I/O
  /**
   * Usage: algorithm flag, start page, end page
   * ex -b "start" "end" (BFS)
   *    -d "start" "end" (Dijkstra's)
   *    -p "start" "end" (PageRank)
  */
  if (!(argc == 4 || (argc == 3 && argv[1] == "-p"))) {
    std::cout << "Usage: algorithm flag, start page, end page\n"
                << "or -p n for the first n pages"
                << "\t-b \"start\" \"end\" (BFS)\n"
                << "\t-d \"start\" \"end\" (Dijkstra's)\n"
                << "\t-p n (PageRank)" << std::endl;
    return 1;
  }

  WikiGraph w{"./datasets/links.tsv"};

  std::vector<std::string> path;
  
  // pick an algorithm
  switch (argv[1][1]) {
    case 'b': {
      path = w.getPathBFS(argv[2], argv[3]);
      break;
    }
    case 'd': {
      path = w.getPathDijkstras(argv[2], argv[3]);
      break;
    }
    case 'p': {
      // need to figure out what this does
      auto pages = w.rankPages();
      // print the first n pages
      break;
    }
    default: {
      std::cout << "Invalid algorithm" << std::endl;
      std::cout << "Usage: algorithm flag, start page, end page\n"
                << "\t-b \"start\" \"end\" (BFS)\n"
                << "\t-d \"start\" \"end\" (Dijkstra's)\n"
                << "\t-p \"start\" \"end\" (PageRank)" << std::endl;
      return 1;
    }
  }

  for (auto i = path.begin(); i != path.end() - 1; ++i) {
    std::cout << *i << " -> ";
  }
  std::cout << path.back() << std::endl;

  return 0;
}
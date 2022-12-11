#include <iostream>

#include "utilities.hpp"
#include <iomanip>
#include <stdexcept>

#include "wikigraph.hpp"

int main(int argc, char* argv[]) {

  std::stringstream usage;
  usage << "Usage: \n";
  usage << "\t./wikigraph bfs \"start\" \"end\" (BFS: shortest path from start to end)\n\n";
  usage << "\t./wikigraph pagerank -t n (list top n ranked pages)\n";
  usage << "\t./wikigraph pagerank -p page (find rank of a particular page)\n\n";
  usage << "\t./wikigraph brandes -t n (list n most central pages)\n";
  usage << "\t./wikigraph brandes -p page (find centrality of a particular page)\n";

  std::string command;
  std::pair<std::string, std::string> args;
  size_t range = 0;
  (void)range;
  try {
    if (argc != 4) {
      throw std::invalid_argument("malformed arguments");
    } else {
      command = argv[1];
      args.first = argv[2];
      args.second = argv[3];

      if (command != "bfs" && command != "brandes" && command != "pagerank")
        throw std::invalid_argument("invalid command");
      else if (command != "bfs") {
        if (args.first != "-t" && args.first != "-p")
          throw std::invalid_argument("invalid flags");
        else if (args.first == "-t")
          range = std::stoi(args.second);
      }
    }
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
    std::cout << usage.str() << std::endl;
    return 1;
  }

  WikiGraph w{"./datasets/links.tsv"};

  if (command == "bfs") {
    auto path = w.getPathBFS(args.first, args.second);
    for (auto page = path.begin(); page != path.end() - 1; ++page) {
      std::cout << *page << " -> ";
    }
    std::cout << path.back() << std::endl;
  } else if (command == "pagerank") {
    if (args.first == "-t") {
      auto path = w.rankPages();
      auto sorted = w.getSortedPageRank();
      for (size_t i = 0; i < range; ++i) {
        std::cout << sorted[i].first << " : " << std::setprecision(5) << std::fixed << sorted[i].second << std::endl;
      }
    } else {
      std::cout << w.getPageRank(args.second) << std::endl;
    }
  } else if (command == "brandes") {
    if (args.first == "-t") {
      auto path = w.getSortedCentrality();
      for (size_t i = 0; i < range; ++i) {
        std::cout << path[i].first << " : " << std::setprecision(5) << std::fixed << path[i].second << std::endl;
      }
    } else {
      std::cout << w.getBetweenCentrality(args.second) << std::endl;
    }
  }

  return 0;
}
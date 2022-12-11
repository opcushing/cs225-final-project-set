#include <iostream>

#include "utilities.hpp"
#include <iomanip>
#include <stdexcept>

#include "wikigraph.hpp"

int main(int argc, char* argv[]) {
  // TODO: Setup I/O

  (void)argv;

  std::stringstream usage;
  usage << "Usage: \n";
  usage << "\t./wiki bfs \"start\" \"end\" (BFS: shortest path from start to end)\n\n";
  usage << "\t./wiki pagerank -t n (list top n ranked pages)\n";
  usage << "\t./wiki pagerank -p page (find rank of a particular page)\n\n";
  usage << "\t./wiki brandes -t n (list n most central pages)\n";
  usage << "\t./wiki brandes -p page (find centrality of a particular page)\n";

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
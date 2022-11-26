#include "wikigraph.hpp"
#include "utilities.hpp"
#include <unordered_map>
#include <fstream>

// ------- Rule of Threes ---------
// TODO: Constructor
WikiGraph::WikiGraph() {

}

// TODO: Construct from File
WikiGraph::WikiGraph(const std::string& file_name) {
  // Reads in file stream.
  // Populates map.

  // open file
  // get a line; decode the first item, decode the second item, add the second to adjlist of first
  
  std::string file = file_to_string(file_name);
  std::vector<std::string> lines;
  SplitString(file, '\n', lines);
  lines.pop_back(); // our dataset has a line of empty space that we can discard

  std::unordered_map<std::string, std::string> decoded; // memoize decoding
  for (auto& line : lines) {
    std::vector<std::string> pages;
    SplitString(line, '\t', pages);

    // decode if necessary
    if (decoded.find(pages[0]) == decoded.end()) {
      decoded[pages[0]] = DecodeURL(pages[0]);
    }
    if (decoded.find(pages[1]) == decoded.end()) {
      decoded[pages[1]] = DecodeURL(pages[1]);
    }

    auto src = decoded[pages[0]];
    auto dest = decoded[pages[1]];

    article_map[src].push_back(dest);
  }
}

// TODO: Destructor
WikiGraph::~WikiGraph() {

}

// TODO: Copy Assignment Operator
WikiGraph& WikiGraph::operator=(WikiGraph& other) {
  // ??
  (void) other;
  return *this;
}


// --------- Algorithms ------------
// TODO: getPathBFS()
std::vector<std::string> WikiGraph::getPathBFS(const std::string& from_page, const std::string& to_page) const {
  std::vector<std::string> path_to_return;
  // ...
  (void) from_page;
  (void) to_page;

  return path_to_return;
}

// TODO: getPathDijkstras()
std::vector<std::string> WikiGraph::getPathDijkstras(const std::string& from_page, const std::string& to_page) const {
  std::vector<std::string> path_to_return;
  // ...
  (void) from_page;
  (void) to_page;

  return path_to_return;
}

// TODO: rankPages()
std::vector<WikiGraph::RankedPage> WikiGraph::rankPages() const {
  std::vector<RankedPage> ranked_pages;
  // ...
  return ranked_pages;
}
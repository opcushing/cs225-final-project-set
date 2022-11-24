#include "wikigraph.hpp"

// ------- Rule of Threes ---------
// TODO: Constructor
WikiGraph::WikiGraph() {

}

// TODO: Construct from File
WikiGraph::WikiGraph(const std::string& file_name) {
  // Reads in file stream.
  // Populates map.
  (void) file_name;
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
#include "wikigraph.hpp"

#include <fstream>
#include <queue>
#include <unordered_map>

#include "utilities.hpp"

// TODO: Construct from File
WikiGraph::WikiGraph(const std::string& file_name) {
  // Reads in file stream.
  // Populates map.

  // open file
  // get a line; decode the first item, decode the second item, add the second
  // to adjlist of firsts
  std::string file = file_to_string(file_name);
  std::vector<std::string> lines;
  SplitString(file, '\n', lines);
  lines
      .pop_back();  // our dataset has a line of empty space that we can discard

  std::unordered_map<std::string, std::string> decoded;  // memoize decoding
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

// --------- Algorithms ------------
// TODO: getPathBFS()
std::vector<std::string> WikiGraph::getPathBFS(
    const std::string& start_page, const std::string& end_page) const {
  std::cout << "getPath" << std::endl;

  std::vector<std::string> page_path;

  std::map<std::string, std::string> page_tree;
  std::queue<std::string> to_visit;

  std::string curr_page;
  to_visit.push(start_page);

  while (!to_visit.empty() && curr_page != end_page) {
    curr_page = to_visit.front();
    to_visit.pop();
    if (article_map.find(curr_page) != article_map.end()) {
      std::vector<std::string> adjacent_pages = article_map.at(curr_page);
      for (const auto& adj_page : adjacent_pages) {
        if (page_tree.count(adj_page) != 1) {  // if page hasn't been visited.
          to_visit.push(adj_page);
          page_tree[adj_page] = curr_page;
        }
        if (adj_page == end_page) break;  // path to page was found.
      }
    }
  }

  // Path between pages was not found...
  if (page_tree.count(end_page) == 0) {
    std::cout << "NO PATH FOUND" << std::endl;
    return page_path;
  }

  std::string temp_page = end_page;
  std::vector<std::string> reverse_path;
  while (temp_page != start_page) {
    reverse_path.push_back(temp_page);
    temp_page = page_tree[end_page];
  }
  reverse_path.push_back(start_page);

  for (int i = (int)reverse_path.size() - 1; i >= 0; --i) {
    page_path.push_back(reverse_path[i]);
  }

  return page_path;
}

// TODO: getPathDijkstras()
std::vector<std::string> WikiGraph::getPathDijkstras(
    const std::string& start_page, const std::string& end_page) const {
  std::vector<std::string> path_to_return;
  // ...
  (void)start_page;
  (void)end_page;

  return path_to_return;
}

// TODO: rankPages()
std::vector<WikiGraph::RankedPage> WikiGraph::rankPages() const {
  std::vector<RankedPage> ranked_pages;
  // ...
  return ranked_pages;
}
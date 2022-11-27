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
  // get a line; decode the first item, decode the second item, add the second to adjlist of firsts
  std::string file = file_to_string(file_name);
  std::vector<std::string> lines;
  SplitString(file, '\n', lines);
  // our dataset has a line of empty space that we can discard
  if (lines.back().empty())
    lines.pop_back(); 

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
    if (article_map.find(dest) == article_map.end()) {
      // create a vertex for the destination (constructs an empty list)
      article_map[dest];
    }
  }
}

// --------- Algorithms ------------
// TODO: getPathBFS()
std::vector<std::string> WikiGraph::getPathBFS(
    const std::string& start_page, const std::string& end_page) const {

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
        // if page hasn't been visited.
        if (page_tree.count(adj_page) != 1) {
          to_visit.push(adj_page);
          page_tree[adj_page] = curr_page;
        }
        if (adj_page == end_page) {
          break; // path to page was found.
        }
      }
    }
  }

  // Path between pages was not found...
  if (page_tree.count(end_page) == 0) {
    throw std::runtime_error("Path to page not found");
  }

  std::string path_page = end_page;
  while (path_page != start_page) {
    page_path.push_back(path_page);
    path_page = page_tree.at(path_page);
  }
  page_path.push_back(start_page);

  return {page_path.rbegin(), page_path.rend()};
}

// TODO: getPathDijkstras()
std::vector<std::string> WikiGraph::getPathDijkstras(const std::string& start_page, const std::string& end_page) const {

// extract keys from map
std::vector<std::string> pages;
std::transform(article_map.begin(), article_map.end(), std::back_inserter(pages),
    [](decltype(article_map)::value_type const &kv) {
        return kv.first;
    });

 // init distance and predecessor
 std::map<std::string, int> distance;
 std::map<std::string, std::string> predecessor;
 for (const auto& page: pages) {
  distance[page] = INT_MAX;
  predecessor[page] = "";
 }
 distance[start_page] = 0;

 // priority is minimum distance, represented by this lambda expression
 auto priority = [&distance](std::string a, std::string b) {
    return distance.at(a) > distance.at(b);
  };

 // construct the priority queue based on the pages (keys in article_map)
 std::priority_queue<std::string, std::vector<std::string>, decltype(priority)> q{priority};
 q.push(start_page);

  // go through the edges
  while (!q.empty()) {
    std::string curr = q.top();
    q.pop();
    for (const auto& neighbor : article_map.at(curr)) {
      if (1 + distance[curr] < distance[neighbor]) {
        distance[neighbor] = 1 + distance[curr];
        predecessor[neighbor] = curr;
        q.push(neighbor);
      }
    }
  }

  // construct the path using the predecessor map
  std::vector<std::string> path;
  path.push_back(end_page);

  while (path.back() != start_page && predecessor[path.back()] != "") {
    path.push_back(predecessor[path.back()]);
  }

  // there is no path from the start to the end
  if (std::find(path.begin(), path.end(), start_page) == path.end()) {
    throw std::invalid_argument("There is no path between these articles");
  }
  
  // return the reversed version (start -> end)
  return {path.rbegin(), path.rend()};
}

// TODO: rankPages()
std::vector<WikiGraph::RankedPage> WikiGraph::rankPages() const {
  std::vector<RankedPage> ranked_pages;
  // ...
  return ranked_pages;
}
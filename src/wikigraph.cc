#include <fstream>
#include <iomanip>
#include <queue>
#include <stack>
#include <limits>
#include <algorithm>
#include <thread>
#include <mutex>

#include "utilities.hpp"

#include "wikigraph.hpp"

std::mutex mtx;

// TODO: Construct from File
WikiGraph::WikiGraph(const std::string& file_name) {
  // Reads in file stream.
  // Populates map.
  std::cout << "-----Generating WikiGraph-----" << std::endl;
  // open file
  // get a line; decode the first item, decode the second item, add the second to adjlist of firsts
  std::string file = file_to_string(file_name);
  std::vector<std::string> lines;
  SplitString(file, '\n', lines);
  // our dataset has a line of empty space that we can discard
  if (lines.back().empty())
    lines.pop_back(); 

  std::map<std::string, std::string> decoded; // memoize decoding
  for (auto& line : lines) {
    // don't process lines with comments
    if (line[0] == '#') continue;
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

// --------- Algorithms --------------
// DONE: getPathBFS()
std::vector<std::string> WikiGraph::getPathBFS(
    const std::string& start_page, const std::string& end_page) const {

  if (!validStartAndEnd(start_page, end_page)) {
    throw std::invalid_argument("These pages are not in the graph");
  }

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

// TEST: getBetweenCentrality()
double WikiGraph::getBetweenCentrality(const std::string& page) const {
  // Note: will possibly be memoized, either from this function or the other.
  std::map<std::string, double> centralityMap = getCentralityMap();
  if (centralityMap.find(page) != centralityMap.end()) {
    return centralityMap.at(page);
  }
  return -1.0; // INVALID VALUE.
}

// TODO: rankPages()
std::vector<WikiGraph::RankedPage> WikiGraph::rankPages() const {
  std::vector<RankedPage> ranked_pages;
  // ...
  return ranked_pages;
}

// DONE: getCentralityMap()
std::map<std::string, double> WikiGraph::getCentralityMap() const {
  // Adapted from Ulrik Brandes original paper:
  // https://snap.stanford.edu/class/cs224w-readings/brandes01centrality.pdf#page=10

  std::map<std::string, double> centralilty_map;

  // POSSIBLE OPTIMIZATION:
  // Try to read the centrality map from a file, and return it if it exists.
  // centralilty_map = centralityMapFromFile("./centrality/wikigraph_centrality_map.tsv");
  // if (!centralilty_map.empty()) {
  //   return centralilty_map;
  // }

  // Otherwise, run the algorithm / produce the centrality map:
  std::cout << "------ Producing Centrality Map ------" << std::endl;
  const std::vector<std::string>& pages = getPages();
  SafeQueue pages_queue;

  for (const auto& page : pages) {
    centralilty_map[page] = 0.0;
    pages_queue.push(page);
  }

  // Spawn multiple threads to run algorithm
  std::vector<std::thread> threads;
  const size_t THREAD_COUNT = 10;
  for (size_t thread_idx = 0; thread_idx < THREAD_COUNT; ++thread_idx) {
    threads.push_back(std::thread(&WikiGraph::threadHelper, this, std::ref(pages_queue), std::ref(centralilty_map), pages));
  }

  // Wait for the threads to finish
  for (auto& thread : threads) {
    thread.join();
  }

  // centralityMapToFile(centralilty_map, "./output/centrality_map.tsv");

  return centralilty_map; 
}

void WikiGraph::threadHelper(SafeQueue& q, std::map<std::string, double>& centrality_map, const std::vector<std::string>& pages) const {
  std::optional<std::string> curr_page = q.pop();
  while (curr_page.has_value()) {
    displayCentralityProgress(q, pages);
    brandesHelper(curr_page.value(), centrality_map, pages);
    curr_page = q.pop();
  }
}

void WikiGraph::brandesHelper(const std::string& start, std::map<std::string, double>& centrality_map, const std::vector<std::string>& pages) const {
  // One run of the Brandes algorithm for a starting node.
  // std::cout << "Thread starting page: " << start << std::endl;
  std::stack<std::string> S;
  std::unordered_map<std::string, std::vector<std::string>> predecessor;
  for (const auto& page : pages) predecessor[page] = {};
  std::unordered_map<std::string, double> sigma;
  for (const auto& page : pages) sigma[page] = 0.0;
  sigma[start] = 1.0;
  std::unordered_map<std::string, int> dist;
  for (const auto& page : pages) dist[page] = -1;
  dist[start] = 0;
  std::queue<std::string> Q;
  Q.push(start);
  while(!Q.empty()) {
    std::string v = Q.front(); Q.pop();
    S.push(v);
    for (const auto& w : article_map.at(v)) {
      if (dist[w] < 0) {
        Q.push(w);
        dist[w] = dist[v] + 1;
      }
      if (dist[w] == dist[v] + 1) {
        sigma[w] = sigma[w] + sigma[v];
        predecessor[w].push_back(v);
      }
    }
  }

  std::unordered_map<std::string, double> delta;
  for (const auto& page : pages) delta[page] = 0.0;
  while (!S.empty()) {
    std::string w = S.top(); S.pop();
    for (const auto& v : predecessor[w]) {
      delta[v] += ( sigma[v] / sigma[w] ) * (1.0 + delta[w]);
    }
    if (w != start) {
      if (delta[w] != 0.0) {
        mtx.lock(); // Ensure read/write collosion to shared result don't occur.
        centrality_map[w] += delta[w];
        mtx.unlock();
      }
    }
  }
}

//---------- Helper Methods ----------

// TODO: centralityMapToFile()
void WikiGraph::centralityMapToFile(const std::map<std::string, double>& centrality_map, const std::string& file_name) const {
  std::ofstream map_file(file_name);
  if (map_file.is_open()) {
    for (const auto& [page, value] : centrality_map) {
      map_file << page << "\t" << std::setprecision(3) << std::fixed << value << "\n";
    }
  }
}

std::map<std::string, double> WikiGraph::centralityMapFromFile(const std::string& file_name) const {
  std::map<std::string, double> centralilty_map;
  std::string centrality_str = file_to_string(file_name);
  if (!centrality_str.empty()) {
    std::vector<std::string> lines;
    SplitString(centrality_str, '\n', lines);  
    if (lines.back().empty()) lines.pop_back(); 
    for (const auto& line : lines) {
      std::vector<std::string> pair;
      SplitString(line, '\t', pair);
      centralilty_map[pair[0]] = std::stod(pair[1]);
    }
    return centralilty_map;
  }
  return {};
}

void WikiGraph::displayCentralityProgress(const SafeQueue& queue, const std::vector<std::string>& pages) const {
  float pages_to_go = (float)queue.size();
  float total_pages = (float)pages.size();
  float pages_complete = total_pages - pages_to_go;
  float progress = pages_complete  / total_pages;
  std::cout << "[ Progess: " << pages_complete << "/" << total_pages << " ";
  std::cout << int(progress * 100.0) << "% ] \r";
  std::cout.flush();
  if (progress == 1.0) std::cout << std::endl;
}

std::vector<std::pair<std::string, double>> WikiGraph::sortCentralityMap(const std::map<std::string, double>& centrality_map) const {
  std::vector<std::pair<std::string, double>> vector(centrality_map.begin(), centrality_map.end());
  std::sort(vector.begin(), vector.end(), 
  [](const std::pair<std::string, int> &a, const std::pair<std::string, int> &b) {
    return a.second > b.second;
  });
  return vector;
}

bool WikiGraph::validStartAndEnd(const std::string& start_page, const std::string& end_page) const {
  return (article_map.find(start_page) != article_map.end()) && (article_map.find(end_page) != article_map.end());
}

std::vector<std::string> WikiGraph::getPages() const {
  // extract keys from map
  std::vector<std::string> pages;
  std::transform(article_map.begin(), article_map.end(), std::back_inserter(pages),
      [](decltype(article_map)::value_type const &kv) {
          return kv.first;
      });

  return pages;
}
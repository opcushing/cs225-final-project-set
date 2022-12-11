#pragma once

#include <map>
#include <unordered_map>
#include <string>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <optional>

typedef std::map<std::string, std::vector<std::string>> Graph;

class SafeQueue {
  mutable std::mutex mutex_;
  std::queue<std::string> q_;
  bool empty() const {
    return q_.empty();
  }
  public:
  SafeQueue() = default;
  SafeQueue(const SafeQueue&) = delete;
  SafeQueue& operator=(const SafeQueue&) = delete;

  SafeQueue(SafeQueue&& other) {
    std::lock_guard<std::mutex> lock(mutex_);
    q_ = std::move(other.q_);
  }
 
  virtual ~SafeQueue() { }
 
  unsigned long size() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return q_.size();
  }

  std::optional<std::string> pop() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (q_.empty()) {
      return {};
    }
    std::string tmp = q_.front();
    q_.pop();
    return tmp;
  }
 
  void push(const std::string &item) {
    std::lock_guard<std::mutex> lock(mutex_);
    q_.push(item);
  }
};

class WikiGraph {
public:
  struct RankedPage {
    std::string title = "";
    double rank = -1.0;
  };

  WikiGraph() = delete;  // require that data be entered into the graph
  WikiGraph(const std::string& file_name);  // construct from file

  // ------ Algorithms -------

  // SHORTEST PATH (BFS):
  std::vector<std::string> getPathBFS(const std::string& start_page,
                                      const std::string& end_page) const;

  // PAGE CENTRALITY (Brandes Algorithm):
  double getBetweenCentrality(const std::string& page);

  std::map<std::string, double> getCentralityMap();

  void threadHelper(SafeQueue& q, std::map<std::string, double>& centrality_map, const std::vector<std::string>& pages) const;

  void brandesHelper(const std::string& start, std::map<std::string, double>& centrality_map, const std::vector<std::string>& pages) const;

  // PAGE RANK:
  double getPageRank(const std::string& page);

  std::map<std::string, double> rankPages();

  // ------ Helpers ---------

  /**
   * Write the contents of the centrality map to a file.
   * @param centrality_map A map of the pages, and their centrality value.
   * @param file_name Name of the file to write to. (In .tsv format)
  */
  void centralityMapToFile(const std::map<std::string, double>& centrality_map, const std::string& file_name) const;

  /**
   * Produces a centrality map from a pre-computed file.
   * @param file_name Name of the file to read from. (In .tsv format)
   * @returns A map of the pages, and their centrality value.
  */
  std::map<std::string, double> centralityMapFromFile(const std::string& file_name) const;

  /**
   * Displays the current progress of the centrality map.
   * Based off of: https://stackoverflow.com/questions/14539867/how-to-display-a-progress-indicator-in-pure-c-c-cout-printf
   * @param queue
   * @param pages
  */
  void displayCentralityProgress(const SafeQueue& queue, const std::vector<std::string>& pages) const;

  void displayPageRankProgress(const size_t& iter, const size_t& total) const;

  std::vector<std::pair<std::string, double>> getSortedCentrality();

  std::vector<std::pair<std::string, double>> getSortedPageRank();

  Graph getMap() const { return article_map; }  // for tests
  std::vector<std::string> getPages() const;
private:
  bool validStartAndEnd(const std::string& start, const std::string& end) const;

  std::map<std::string, double> centrality_map;

  std::map<std::string, double> page_rank_map;

  Graph article_map;
};
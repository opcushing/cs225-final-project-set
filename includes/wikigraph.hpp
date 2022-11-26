#pragma once

#include <string>
#include <vector>
#include <map>

class WikiGraph {
  public:
    struct RankedPage {
      std::string title = "";
      double rank = -1.0;
    };

    WikiGraph();
    WikiGraph(const std::string& file_name); // construct from file
    ~WikiGraph();
    WikiGraph& operator=(WikiGraph& other); // could possibly have this as deleted.

    std::vector<std::string> getPathBFS(const std::string& from_page, const std::string& to_page) const;
    std::vector<std::string> getPathDijkstras(const std::string& from_page, const std::string& to_page) const;
    std::vector<RankedPage> rankPages() const;
    std::map<std::string, std::vector<std::string>> getMap() { return article_map; } // for tests
  private:
    std::vector<std::string> getAdjacentArticles(const std::string& from_page) const;

    std::map<std::string, std::vector<std::string>> article_map;
};
#pragma once

#include <string>
#include <vector>
#include <map>

typedef std::map<std::string, std::vector<std::string>> Graph;

class WikiGraph {
  public:
    struct RankedPage {
      std::string title = "";
      double rank = -1.0;
    };

    WikiGraph() = delete; // require that data be entered into the graph
    WikiGraph(const std::string& file_name); // construct from file

    std::vector<std::string> getPathBFS(const std::string& from_page, const std::string& to_page) const;
    std::vector<std::string> getPathDijkstras(const std::string& from_page, const std::string& to_page) const;
    std::vector<RankedPage> rankPages() const;
    Graph getMap() { return article_map; } // for tests
  private:
    std::vector<std::string> getAdjacentArticles(const std::string& from_page) const;

    Graph article_map;
};
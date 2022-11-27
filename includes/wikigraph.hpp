#pragma once

#include <map>
#include <string>
#include <vector>

typedef std::map<std::string, std::vector<std::string>> Graph;

class WikiGraph {
public:
  struct RankedPage {
    std::string title = "";
    double rank = -1.0;
  };

  WikiGraph() = delete;  // require that data be entered into the graph
  WikiGraph(const std::string& file_name);  // construct from file

  std::vector<std::string> getPathBFS(const std::string&,
                                      const std::string&) const;
  std::vector<std::string> getPathDijkstras(const std::string&,
                                            const std::string&) const;
  std::vector<RankedPage> rankPages() const;
  Graph getMap() { return article_map; }  // for tests
private:
  std::vector<std::string> getAdjacentArticles(
      const std::string&) const;

  bool validStartAndEnd(const std::string&, const std::string&) const;

  Graph article_map;
};
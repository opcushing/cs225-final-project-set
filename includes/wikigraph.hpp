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

  // ------ Algorithms -------

  std::vector<std::string> getPathBFS(const std::string& start_page,
                                      const std::string& end_page) const;
  std::vector<std::string> getPathDijkstras(const std::string& start_page,
                                            const std::string& end_page) const;
  std::vector<RankedPage> rankPages() const;

  double getBetweenCentrality(const std::string& page) const;

  std::map<std::string, double> getCentralityMap() const;


  // ------ Helpers ---------
  Graph getMap() const { return article_map; }  // for tests
  std::vector<std::string> getPages() const;
private:
  bool validStartAndEnd(const std::string& start, const std::string& end) const;

  Graph article_map;
};
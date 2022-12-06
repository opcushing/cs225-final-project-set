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

  /**
   * Write the contents of the centrality map to a file.
   * @param centrality_map A map of the pages, and their centrality value.
   * @param file_name Name of the file to write to. (Should end with .tsv)
  */
  void centralityMapToFile(const std::map<std::string, double>& centrality_map, const std::string& file_name) const;

  Graph getMap() const { return article_map; }  // for tests
  std::vector<std::string> getPages() const;
private:
  bool validStartAndEnd(const std::string& start, const std::string& end) const;

  Graph article_map;
};
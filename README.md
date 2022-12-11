# Github organization
- The majority of our code can be found in `src/wikigraph.cc`.
- The primary dataset can be found in `datasets/links.tsv`.
- Tests can be found in the `tests` directory.
- The final project presentation can be found [here](https://example.com)
- The results writeup can be found in `results.md`.

# Running instructions
1. Compile the progam using `make`. This will compile to `./bin/exec`.
2. Run `./wikigraph` with arguments:
  - `bfs "A" "B"` for the shortest path from A to B
  - `pagerank -t n` for the top `n` ranked pages
  - `pagerank -p "page"` for the ranking of `page`
  - `brandes -t n` for the top `n` most central pages
  - `brandes -p "page"` for the centrality of `page`
3. You can run tests by compiling (`make tests`) and running `./bin/tests`. We test the following functionalities:
  - The constructor can read from a TSV file properly
  - The BFS can work on a simple example graph
  - BFS finds the shortest path in a graph with multiple paths
  - BFS can handle graph cycles
  - Brandes algorithm works on various test graphs with obvious node centrality
  - PageRank algorithm works on various test graphs with obvious rankings

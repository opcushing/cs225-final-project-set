# Github organization
- The majority of our code can be found in `src/wikigraph.cc`.
- The primary dataset can be found in `datasets/links.tsv`.
- Tests can be found in the `tests` directory.
- The final project presentation can be found [here](https://example.com)
- The results writeup can be found in `results.md`.

# Running instructions
1. Compile the progam using `make`.
2. Run `./wikigraph` with arguments:
  - (we need a proper driver)
3. You can run tests by compiling (`make tests`) and running `./bin/tests`. We test the following functionalities:
  - The constructor can read from a TSV file properly
  - The BFS can work on a simple example graph
  - BFS finds the shortest path in a graph with multiple paths
  - BFS can handle graph cycles
  - Brandes algorithm works on various test graphs with obvious node centrality
  - PageRank algorithm works on various test graphs with obvious rankings

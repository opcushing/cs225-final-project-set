## Leading Question 

####As in the popular webgame [Wikiracer](https://www.thewikigame.com/group), can we find the shortest way to navigate from one Wikipedia article to another through links to other articles?

## Dataset Acquisition

We will be using the following dataset provided by Standford University:   
[wikispeedia_paths-and-graph.tar.gz](http://snap.stanford.edu/data/wikispeedia/wikispeedia_paths-and-graph.tar.gz)   
which was found from:  
[SNAP: Web data: Wikispeedia navigation paths](http://snap.stanford.edu/data/wikispeedia.html)   

This folder of data contains different kinds of data collected, but what we are likely most interested in is the file titled `links.tsv`. This file contains a list of wikipedia article titles, and links to other articles that are referenced / linked in the body of that article.

This dataset was provided from the following sources:  
- Robert West and Jure Leskovec: Human Wayfinding in Information Networks. 21st International World Wide Web Conference (WWW), 2012.  
- Robert West, Joelle Pineau, and Doina Precup: Wikispeedia: An Online Game for Inferring Semantic Distances between Concepts. 21st International Joint Conference on Artificial Intelligence (IJCAI), 2009.  

## Data Format

The data is in tsv format. The first column of the table contains the list of article names, and the second column contains other articles that are linked in the body of the article.  
For example, the Wikipedia article "Agriculture" (in the first column) links to the article "Vegetable" (in the second column). 

## Data Correction

Some of the article titles are URL-encoded for some reason (while others aren't), so we will likely have to do some scripting to convert any URL-encoded article title into it's regular text format.

## Data Storage

We can represent this problem as a *directed* graph of Wikipedia article titles. Each node in our graph is an article, and a directed edge connecting, say, A to B would be mean that the article A has a link to article B contained in it (You can get to article B using a link from A). 
We will store this graph as a `std::map<std::string, std::vector<std::string>>`, with the key being the article title (`std::string`), and the value being a vector of article titles that can be accessed from that given article.

To generate the graph, we will simply have to iterate over the file, parsing the pairs of these article titles (as described above), and link them using our map. Let's call this map `wiki_map`. Using the example from before, we would say that "Agriculture" links to "Vegetable", which would be assigned like: `wiki_map["Agriculture"].push_back("Vegetable");`

## Algorithm

BFS
- Function efficiency: The worst BFS will require going through every link, so the runtime will be O(E) Where E is the number of links in the dataset. Holding every point in queue/set for this worst traversal will also require O(V) space, where V is the number of pages. 
- Function input: (Assume this function has access to the graph data). The function will take in a start page's title and destination page's title as strings. 
- Function output: The function will output a vector of strings where the first element is the start, the final element is the destination, and the interior are the titles of the pages used to get from the start to the end.

Brandes
- Function efficiency: Brandes' algorithm calculates the betweenness centrality index for every page. A naive implementation of this process would require a BFS from every node to every other node, taking about $O(V^3)$ time. Brandes' algorithm still requires doing a BFS, but is slightly more clever, using $O(VE + V^2 \times log(E))$. This is a still an extremely slow process w/o the usage of parallel computation, but its output can be reused, so it will be done upon initialization and memoized for later use.
- Function input: This function just needs the entire graph data to perform the algorithm.
- Function output: The function will output a map from a given page $v$ to its betweenness centrality index. This index $C(v)$, where $v$ is the given page, is defined as $C(v)=\sum_{s,t \in V}\frac{S(s,t|v)}{S(s,t)}$, where $S(s,t|v)$ is the number of shortest paths from $s$ to $t$ which pass through $v$ and $S(s,t)$ is the number of shortest paths from $s$ to $t$. In essence, it describes the overall importance of a possibly visiting a given node when travelling through a shortest path.

Page Rank
- Function efficiency: The page rank algorithm runs in $O(V + E)$ time, where E is the number of edges (links in the dataset) and V is the number of vertices (pages in the dataset). The memory needed to perform the algorithm is at least $O(V^2)$, since we need to represent the data as a graph adjacency matrix to perform the neccesary calculations.
- Function input: This function just needs the entire graph data to perform the algorithm.
- Function output: This function will output the relative strength / popularity of every page, in descending order of popularity. This will likely be a vector of pairs of strings and doubles, the string being the article title, and the double being the article's popularity (0.0 to 1.0).

## Timeline

- Initialize Project
- Be able to load data in. Store it as graph
- Create our first algorithm
- Develop the other two algorithms
- Develop Presentation

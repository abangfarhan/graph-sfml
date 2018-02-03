# Graph SFML

In this repo I created a graph using C++ with the SFML library. This repo is created for educational purpose. For now I only focus on creating the graph. Some definitions that I used:

- A graph is an array of nodes.
- A node, defined by the `Node` class, mainly consisted of `x` and `y` coordinates.
- Each node also has neighbors, which is just a vector of pointers to other nodes.
- When we add a neighbor to a node, that neighbor will also add that node as its neighbor, except if that neighbor already has that node as its neighbor. In other words, there is no direction between the connection of two nodes.

In addition to that, I also use SFML to display the graph.

In the near future, I will use this program to implement algorithms related with graphs.

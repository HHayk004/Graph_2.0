#ifndef GRAPH_LIST_H
#define GRAPH_LIST_H

#include <iostream>
#include <vector>
#include <unordered_set>
#include <stack>
#include <queue>
#include <utility>

class Graph
{
private:
    void printDfsRecH(const size_t& index2, std::vector<bool>& visited) const;
    
    std::vector<size_t> constructPath(const std::vector<size_t>& visited, size_t& dest) const;

public:
    Graph() = default;
    Graph(const std::vector<std::pair<size_t,size_t>>& edges);

    ~Graph() = default;

    void addEdge(const size_t& index1, const size_t& index2);
    void addVertex(const size_t& add_size = 1);

    void removeEdge(const size_t& index, const size_t& index2);

    void clear();

    size_t vertexCount() const;
    size_t edgeCount() const;

    void printDfsIterative(const size_t& index) const;
    void printDfsRecursive(const size_t& index) const;

    void printBfs(const size_t& index) const;

    std::vector<size_t> getShortPath(const size_t& source, size_t dest) const;

private:
    std::vector<std::vector<bool>> vec;
};

#include "graph_matrix.hpp"

#endif
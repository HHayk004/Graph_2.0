#ifndef GRAPH_LIST_H
#define GRAPH_LIST_H

#include <iostream>
#include <vector>
#include <unordered_set>
#include <stack>
#include <queue>
#include <utility>
#include <algorithm>

class Graph
{
private:
    void printDfsRecH(const size_t& index2, std::vector<bool>& visited) const;

    std::vector<size_t> constructPath(const std::vector<size_t>& visited, size_t& dest) const;

    void levelRec(const size_t& index, const size_t& level, std::vector<bool>& visisted, std::vector<size_t>& result) const;

    void allPathesRec(const size_t& source, const size_t& dest, std::vector<std::vector<size_t>>& result, 
                        std::vector<bool>& visited, std::vector<size_t>& path) const;

public:
    Graph() = default;
    Graph(const std::vector<std::pair<size_t,size_t>>& edges);

    ~Graph() = default;

    void addEdge(const size_t& index1, const size_t& index2);
    void addVertex(const size_t& add_size = 1);

    void removeEdge(const size_t& index, const size_t& index2);

    void clear();

    void transpose();

    size_t vertexCount() const;
    size_t edgeCount() const;

    void printDfsIterative(const size_t& index) const;
    void printDfsRecursive(const size_t& index) const;

    void printBfs(const size_t& index) const;

    std::vector<size_t> printLevelDfs(const size_t& index, const size_t& level) const; // have some questions
    std::vector<size_t> printLevelBfs(const size_t& index, size_t level) const;

    std::vector<size_t> getShortPath(const size_t& source, size_t dest) const;

    std::vector<std::vector<size_t>> allPathes(const size_t& source, const size_t& dest) const;

private:
    std::vector<std::unordered_set<size_t>> vec;
};

#include "graph_list.hpp"

#endif
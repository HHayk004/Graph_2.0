#ifndef GRAPH_LIST_H
#define GRAPH_LIST_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <queue>
#include <utility>
#include <algorithm>
#include <limits>

class Graph
{
private:
    class Union
    {
        public:
            Union(const size_t& size);

            size_t findParent(const size_t& u);
            bool unionFind(const size_t& u, const size_t& v);

        private:
            std::vector<size_t> parents;
            std::vector<size_t> sizes;
    };

private:
    void printDfsRecH(const size_t& index2, std::vector<bool>& visited) const;

    std::vector<size_t> constructPath(const std::vector<size_t>& visited, size_t& dest) const;

    void levelRec(const size_t& level, std::vector<bool>& visisted, std::vector<size_t>& result) const;

    void allPathesRec(const size_t& source, const size_t& dest, std::vector<std::vector<size_t>>& result, 
                    std::vector<bool>& visited, std::vector<size_t>& path, size_t w) const;

    bool hasCycleRec(const size_t& index, const size_t& parent,
                    std::vector<bool>& visited, std::vector<bool>& path) const;

    bool topoRec(const size_t& i, std::vector<size_t>& result,
                std::vector<bool>& visited, std::vector<bool>& path) const;

    void kosarajuRec(const size_t& index, std::vector<bool>& visited, std::stack<size_t>& st) const;
    void kosarajuRec(const size_t& index, std::vector<bool>& visited, std::stack<size_t>& st,
                    std::vector<std::vector<size_t>>& result) const;

    void tarjanRec(const size_t& index, std::vector<std::vector<size_t>>& result, std::vector<bool>& visited,
                std::stack<size_t>& st, size_t& ip, std::vector<long long>& ip_vec, std::vector<long long>& ll_vec) const;

public:
    Graph() = default;
    Graph(const std::vector<std::tuple<size_t, size_t, size_t>>& edges, bool mode = 0);
    Graph(const Graph& gr) = default;
    Graph(Graph&& gr) = default;

    ~Graph() = default;

    Graph& operator=(const Graph& gr) = default;
    Graph& operator=(Graph&& gr) = default;

    void addEdge(const size_t& index1, const size_t& index2, const size_t& w);
    void addVertex(const size_t& add_size = 1);

    void removeEdge(const size_t& index, const size_t& index2);
    void removeVertex(const size_t& vertex);

    void clear();

    void transpose();

    size_t vertexCount() const;
    size_t edgeCount() const;

    void printDfsIterative(const size_t& index) const;
    void printDfsRecursive(const size_t& index) const;

    void printBfs(const size_t& index) const;

    void printGraph() const;
    std::vector<size_t> printLevelDfs(const size_t& index, const size_t& level) const;
    std::vector<size_t> printLevelBfs(const size_t& index, size_t level) const;

    std::vector<std::vector<size_t>> allPathes(const size_t& source, const size_t& dest) const;

    bool hasCycle() const;

    std::vector<size_t> topoDfs() const;
    std::vector<size_t> topoKahn() const;

    std::vector<std::vector<size_t>> kosaraju() const;
    std::vector<std::vector<size_t>> tarjan() const;

    std::vector<long long> SSSP(const size_t& source) const;
    std::vector<std::pair<std::vector<size_t>, long long>> dijkstra(const size_t& source) const;
    std::vector<std::pair<std::vector<size_t>, long long>> bellmanFord(const size_t& source) const;

    Graph Prim() const;
    Graph Kruskal() const;

private:
    std::vector<std::unordered_map<size_t, long long>> vec;
    bool mode;
};

#include "graph_list_w.hpp"

#endif
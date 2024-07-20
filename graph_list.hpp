Graph::Graph(const std::vector<std::pair<size_t, size_t>>& edges)
{
    for (auto [index1, index2] : edges)
    {
        addEdge(index1, index2);
    }
}

void Graph::addEdge(const size_t& index1, const size_t& index2)
{
    size_t max = std::max(index1, index2);
    if (max >= vec.size())
    {
        addVertex(max - vec.size() + 1);
    }

    if (vec[index1].find(index2) == vec[index1].end())
    {
        vec[index1].insert(index2);
        vec[index2].insert(index1);
    }
}

void Graph::addVertex(const size_t& add_size)
{
    vec.resize(vec.size() + add_size);
}

void Graph::removeEdge(const size_t& index1, const size_t& index2)
{
    if (vec[index1].find(index2) != vec[index1].end())
    {
        vec[index1].erase(index2);
    }
}

void Graph::clear()
{
    vec.clear();
}

size_t Graph::vertexCount() const
{
    return vec.size();
}

size_t Graph::edgeCount() const
{
    size_t edges_count = 0;
    for (auto elem : vec)
    {
        edges_count += elem.size();
    }

    return edges_count;
}

void Graph::printDfsIterative(const size_t& index) const
{
    std::stack<size_t> indexes;
    indexes.push(index);

    std::vector<bool> visited(vec.size(), false);
    visited[index] = true;

    while (!indexes.empty())
    {
        size_t curr = indexes.top();
        indexes.pop();

        std::cout << curr << ' ';

        for (auto elem : vec[curr])
        {
            if (!visited[elem])
            {
                visited[elem] = true;
                indexes.push(elem);
            }
        }
    }

    std::cout << std::endl;
}

void Graph::printDfsRecH(const size_t& index, std::vector<bool>& visited) const
{
    visited[index] = true;

    std::cout << index << ' ';

    for (auto elem : vec[index])
    {
        if (!visited[elem])
        {
            printDfsRecH(elem, visited);
        }
    }
}

void Graph::printDfsRecursive(const size_t& index) const
{
    std::vector<bool> visited(vec.size(), false);
    printDfsRecH(index, visited);

    std::cout << std::endl;
}

void Graph::printBfs(const size_t& index) const
{
    std::queue<size_t> indexes;
    indexes.push(index);

    std::vector<bool> visited(vec.size(), false);
    visited[index] = true;

    while (!indexes.empty())
    {
        size_t curr = indexes.front();
        indexes.pop();

        std::cout << curr << ' ';

        for (auto elem : vec[curr])
        {
            if (!visited[elem])
            {
                visited[elem] = true;
                indexes.push(elem);
            }
        }
    }

    std::cout << std::endl;
}
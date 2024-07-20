Graph::Graph(const std::vector<std::pair<size_t, size_t>>& edges)
{
    for (const auto& [index1, index2] : edges)
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

    vec[index1][index2] = true;
    vec[index2][index1] = true;
}

void Graph::addVertex(const size_t& add_size)
{
    vec.resize(vec.size() + add_size, std::vector<bool>(vec.size() + add_size, false));
}

void Graph::removeEdge(const size_t& index1, const size_t& index2)
{
    vec[index1][index2] = 0;
    vec[index2][index1] = 0;
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
    for (const auto& elem : vec)
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

        for (int j = 0; j < vec.size(); ++j)
        {
            if (vec[curr][j] && !visited[j])
            {
                visited[j] = true;
                indexes.push(j);
            }
        }
    }

    std::cout << std::endl;
}

void Graph::printDfsRecH(const size_t& index, std::vector<bool>& visited) const
{
    visited[index] = true;

    std::cout << index << ' ';

    for (int i = 0; i < vec.size(); ++i)
    {
        if (vec[index][i] && !visited[i])
        {
            printDfsRecH(i, visited);
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

        for (int i = 0; i < vec.size(); ++i)
        {
            if (vec[curr][i] && !visited[i])
            {
                visited[i] = true;
                indexes.push(i);
            }
        }
    }

    std::cout << std::endl;
}
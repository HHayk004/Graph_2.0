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
        vec[index2].erase(index1);
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

    for (auto& elem : vec[index])
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

    size_t size = 1;
    size_t new_size = 0;
    while (!indexes.empty())
    {
        size_t curr = indexes.front();
        indexes.pop();

        std::cout << curr << ' ';

        for (auto& elem : vec[curr])
        {
            if (!visited[elem])
            {
                ++new_size;
                visited[elem] = true;
                indexes.push(elem);
            }
        }

        --size;
        if (!size)
        {
            size = new_size;
            new_size = 0;
            std::cout << std::endl;
        }
    }

    std::cout << std::endl;
}

void Graph::transpose()
{
    std::vector<std::unordered_set<size_t>> new_graph(vec.size());

    for (int i = 0; i < vec.size(); ++i)
    {
        for (auto it = vec[i].begin(); it != vec[i].end(); ++it)
        {
            new_graph[*it].insert(i);
        }
    }

    vec = std::move(new_graph);
}

std::vector<size_t> Graph::constructPath(const std::vector<size_t>& visited, size_t& dest) const
{
    std::vector<size_t> result;
    while (dest != -1)
    {
        result.push_back(dest);
        dest = visited[dest];
    }

    std::reverse(result.begin(), result.end());

    return result;
}

std::vector<size_t> Graph::getShortPath(const size_t& source, size_t dest) const
{
    std::queue<size_t> indexes;
    indexes.push(source);

    std::vector<size_t> visited(vec.size(), 0);

    visited[source] = -1;

    while (!indexes.empty())
    {
        size_t curr = indexes.front();
        indexes.pop();

        for (auto& elem : vec[curr])
        {
            if (!visited[elem])
            {
                visited[elem] = curr;

                if (elem == dest)
                {
                    return constructPath(visited, dest);
                }

                indexes.push(elem);
            }
        }
    }

    return std::vector<size_t>();
}

void Graph::levelRec(const size_t& level, std::vector<bool>& visited, std::vector<size_t>& result) const
{
    if (level)
    {
        std::vector<size_t> new_level;
        for (int elem : result)
        {
            for (auto i : vec[elem])
            {
                if (!visited[i])
                {
                    new_level.push_back(i);
                    visited[i] = true;
                }
            }
        }

        result = std::move(new_level);
        levelRec(level - 1, visited, result);
    }
}

std::vector<size_t> Graph::printLevelDfs(const size_t& index, const size_t& level) const
{
    std::vector<bool> visited(vec.size(), false);
    visited[index] = true;

    std::vector<size_t> result{index};

    levelRec(level, visited, result);

    return result;
}

std::vector<size_t> Graph::printLevelBfs(const size_t& index, size_t level) const
{
    std::queue<size_t> indexes;
    indexes.push(index);

    std::vector<bool> visited(vec.size(), false);
    visited[index] = true;

    size_t size = 1;
    size_t new_size = 0;
    while (!indexes.empty() && level)
    {
        size_t curr = indexes.front();
        indexes.pop();

        for (auto& elem : vec[curr])
        {
            if (!visited[elem])
            {
                ++new_size;
                visited[elem] = true;
                indexes.push(elem);
            }
        }

        --size;
        if (!size)
        {
            --level;
            size = new_size;
            new_size = 0;
        }
    }

    std::vector<size_t> result;
    while (!indexes.empty())
    {
        result.push_back(indexes.front());
        indexes.pop();
    }

    return result;
}

void Graph::allPathesRec(const size_t& source, const size_t& dest, std::vector<std::vector<size_t>>& result,
                    std::vector<bool>& visited, std::vector<size_t>& path) const
{
    path.push_back(source);
    visited[source] = true;

    if (source == dest)
    {
        result.push_back(path);
    }

    else
    {
        for (auto& elem : vec[source])
        {
            if (!visited[elem])
            {
                allPathesRec(elem, dest, result, visited, path);
            }
        }
    }

    visited[source] = false;
    path.pop_back();
}

std::vector<std::vector<size_t>> Graph::allPathes(const size_t& source, const size_t& dest) const
{
    std::vector<std::vector<size_t>> result;
    std::vector<size_t> path;
    std::vector<bool> visited(vec.size(), false);

    allPathesRec(source, dest, result, visited, path);

    std::sort(result.begin(), result.end(), [](const std::vector<size_t>& val1, const std::vector<size_t>& val2){
        return val1.size() < val2.size();
    });

    return result;
}

bool Graph::hasCycleRec(const size_t& index, const size_t& parent,
                        std::vector<bool>& visited, std::vector<bool>& path) const
{
    path[index] = true;
    visited[index] = true;

    for (auto elem : vec[index])
    {
        if (elem != parent && path[elem] ||
            !visited[elem] && hasCycleRec(elem, index, visited, path))
        {
            return true;
        }
    }

    path[index] = false;
    return false;
}

bool Graph::hasCycle() const
{
    std::vector<bool> visited(vec.size(), false);
    std::vector<bool> path(vec.size(), false);

    for (int i = 0; i < vec.size(); ++i)
    {
        if (!visited[i] && hasCycleRec(i, -1, visited, path))
        {
            return true;
        }
    }

    return false;
}
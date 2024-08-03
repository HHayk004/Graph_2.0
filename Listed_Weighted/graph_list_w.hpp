Graph::Graph(const std::vector<std::tuple<size_t, size_t, size_t>>& edges, bool mode) : mode(mode)
{
    for (const auto& [index1, index2, w] : edges)
    {
        addEdge(index1, index2, w);
    }
}

void Graph::addEdge(const size_t& index1, const size_t& index2, const size_t& w)
{
    size_t max = std::max(index1, index2);
    if (max >= vec.size())
    {
        addVertex(max - vec.size() + 1);
    }

    vec[index1][index2] = w;

    if (!mode)
    {
        vec[index2][index1] = w;
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

        if (!mode)
        {
            vec[index2].erase(index1);
        }
    }
}

void Graph::removeVertex(const size_t& vertex)
{
    if (vertex < vec.size())
    {
        vec.erase(vec.begin() + vertex);
    
        for (int i = 0; i < vec.size(); ++i)
        {
            vec[i].erase(vertex);
            for (auto& val : vec[i])
            {
                if (val.first > vertex)
                {
                    vec[i][val.first - 1] = vec[i][val.first];
                    vec[i].erase(val.first);
                }
            }
        }
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

        for (auto& elem : vec[curr])
        {
            if (!visited[elem.first])
            {
                visited[elem.first] = true;
                indexes.push(elem.first);
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
        if (!visited[elem.first])
        {
            printDfsRecH(elem.first, visited);
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
            if (!visited[elem.first])
            {
                ++new_size;
                visited[elem.first] = true;
                indexes.push(elem.first);
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
    std::vector<std::unordered_map<size_t, size_t>> new_graph(vec.size());

    for (int i = 0; i < vec.size(); ++i)
    {
        for (auto it = vec[i].begin(); it != vec[i].end(); ++it)
        {
            new_graph[it->first][i] = it->second;
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

void Graph::levelRec(const size_t& level, std::vector<bool>& visited, std::vector<size_t>& result) const
{
    if (level)
    {
        std::vector<size_t> new_level;
        for (int elem : result)
        {
            for (auto& i : vec[elem])
            {
                if (!visited[i.first])
                {
                    new_level.push_back(i.first);
                    visited[i.first] = true;
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
            if (!visited[elem.first])
            {
                ++new_size;
                visited[elem.first] = true;
                indexes.push(elem.first);
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
                    std::vector<bool>& visited, std::vector<size_t>& path, size_t w) const
{
    path.push_back(source);
    visited[source] = true;

    if (source == dest)
    {
        path.push_back(w);
        result.push_back(path);
        path.pop_back();
    }

    else
    {
        for (auto& elem : vec[source])
        {
            if (!visited[elem.first])
            {
                allPathesRec(elem.first, dest, result, visited, path, w + elem.second);
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

    allPathesRec(source, dest, result, visited, path, 0);

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

    for (auto& elem : vec[index])
    {
        if (elem.first != parent && path[elem.first] ||
            !visited[elem.first] && hasCycleRec(elem.first, index, visited, path))
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

bool Graph::topoRec(const size_t& i, std::vector<size_t>& result, std::vector<bool>& visited, std::vector<bool>& path) const
{
    visited[i] = true;
    path[i] = true;

    for (auto& elem : vec[i])
    {
        if (!visited[elem.first])
        {
            if (topoRec(elem.first, result, visited, path))
            {
                return true;
            }
        }

        else if (path[elem.first])
        {
            return true;
        }
    }

    result.push_back(i);

    path[i] = false;

    return false;
}

std::vector<size_t> Graph::topoDfs() const
{
    std::vector<bool> path(vec.size(), false);
    std::vector<bool> visited(vec.size(), false);
    std::vector<size_t> result;

    for (int i = 0; i < vec.size(); ++i)
    {
        if (!visited[i] && topoRec(i, result, visited, path))
        {
            return std::vector<size_t>();
        }
    }

    std::reverse(result.begin(), result.end());

    return result;
}

std::vector<size_t> Graph::topoKahn() const
{
    std::vector<size_t> result;
    
    std::vector<size_t> parent(vec.size(), 0);
    for (int i = 0; i < vec.size(); ++i)
    {
        for (auto& elem : vec[i])
        {
            ++parent[elem.first];
        }
    }

    std::queue<size_t> indexes;

    do
    {
        while (!indexes.empty())
        {
            result.push_back(indexes.front());
            indexes.pop();
        }

        for (int i = 0; i < vec.size(); ++i)
        {
            if (!parent[i])
            {
                parent[i] = -1;
                indexes.push(i);

                for (auto& elem : vec[i])
                {
                    --parent[elem.first];
                }
            }
        }
    } while (!indexes.empty());

    if (result.size() != vec.size())
    {
        return std::vector<size_t>();
    }

    return result;
}

void Graph::kosarajuRec(const size_t& index, std::vector<bool>& visited, std::stack<size_t>& st) const
{
    visited[index] = true;

    for (auto& elem : vec[index])
    {
        if (!visited[elem.first])
        {
            kosarajuRec(elem.first, visited, st);
        }
    }

    st.push(index);
}

void Graph::kosarajuRec(const size_t& index, std::vector<bool>& visited, std::stack<size_t>& st, std::vector<std::vector<size_t>>& result) const
{
    visited[index] = true;

    result.back().push_back(index);

    for (auto& elem : vec[index])
    {
        if (!visited[elem.first])
        {
            kosarajuRec(elem.first, visited, st, result);
        }
    }
}

std::vector<std::vector<size_t>> Graph::kosaraju() const
{
    std::vector<bool> visited(vec.size(), false);
    std::stack<size_t> st;

    for (size_t i = 0; i < vec.size(); ++i)
    {
        if (!visited[i])
        {
            kosarajuRec(i, visited, st);
        }
    }

    Graph tp = *this;

    tp.transpose();

    std::vector<std::vector<size_t>> result;

    visited = std::vector<bool>(vec.size(), false);

    while (!st.empty())
    {
        if (!visited[st.top()])
        {
            result.emplace_back();
            tp.kosarajuRec(st.top(), visited, st, result);
        }

        st.pop();
    }

    return result;
}

void Graph::tarjanRec(const size_t& index, std::vector<std::vector<size_t>>& result, std::vector<bool>& visited,
                   std::stack<size_t>& st, size_t& ip, std::vector<long long>& ip_vec, std::vector<long long>& ll_vec) const
    {
        ip_vec[index] = ll_vec[index] = ip++;
        st.push(index);
        visited[index] = true;

        for (auto& elem : vec[index])
        {
            if (ip_vec[elem.first] == -1) 
            {
                tarjanRec(elem.first, result, visited, st, ip, ip_vec, ll_vec);
                ll_vec[index] = std::min(ll_vec[index], ll_vec[elem.first]);
            } 
            
            else if (visited[elem.first])
            {
                ll_vec[index] = std::min(ll_vec[index], ll_vec[elem.first]);
            }
        }

        if (ip_vec[index] == ll_vec[index])
        {
            result.emplace_back();
            while (!st.empty() && st.top() != index)
            {
                result.back().push_back(st.top());
                visited[st.top()] = false;
                st.pop();
            }
            
            if (!st.empty())
            {
                result.back().push_back(st.top());
                st.pop();
            }
        }
    }

std::vector<std::vector<size_t>> Graph::tarjan() const
{
    std::vector<long long> ip_vec(vec.size(), -1);
    std::vector<long long> ll_vec(vec.size(), -1);

    std::vector<bool> visited(vec.size(), false);
    std::stack<size_t> st;

    std::vector<std::vector<size_t>> result;

    size_t ip = 0;
    for (int i = 0; i < vec.size(); ++i)
    {
        if (ip_vec[i] == -1)
        {
            tarjanRec(i, result, visited, st, ip, ip_vec, ll_vec);
        }
    }

    // for (int i = 0; i < vec.size(); ++i)
    // {
    //     std::cout << i << ": " << ip_vec[i] << ' ' << ll_vec[i] << std::endl;
    // } for checking if ll values for each SCC is the same (not)

    return result;
}
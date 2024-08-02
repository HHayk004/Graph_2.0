Graph::Graph(const std::vector<std::pair<size_t, size_t>>& edges, bool mode) : mode(mode)
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

    if (!mode)
    {
        vec[index2][index1] = true;
    }
}

void Graph::addVertex(const size_t& add_size)
{
    for (int i = 0; i < vec.size(); ++i)
    {
        vec[i].resize(vec.size() + add_size);
    }

    vec.resize(vec.size() + add_size, std::vector<bool>(vec.size() + add_size, false));
}

void Graph::removeEdge(const size_t& index1, const size_t& index2)
{
    vec[index1][index2] = false;

    if (!mode)
    {
        vec[index2][index1] = false;
    }
}

void Graph::removeVertex(const size_t& vertex)
{
    if (vertex < vec.size())
    {
        vec.erase(vec.begin() + vertex);
    
        for (int i = 0; i < vec.size(); ++i)
        {
            for (int j = vertex; j < vec[i].size(); ++j)
            {
                if (vec[i][j])
                {
                    if (j > vertex)
                    {
                        std::cout << j << std::endl;
                        vec[i][j] = false;
                        vec[i][j - 1] = true;
                    }

                    else if (j == vertex)
                    {
                        vec[i][vertex] = false;
                    }
                }
            }

            vec[i].pop_back();
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

    size_t size = 1;
    size_t new_size = 0;

    while (!indexes.empty())
    {
        size_t curr = indexes.front();
        indexes.pop();

        std::cout << curr << ' ';

        for (int i = 0; i < vec.size(); ++i)
        {
            if (vec[curr][i] && !visited[i])
            {
                ++new_size;
                visited[i] = true;
                indexes.push(i);
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
    std::vector<std::vector<bool>> new_graph(vec.size(), std::vector<bool>(vec.size(), false));

    for (int i = 0; i < vec.size(); ++i)
    {
        for (int j = 0; j < vec.size(); ++j)
        {
            new_graph[i][j] = vec[j][i];
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

        for (int i = 0; i < vec.size(); ++i)
        {
            if (vec[curr][i] && !visited[i])
            {
                visited[i] = curr;

                if (i == dest)
                {
                    return constructPath(visited, dest);
                }

                indexes.push(i);
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
            for (int i = 0; i < vec.size(); ++i)
            {
                if (vec[elem][i] && !visited[i])
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

        for (int i = 0; i < vec.size(); ++i)
        {
            if (vec[curr][i] && !visited[i])
            {
                ++new_size;
                visited[i] = true;
                indexes.push(i);
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
        for (int i = 0; i < vec.size(); ++i)
        {
            if (vec[source][i] && !visited[i])
            {
                allPathesRec(i, dest, result, visited, path);
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

    for (int elem = 0; elem < vec.size(); ++elem)
    {
        if (vec[index][elem] && 
            (elem != parent && path[elem] ||
            !visited[elem] && hasCycleRec(elem, index, visited, path)))
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

    for (int elem = 0; elem < vec.size(); ++elem)
    {
        if (vec[i][elem])
        {
            if (!visited[elem])
            {
                if (topoRec(elem, result, visited, path))
                {
                    return true;
                }
            }

            else if (path[elem])
            {
                return true;
            }
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
        for (int j = 0; j < vec.size(); ++j)
        {
            if (vec[i][j])
            {
                ++parent[j];
            }
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

                for (int elem = 0; elem < vec.size(); ++elem)
                {
                    if (vec[i][elem])
                    {
                        --parent[elem];
                    }
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

    for (size_t elem = 0; elem < vec.size(); ++elem)
    {
        if (vec[index][elem] && !visited[elem])
        {
            kosarajuRec(elem, visited, st);
        }
    }

    st.push(index);
}

void Graph::kosarajuRec(const size_t& index, std::vector<bool>& visited, std::stack<size_t>& st, std::vector<std::vector<size_t>>& result) const
{
    visited[index] = true;

    result.back().push_back(index);

    for (size_t elem = 0; elem < vec.size(); ++elem)
    {
        if (vec[index][elem] && !visited[elem])
        {
            kosarajuRec(elem, visited, st, result);
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
    std::cout << std::endl;

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

    for (size_t elem = 0; elem < vec.size(); ++elem)
    {
        if (vec[index][elem])
        {
            if (ip_vec[elem] == -1) 
            {
                tarjanRec(elem, result, visited, st, ip, ip_vec, ll_vec);
                ll_vec[index] = std::min(ll_vec[index], ll_vec[elem]);
            }  
            
            else if (visited[elem])
            {
                ll_vec[index] = std::min(ll_vec[index], ll_vec[elem]);
            }
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
#include <iostream>
#include <vector>
#include <queue>
#include <climits>

#define V 6  // Здесь укажите количество вершин в графе

bool bfs(int rGraph[V][V], int s, int t, int parent[])
{
    bool visited[V];
    memset(visited, 0, sizeof(visited));

    std::queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int v = 0; v < V; v++)
        {
            if (!visited[v] && rGraph[u][v] > 0)
            {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    return (visited[t] == true);
}

int fordFulkerson(int graph[V][V], int s, int t)
{
    int u, v;
    int rGraph[V][V];  // Остаточная сеть
    for (u = 0; u < V; u++)
        for (v = 0; v < V; v++)
            rGraph[u][v] = graph[u][v];

    int parent[V];
    int max_flow = 0;

    while (bfs(rGraph, s, t, parent))
    {
        int path_flow = INT_MAX;
        for (v = t; v != s; v = parent[v])
        {
            u = parent[v];
            path_flow = std::min(path_flow, rGraph[u][v]);
        }

        for (v = t; v != s; v = parent[v])
        {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        max_flow += path_flow;

        // Вывод состояния графа
        std::cout << "Состояние графа после увеличения потока на " << path_flow << ":" << std::endl;
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                std::cout << rGraph[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    return max_flow;
}

int main()
{
    setlocale(LC_ALL, "RUS");
    int graph[V][V];
    std::cout << "Введите матрицу пропускных способностей для графа (" << V << "x" << V << "):" << std::endl;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            std::cin >> graph[i][j];
        }
    }
    int source, sink;
    std::cout << "Введите исток и сток: ";
    std::cin >> source >> sink;

    // Вызов алгоритма Форда-Фалкерсона
    std::cout << "Максимальный поток в графе: " << fordFulkerson(graph, source, sink) << std::endl;

    return 0;
}
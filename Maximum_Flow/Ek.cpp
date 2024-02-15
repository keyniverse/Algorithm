#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <windows.h>
#include <thread>

using namespace std;

class Graph{
public:
    vector<int> vertices;
    vector<vector<int>> edges;
    Graph() {};
    Graph(int n);
    int maxFlowBFS(int s, int t);
    bool bfs(vector<vector<int>> residual, int s, int t, int* predecessor, int* flow);
};

bool Graph::bfs(vector<vector<int>> residual, int s, int t, int* predecessor, int* flow){
    int visited[vertices.size()];
    for (int i = 0;i<vertices.size();i++){
        visited[i] = 0;
        predecessor[i] = -1;
    }

    queue<int> q;
    q.push(s);
    visited[s] = 1;
    int cur = q.front();
    while (cur != t && !q.empty()){
        for (int i = 0;i<vertices.size();i++){
            if (residual.at(cur).at(i) != 0 && visited[i] == 0){
                q.push(i);
                visited[i] = 1;
                predecessor[i] = cur;
            }
        }
        q.pop();
        cur = q.front();
    }

    if (visited[t] == 0) return false;

    *flow = 0x7FFFFFFF;
    for (int i = t;predecessor[i] != -1;i = predecessor[i]){
        if (residual.at(predecessor[i]).at(i) < *flow){
            *flow = residual.at(predecessor[i]).at(i);
        }
    }
    return true;
}

int Graph::maxFlowBFS(int s, int t){
    vector<vector<int>> residual(edges);
    int maxFlow = 0;
    int flow;
    int predecessor[vertices.size()];

    while (bfs(residual, s, t, predecessor, &flow)){
        maxFlow += flow;
        for (int i = t;i != s;i = predecessor[i]){
            int temp = predecessor[i];
            residual.at(temp).at(i) -= flow;
            residual.at(i).at(temp) += flow;
        }
    }
    return maxFlow;
}

Graph::Graph(int n){
    edges.resize(n);
    for (int i = 0;i<n;i++)
        edges.at(i).resize(n);
}

int main()
{
    int n, s, t, c, from, to, w;
    cin >> n >> s >> t >> c;
    Graph graph(n);

    for (int i = 0;i<n;i++) {
        graph.vertices.push_back(i+1);
    }
    for(int i = 0;i < c;i++) {
        cin >> from >> to >> w;
        graph.edges.at(from-1).at(to-1) = w;
    }
    int temp = graph.maxFlowBFS(s-1, t-1);
    cout << temp << '\n';
    return 0;
}

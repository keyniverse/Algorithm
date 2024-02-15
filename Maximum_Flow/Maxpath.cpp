#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <windows.h>
#include <thread>

using namespace std;

class Edge{
public:
    int from, to, capacity;
    Edge() {};
    Edge(int from, int to, int capacity);
};

Edge::Edge(int from, int to, int capacity){
    this->from = from;
    this->to = to;
    this->capacity = capacity;
}

struct cmp{
    bool operator() (const Edge &lhs, const Edge &rhs){
        return lhs.capacity < rhs.capacity;
    }
};

class Graph{
public:
    vector<int> vertices;
    vector<vector<int>> edges;
    Graph() {};
    Graph(int n);
    int getFlow(const vector<vector<int>> &residual, int* predecessor, int t);
    int maxFlowPrim(int s, int t);
    bool prim(const vector<vector<int>> &residual, int s, int t, int* predecessor, int* flow);
};

int Graph::getFlow(const vector<vector<int>> &residual, int* predecessor, int t){
    int flow = 0x7FFFFFFF;
    for (int i = t;predecessor[i] != -1;i = predecessor[i]){
        if (residual.at(predecessor[i]).at(i) < flow){
            flow = residual.at(predecessor[i]).at(i);
        }
    }
    return flow;
}

bool Graph::prim(const vector<vector<int>> &residual, int s, int t, int* predecessor, int* flow){
    int visited[vertices.size()];
    for (int i = 0;i<vertices.size();i++){
        visited[i] = 0;
        predecessor[i] = -1;
    }

    priority_queue<Edge, vector<Edge>, cmp> pq;
    visited[s] = 1;
    int cur = s;
    while (cur != t){
        for (int i = 0;i<vertices.size();i++){
            if (residual.at(cur).at(i) != 0 && visited[i] == 0){
                pq.push(Edge(cur, i, residual.at(cur).at(i)));
            }
        }
        if (pq.empty())
            break;
        Edge edge;
        do{
            edge = pq.top();
            pq.pop();
        }while (visited[edge.to] != 0 && !pq.empty());
        if (visited[edge.to] != 0) break;
        predecessor[edge.to] = edge.from;
        visited[edge.to] = 1;
        cur = edge.to;
    }
    if (visited[t] == 0) return false;

    *flow = getFlow(residual, predecessor, t);
    return true;
}

int Graph::maxFlowPrim(int s, int t){
    vector<vector<int>> residual(edges);
    int maxFlow = 0;
    int flow;
    int predecessor[vertices.size()];

    while (prim(residual, s, t, predecessor, &flow)){
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
    int temp = graph.maxFlowPrim(s-1, t-1);
    cout << temp << '\n';
    return 0;
}

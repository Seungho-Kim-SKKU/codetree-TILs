#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

#define endl '\n'
#define MAX 3000000

typedef struct Node {
    int i;
    vector<int> to;
    vector<int> weight;
    int fromStart;
} node;

typedef struct Product {
    int rev;
    int dest;
    int dist;
} product;

int Q;
int op;
int n, m;
int v, u, w;
int id, rev, dest, dist;
int start = 0;

int curId = -1;
int curMax = -1;

vector<Node> graph;
unordered_map<int, Product> list;

void initGraph(int n) {
    for (int i = 0; i < n; i++) {
        graph.push_back({i});
        graph[i].fromStart = MAX;
    }
    return;
}

void initFromStart(int n) {
    for (int i = 0; i < n; i++) {
        graph[i].fromStart = MAX;
    }
}

void calculateDist(int start) {
    bool visit[n] = { 0, };

    queue<int> q;

    graph[start].fromStart = 0;

    int cur;
    int to;
    int curSize = graph[start].to.size();

    for (int i = 0; i < curSize; i++) {
        visit[start] = 1;
        to = graph[start].to[i];
        if (!visit[to]) {
            q.push(to);
            visit[to] = 1;
        }
        w = graph[start].fromStart + graph[start].weight[i];
        if (w < graph[to].fromStart) {
            graph[to].fromStart = w;
        }         
    }

    while (!q.empty()) {
        cur = q.front();
        q.pop();
        curSize = graph[cur].to.size();

        for (int i = 0; i < curSize; i++) {
            to = graph[cur].to[i];
            if (!visit[to]) {
                q.push(to);
                visit[to] = 1;
            }            
            w = graph[cur].fromStart + graph[cur].weight[i];

            if (w < graph[to].fromStart) {
                graph[to].fromStart = w;
            }            
        }
    }
    // cout << endl;
    // for (int i = 0; i < n; i++) {
    //     cout << graph[i].fromStart << endl;
    // }
    // cout << endl;
}

void calculateMax() {
    for (auto& it: list) {
        // cout << it.first << " " << it.second.rev << " " << it.second.dist << endl;
        int cur = it.second.rev - it.second.dist;
        if (cur > curMax) {
            curId = it.first;
            curMax = cur;
        }
        else if (cur == curMax) {
            if (it.first < curId) {
                curId = it.first;
            }
        }
    }
}

int main() {
    cin >> Q;

    for (int i = 0; i < Q; i++) {
        cin >> op;

        if (op == 100) {
            cin >> n >> m;
            initGraph(n);

            for (int j = 0; j < m; j++) {
                cin >> v >> u >> w;
                graph[v].to.push_back(u);
                graph[v].weight.push_back(w);
                graph[u].to.push_back(v);
                graph[u].weight.push_back(w);
            }
            calculateDist(start);
        }
        else if (op == 200) {
            cin >> id >> rev >> dest;

            dist = graph[dest].fromStart;

            list[id] = {rev, dest, dist};
        }
        else if (op == 300) {
            cin >> id;
            if (list.find(id) != list.end()) {
                list.erase(id);
                curId = -1;
                curMax = -1;                
            }
        }        
        else if (op == 400) {           
            calculateMax();

            if (curMax != -1) {
                list.erase(curId);
                cout << curId << endl;
                curId = -1;
                curMax = -1;
            }
            else {
                cout << curId << endl;
            }
            // cout << 123 << endl;
        }
        else if (op == 500) {
            cin >> start;
            initFromStart(n);
            
            calculateDist(start);

            for (auto& it: list) {
                it.second.dist = graph[it.second.dest].fromStart;
                // cout << it.first << " " << it.second.dist << endl;
            }
        }
        else {
            continue;
        }
    }
    
    return 0;
}
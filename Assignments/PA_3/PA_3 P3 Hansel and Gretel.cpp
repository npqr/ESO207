/* PA_3 P3 Hansel and Gretel */
/* Name : Nevish Pathe */
/* Roll No. 220757*/
/* Handle : npqrrr */

#include <bits/stdc++.h>
using namespace std;

vector<int> G[200005];

struct LCA {
    vector<int> height, euler, first, segtree;
    vector<bool> visited;
    int n;

    LCA(int root = 0) {
        n = 200005;
        height.resize(n);
        first.resize(n);
        euler.reserve(n * 2);
        visited.assign(n, false);
        dfs(root);
        int m = euler.size();
        segtree.resize(m * 4);
        build(1, 0, m - 1);
    }

    void dfs(int node, int h = 0) {
        visited[node] = true;
        height[node] = h;
        first[node] = euler.size();
        euler.push_back(node);
        for (auto to : G[node]) {
            if (!visited[to]) {
                dfs(to, h + 1);
                euler.push_back(node);
            }
        }
    }

    void build(int node, int b, int e) {
        if (b == e) {
            segtree[node] = euler[b];
        } else {
            int mid = (b + e) / 2;
            build(node << 1, b, mid);
            build(node << 1 | 1, mid + 1, e);
            int l = segtree[node << 1], r = segtree[node << 1 | 1];
            segtree[node] = (height[l] < height[r]) ? l : r;
        }
    }

    int query(int node, int b, int e, int L, int R) {
        if (b > R || e < L)
            return -1;
        if (b >= L && e <= R)
            return segtree[node];
        int mid = (b + e) >> 1;

        int left = query(node << 1, b, mid, L, R);
        int right = query(node << 1 | 1, mid + 1, e, L, R);
        if (left == -1) return right;
        if (right == -1) return left;
        return height[left] < height[right] ? left : right;
    }

    int lca(int u, int v) {
        int left = first[u], right = first[v];
        if (left > right)
            swap(left, right);
        return query(1, 0, euler.size() - 1, left, right);
    }
};

class Graph {
public:
    Graph(int vertices) : V(vertices) {
        G.resize(V);
    }

    void printGraph() {
        for (int v = 0; v < V; ++v) {
            std::cout << "Vertex " << v << ": ";
            for (int neighbor : G[v]) {
                std::cout << neighbor << " ";
            }
            std::cout << std::endl;
        }
    }

    void countEdges(vector<int>& edgyy) {
        for (int v = 0; v < V; ++v) {
            for (int neighbor : G[v]) {
                edgyy[v]++;
            }
        }
    }

    bool BFS_BP(int startVertex, std::vector<int>& color) {
        std::queue<int> q;
        bool bp = true;
        color[startVertex] = 1;
        vector<int> visited(V, false);
        q.push(startVertex);
        visited[startVertex] = true;
        // for(int i = 0; i <  V; i++) cout << color[i] << " ";
        // cout << "\n XOXOXO \n";
        while (!q.empty()) {
            int currentVertex = q.front();
            q.pop();
            visited[currentVertex] = true;
            // std::cout << currentVertex << " ";

            for (int neighbor : G[currentVertex]) {
                // cout << currentVertex << "::s" << neighbor << "\n";
                if (color[neighbor] == -1) {
                    visited[neighbor] = true;
                    //cout << color[currentVertex] << "::s" << color[neighbor] << "\n";
                    color[neighbor] = (1+(color[currentVertex])) % 2;
                    //cout << color[currentVertex] << "::t" << color[neighbor] << "\n";
                    q.push(neighbor);
                }
                else if(color[currentVertex] == color[neighbor])
                return false;
            }

        }
        // cout << " BIparrt?" << bp << "\n";
            // cout << "YES\n";
            // for(int i = 0; i < V; i++){
            //     if(visited[i]) cout << color[V] << " ";
            // }
     

        return true;
    }

    bool BBFFSS(vector<int>& color)
    {        
        for(int i = 0; i < V; i++)
        {
            if(color[i] == -1)
            {
                if(BFS_BP(i, color) == false) return false;
            }
        }
        return true;
    }

    /*
    void aDFS(int current, int parent, vector<bool>& visited, vector<int>& cycle, vector<int>& rang) {
    visited[current] = true;
    cycle.push_back(current);
    
    for (int neighbor : G[current]) {
        if (neighbor == parent) continue;
        
        if (!visited[neighbor]) {
            // Explore unvisited neighbors
            DFS(neighbor, current, visited, cycle, rang);
        } else {
            // Found a cycle
            for (int i = cycle.size() - 1; i >= 0; --i) {
                    rang[cycle[i]] = 1;
                    if (cycle[i] == neighbor) break;
                }
        }
    }
    
    cycle.pop_back();
    }
    */



private:
    int V;  // Number of vertices
    vector<vector<int>> G;
};

void getparents(int u, int par, int parent[][20], int& journeys, int pickvert[], int dropvert[]){
    pickvert[u] = ++journeys;
    parent[u][0] = par;
    for(int i = 1; i < 20; i++)
        parent[u][i] = parent[parent[u][i-1]][i-1];
    for(int v : G[u])
        if(v != par)
            getparents(v, u, parent, journeys, pickvert, dropvert);
    dropvert[u] = ++journeys;
}

void getFinalCrumbs(int u, int parent[][20], int crumbs[]){
    for(int v : G[u]){
        if(v != parent[u][0]){
            getFinalCrumbs(v, parent, crumbs);
            crumbs[u] += crumbs[v];
        }
    }
}

bool anc(int u, int v, int pickvert[], int dropvert[]){
    return pickvert[u] <= pickvert[v] && dropvert[u] >= dropvert[v];
}

int lca(int u, int v, int parent[][20], int pickvert[], int dropvert[]){
    if(anc(u, v, pickvert, dropvert))  return u;
    if(anc(v, u, pickvert, dropvert))  return v;
    for(int i = 19; i >= 0; i--)
        if(!anc(parent[u][i], v, pickvert, dropvert))
            u = parent[u][i];
    return parent[u][0];
}

void dropCrumbs(int K, LCA& lca, int crumbs[], int parent[][20])
{
    int L, R;
    for(int i = 0; i < K; i++){
        cin >> L >> R;
        int l = lca.lca(L, R);
        if(l != 1) crumbs[parent[l][0]]--;
        crumbs[L]++; crumbs[R]++; crumbs[l]--;
    }
}

int main(){
    int N, K;
    cin >> N >> K;
    vector<int> A(N-1), B(N-1);
    
    int crumbs[200005], parent[200005][20], journeys, pickvert[200005], dropvert[200005];

    for(int i = 0; i < N-1; i++) {cin >> A[i]; }
    for(int i = 0; i < N-1; i++) {cin >> B[i]; }

    for(int i = 0; i < N-1; i++) {
        G[A[i]].push_back(B[i]);
        G[B[i]].push_back(A[i]);
        }

    getparents(1, 1, parent, journeys, pickvert, dropvert);
    LCA lca(1);
    dropCrumbs(K, lca, crumbs, parent);
    getFinalCrumbs(1, parent, crumbs);

    for(int i = 1; i <= N; i++) cout << crumbs[i] << " ";
    cout << "\n";
    
    }
/* PA_3 P1 Red-Green Colourblind */
/* Name : Nevish Pathe */
/* Roll No. 220757*/
/* Handle : npqrrr */

#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

class Graph {
public:
    Graph(int vertices) : V(vertices) {
        adjacencyList.resize(V);
    }

    void addEdge(int v, int w) {
        adjacencyList[v].push_back(w);
        adjacencyList[w].push_back(v);  
    }

    void printGraph() {
        for (int v = 0; v < V; ++v) {
            std::cout << "Vertex " << v << ": ";
            for (int neighbor : adjacencyList[v]) {
                std::cout << neighbor << " ";
            }
            std::cout << std::endl;
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

            for (int neighbor : adjacencyList[currentVertex]) {
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

private:
    int V; 
    std::vector<std::vector<int>> adjacencyList;
};

void IsSamLying(){
    int N, M;
    cin >> N >> M;

    int l, r; 
    
    Graph g(N);
    vector<int> color(N+1, -1);

    for(int i = 0; i < M; i++) {cin >> l >> r; g.addEdge(l-1,r-1); }
    
    if(g.BBFFSS(color)) 
    {
        cout << "YES\n";
        for(int i = 0; i <  N; i++) cout << color[i] + 1 << " ";
    }
    else cout << "NO\n";
}

int main(){
    IsSamLying();
    return 0;
}






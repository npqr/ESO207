/* PA_3 P2 Cycling Frenzy */
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
        auto it = std::find(
                    adjacencyList[v].begin(),
                    adjacencyList[v].end(),
                    w) ;

        if(it == adjacencyList[v].end()){
        adjacencyList[v].push_back(w);
        adjacencyList[w].push_back(v); 
        }
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

    void countEdges(vector<int>& edgyy) {
        for (int v = 0; v < V; ++v) {
            for (int neighbor : adjacencyList[v]) {
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

    void dfs(int s,vector<pair<int,int>> &bridges, vector<bool>& visited, vector<int>&low, vector<int>&tin, vector<int>& edges, int timer, int p = -1){
        visited[s]=true;
        low[s]=tin[s]=timer++;        
        for(auto x: adjacencyList[s]){
            //cout << "visiting.." << x << "of " << s << "and p is " << p <<" \n";
            if(x==p) continue;          
            if(visited[x]) 
            {
                //cout << "visited " << x << ".\n";
            low[s]=min(low[s],tin[x]);
            }
            else{
                dfs(x, bridges, visited, low, tin, edges, timer, s);
                low[s]=min(low[s],low[x]);
                //cout << " current " << low[x] << "?<" << tin[s] <<"\n";
                if(low[x]>tin[s]){
                    bridges.push_back({s,x});
                    edges[s]++;
                    edges[x]++;
                    //cout << "( " << s << ", " << x << " )" << "\n";
                }
            }
        }
    }
        
    void findBridges(vector<pair<int,int>> &bridges, vector<int>&low, vector<int>&tin, vector<bool>& visited, vector<int>& edges){
        int n = V;
        low.resize(n,-1); 
        tin.resize(n,-1);
        visited.resize(n,false);
        int k = -1;
        int timer = 0;
        //cout<<"yeh bh nhi?\n";
        for(int i=0;i<n;i++){
            //cout << "hojabhai\n";
            if(!visited[i])
                dfs(i,bridges,visited,low,tin,edges, timer, k);
        }
    }


private:
    int V; 
    std::vector<std::vector<int>> adjacencyList;
};

void CycFren(){
    int N, M;
    cin >> N >> M;

    vector<int> A(M), B(M);
    vector<int> rang(N, 0);
    Graph g(N);

    for(int i = 0; i < M; i++) {cin >> A[i]; }
    for(int i = 0; i < M; i++) {cin >> B[i]; }
    
    // for(int i = 1; i <= N; i++) {cout << A[i] << " ";}    
    
    for(int i = 0; i < M; i++) {g.addEdge(A[i]-1,B[i]-1);}
    //g.printGraph();
    
    vector<int> low, tin;
    vector<int> edges(N, 0);
    vector<int> edgyy(N, 0);
    vector<bool> visited;
    vector<pair<int, int>> bridges;

    //g.findCycles(rang);

    g.findBridges(bridges, low, tin, visited, edges);
    g.countEdges(edgyy);

    //for(int i = 0; i < N; i++) cout << edgyy[i] << " ";
    //cout << "\n";
    //for(int i = 0; i < N; i++) cout << edges[i] << " ";

    for(int i = 0; i < N; i++) 
    {
        if(edgyy[i] - edges[i] > 0) cout << 1 << " ";
        else cout << 0 << " ";
    }

}

int main(){
    CycFren();
    return 0;
}

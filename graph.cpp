#include <iostream>
#include <queue>
#include <algorithm>
#include <climits>
#include <utility>

using namespace std;

#include "graph.h"

Graph::Graph() { 
  string a;
  int N, M = 0;
  cin >> N >> M;        
  Adj.resize(N);
  for (int i = 0; i < M; i++) {
    int u, v, w = 0;
    cin >> a >> u >> v >> w;
    edge e(u, v, w);
    Adj[u].push_back(e);
    //for transpose just flip u and v. just make another adj
  }
  colors.resize(N);
  distance.resize(N); 
  parent.resize(N);
  stamps.resize(N);
  size = N;
}

void Graph::printLevels(int s) {
  queue< pair<int, int> > aq;
  for (int i = 0; i < size; i++) { 
    distance[i] = INT_MAX;
    parent[i] = i;
  } 
  distance[s] = 0;
  pair <int, int> u (0, 0);
  pair <int, int> p (s, distance[s]);
  aq.push (p);
  int current_level = p.second; 
  while(!aq.empty()) { 
    u = aq.front();
    aq.pop();
    if (current_level != u.second) {  
      cout << '\n';
      current_level = u.second;
    } 
    cout << u.first << " ";
    
    for (int i = 0; i < Adj[u.first].size(); i++) {
      int v = Adj[u.first][i].neighbor;
      if (distance[v] == INT_MAX) {
        distance[v] = distance[u.first] + 1;
        parent[v] = u.first;
        pair<int, int> tmp (v, distance[v]);
        aq.push(tmp);
      } 
    }
  }
  cout << '\n';
}  

void Graph::bfs(int s) { 
  queue<int> q;
  for (int i = 0; i < size; i++) {
    distance[i] = INT_MAX;    
    parent[i] = i;
  }
  distance[s] = 0;
  int u = 0;
  q.push(s);
  while(!q.empty()) { 
    u = q.front();
    q.pop();
    cout << u << " ";
    
    for (int i = 0; i < Adj[u].size(); i++) { 
      int v = Adj[u][i].neighbor;
      if (distance[v] == INT_MAX) { 
        distance[v] = distance[u] + 1;
        parent[v] = u;
        q.push(v);  
      }
    }
  } 
  cout << '\n';
}

    
void Graph::dfsVisit(int u, int &t) {
  cout << u << " ";
  colors[u] = 'G';
  stamps[u].d = t;   //distance time of u
  t++;
  for (int i = 0; i < (int) Adj[u].size(); i++) { 
    int child = Adj[u][i].neighbor;
    if (colors[child] == 'W') { 
      parent[child] = u;
      dfsVisit(child, t);
    } 
  } 
  stamps[u].f = t;   //finish time is put into stamps
  t++;
  colors[u] = 'B';
} 

void Graph::dfs() { 
  int t = 0;
  for (int i = 0; i < size; i++) { 
    colors[i] = 'W';
    parent[i] = i;
  } 
  for (int i = 0; i < size; i++) { 
    if (colors[i] == 'W') 
      dfsVisit(i, t);//t is passed by reference
  } 
 cout << '\n';
}

void Graph::getPath(int u, int v, vector<int> &p) { 
  if (u == v) {
    p.push_back(u);
    return;
  } 
  getPath(u, parent[v], p);
  p.push_back(v);
}

void Graph::longestVisit(int u, int &t, int &longest) {
  //cout << u << " ";
  colors[u] = 'G';
  stamps[u].d = t;
  distance[0] = 0;
  int p = parent[u];
  distance[u] = distance[p] + 1;
  longest++;
  
  t++;
  for (int i = 0; i < (int) Adj[u].size(); i++) { 
    int child = Adj[u][i].neighbor;
    if (colors[child] == 'G') { 
      cycleLengths.push_back(longest);    
      //longest = 0;
    } 
        //return;
    if (colors[child] == 'W') { 
      parent[child] = u;
      longestVisit(child, t, longest);
    }
  } 
  stamps[u].f = t;   //finish time is put into stamps
  t++;
  colors[u] = 'B';
} 

void Graph::longestdfs() { 
  int t = 0;
  int longest = 0;
  for (int i = 0; i < size; i++) { 
    colors[i] = 'W';
    parent[i] = i;
    distance[i] = INT_MAX;
  } 
  for (int i = 0; i < size; i++) { 
    if (colors[i] == 'W') 
      longestVisit(i, t, longest);//t is passed by reference
  }
  cout << "longest is " << longest; 
  cout << '\n';
  cout << "printing out cycles length" << endl;
  for (int i = 0; i < cycleLengths.size(); i++) {
    cout << cycleLengths[i] << endl;
  } 
}


void Graph::printPath(int v) { 
  if (v == parent[v]) { 
    cout << v << " ";
    return;
  } 
  printPath(parent[v]);
  cout << v << " ";
} 

bool Graph::isCycle() {
  bool answer = false;
  int t = 0;
  for (int i = 0; i < size; i++) {
    colors[i] = 'W';
    //parent[i] = i;
  } 
  for (int i = 0; i < size; i++) { 
    if (colors[i] == 'W') { 
      answer = isCycleVisit(i, t); 
      if (answer) 
        return true;
    } 
  }
return false;
} 

bool Graph::isCycleVisit(int u, int &t) {
  colors[u] = 'G';
  stamps[u].d = t;
  t++;
  for (int i = 0; i < (int) Adj[u].size(); i++) { 
    int child = Adj[u][i].neighbor;
    if (colors[child] == 'W') { 
      isCycleVisit(child, t);
    }
    if (colors[child] == 'G') { 
      return true;
    } 
  } 
  stamps[u].f = t;
  t++;
  colors[u] = 'B';

return false;
} 

void Graph::printDistance() {
  cout << "printing distances below" << endl;
  for (int i = 0; i < distance.size(); i++) 
    cout << distance[i] << " ";

  cout << '\n';
}

void Graph::printDandFtime() { 
  cout << '\n';
  cout << "discover" << endl;
  for (int i = 0; i < stamps.size(); i++) {
    cout << stamps[i].d << " ";
  } cout << endl;
  cout << "finish time" << endl;
  for (int i = 0; i < stamps.size(); i++) {
    cout << stamps[i].f << " ";
  } cout << endl;
} 

void Graph::printGraph() {
  cout << "print adjacency" << endl;
  for (int i = 0; i < Adj.size(); i++) {
    cout << i << ": ";
    for (int n = 0; n < Adj[i].size(); n++) {
      cout << Adj[i][n].neighbor << " ";
    } cout << '\n';
  }
}







#include "timestamp.h"

#ifndef GRAPH_H
#define GRAPH_H
using namespace std;

struct edge {
  int source;//edge is from this node to neighbor 
  int neighbor;//adjacent node
  int w;  //keeps auxiliary info
  edge() {source = 0; neighbor = 0; w = 0;}
  edge(int i, int j) {source = 0; neighbor = i; w = j;}
  edge(int from, int to, int aweight) {
    source = from;//edge is from this node
    neighbor = to;//edge is to this node
    w = aweight; //weight of this edge
  }
};

class Graph { 

  public:
    Graph(); 
    void bfs(int s); 
    void printPath(int v);
    void dfsVisit(int u, int &t);
    void dfs();
    void printLevels(int s);
    bool isCycle();
    bool isCycleVisit(int u, int &t);
    void longestdfs();
    void longestVisit(int u, int &t, int &longest);
    void printDistance();
    void printDandFtime();
    void printGraph();
    void getPath(int u, int v, vector<int> &p);
  private:
    vector<int> cycleLengths;
    vector<vector <edge> > Adj;
    vector<int> parent;  //for BFS
    vector<int> distance;  //for BFS and DFS
    vector<char> colors; //for DFS
    vector<TimeStamp> stamps; //for DFS
    int size;  //total vertices
};

#endif

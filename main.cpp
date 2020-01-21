#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<utility>
#include<cmath>
using namespace std;

#include "graph.h"

int main(){
    Graph ag;

    cout << "Testing BFS on node 0." << endl;
    ag.bfs(0);
    //cout << "Testing print path on node 3." << endl;
    //ag.printPath(3);
    //cout << endl;
    //cout << "Testing print levels on node 0." << endl;
    //ag.printLevels(0);
    cout << "Testing DFS." << endl;
    ag.dfs();
    //vector<int>p;
    //ag.getPath(0,2,p);
    //for (int i = 0; i < p.size(); i++) cout << p[i] << " ";
    //cout << '\n';
    //cout << "Testing to check if a graph has a cycle." << endl;
    //bool res = ag.isCycle();
    //if(res){
    //   cout << "Graph has a cycle." << endl;

    //}
    //else
    //cout << "Graph does not have a cycle." << endl;
    
    ag.printGraph();
    ag.longestdfs();
    ag.printDistance();
    ag.printDandFtime();  
  return 0;
}

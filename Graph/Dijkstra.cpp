#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#define INF 2000000000

using namespace std;

class point{
  public:
    int id;
    short visited;
    int parent;
    int d;
    point(int i) 
      : id(i), visited(0), d(INF)
    {}
    bool operator< (const point& p) const {
      return (d<p.d);
    }
};

class edge {
  public:
  int u;
  int v;
  int w;
  edge(int uu, int vv, int ww) 
    : u(uu), v(vv), w(ww) 
  {}
  bool operator< (const edge& e) const {
    return (w>e.w); //because priority_queue starts with highest element, but we prefer cheapest
  }
};
vector<vector<edge> > graph;
int N;
/*Dijkstra: single source shortest paths from vertex with id s
  in a graph with non-negative weights */
void dijkstra(int s, vector<point> & vertices) {
  vertices[s].d=0;
  priority_queue<point> q; //in increasing order of known distance from s
  q.push(vertices[s]);
  while(!q.empty()) {
    point p=q.front();
    q.pop();
    if(!vertices[p.id].visited) {
      vertices[p.id].visited=true;
      for(unsigned int i=0; i<graph[p.id].size(); i++) {
        edge e=graph[p.id][i];
        if(!vertices[e.v].visited && vertices[e.v].d>e.w+vertices[p.id].d) {
          vertices[e.v].d=e.w+vertices[p.id].d;
          vertices[e.v].parent=p.id;
          q.push(vertices[e.v]);
        }
      }
    }
  }
}

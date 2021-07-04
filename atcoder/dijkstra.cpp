#include <iostream>
#include <vector>
#include <queue>

typedef std::pair<int, int> p; // distance, vertex

#define MAX_V (1 << 10)
#define INF (1 << 30)

int V;
struct edge {
  int to, cost;
  edge(int x, int y) : to(x), cost(y) {}
};
std::vector<edge> G[MAX_V];
int d[MAX_V];

void dijkstra(int s){
  std::priority_queue<p, std::vector<p>, std::greater<p>> que;
  std::fill(d, d+V, INF);
  d[s] = 0;
  que.push(p(0,s));

  while(que.size() > 0){
    p item = que.top();
    que.pop();
    int v = item.second;
    if(d[v] < item.first)
      continue;
    for(int i=0;i<G[v].size();i++){
      edge e = G[v][i];
      if(d[e.to] > d[v] + e.cost){
	d[e.to] = d[v] + e.cost;
	que.push(p(d[e.to], e.to));
      }
    }
  }
}

int main(void){
  V = 10;
  for(int i=0;i<V-1;i++){
    G[i].push_back(edge(i+1, 10));
  }
  G[3].push_back(edge(7,10));
  dijkstra(0);
  std::cout << d[10-1] << std::endl;
}

#include <iostream>
#include <vector>

#define MAX_V 1000
#define INF 1<<30
struct edge {int to, cap, rev; };

std::vector<edge> G[MAX_V];
bool used[MAX_V];

// add an edge with capacity 'cap' on the graph 
void add_edge(int from, int to, int cap){
  G[from].push_back((edge){to, cap, (int)G[to].size()});
  G[to].push_back((edge){from, 0, (int)G[from].size() - 1});
}

int dfs(int v, int t, int f){
  if(v == t)
    return f;
  used[v] = true;
  for(int i=0;i<G[v].size();i++){
    edge &e = G[v][i];
    if(!used[e.to] && e.cap > 0){
      int d = dfs(e.to, t, std::min(f, e.cap));
      if(d > 0){
	e.cap -= d;
	G[e.to][e.rev].cap += d;
	return d;
      }
    }
  }
  return 0;
}

// s --> t
int max_flow(int s, int t){
  int flow = 0;
  for(;;){
    for(int i=0;i<MAX_V;i++)
      used[i] = false;
    int f = dfs(s, t, INF);
    if(f == 0)
      return flow;
    flow += f;
  }
}


int main(void){
  add_edge(0, 1, 10);
  add_edge(0, 2, 2);
  add_edge(1, 2, 6);
  add_edge(1, 3, 6);
  add_edge(3, 2, 3);
  add_edge(3, 4, 8);
  add_edge(2, 4, 5);
  std::cout << max_flow(0,4) << std::endl;
}

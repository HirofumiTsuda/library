#include <iostream>
#include <vector>

#define MAX_E 1 << 17
#define MAX_V 1 << 17
#define INF 1 << 17

struct edge {
  int from, to, cost;
};

edge es[MAX_E]; // edge
int d[MAX_V];
int V, E;

void bellman_ford(int s){
  for(int i=0;i<E;i++)
    d[i] = INF;
  d[s] = 0;
  while(true){
    bool update = false;
    for(int i=0;i<E;i++){
      edge e = es[i];
      if(d[e.from] != INF && d[e.to] > d[e.from] + e.cost){
	d[e.to] = d[e.from] + e.cost;
	update = true;
      }
    }
    if(!update)
      break;
  }
}

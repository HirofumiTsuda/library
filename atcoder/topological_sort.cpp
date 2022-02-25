#include <iostream>
#include <vector>
#include <algorithm>


void dfs_topological(int v, std::vector<std::vector<int>>& G, std::vector<bool>& seen, std::vector<int>& order){
  seen[v] = true;
  for(auto next : G[v]){
    if(!seen[next]){
      dfs_topological(next, G, seen, order);
    }
  }
  order.push_back(v);
}

std::vector<int> topological_sort(std::vector<std::vector<int>>& G){
  int N = G.size();
  std::vector<bool> seen(N, false);
  std::vector<int> order;
  for(int v=0;v<N;v++){
    if(!seen[v]){
      dfs_topological(v, G, seen, order);
    }
  }
  std::reverse(order.begin(), order.end());
  return std::move(order);
}


int main(){
  int N = 4;
  std::vector<std::vector<int>> G; // graph  
  G.assign(N, std::vector<int>(0));
  for(int v=1;v<N;v++){
    G[N - v].push_back(N - v - 1);
  }
  std::vector<int> res = topological_sort(G);
  for(auto e : res){
    std::cout << e << std::endl;
  } 
}

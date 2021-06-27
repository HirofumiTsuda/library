#include <iostream>

#define MAX_N 10000


int par[MAX_N];
int rank[MAX_N];
int size[MAX_N];

void init(int n){
  for(int i=0;i<n;i++){
    par[i] = i;
    rank[i] = 0;
    size[i] = 1;
  }
}

int find(int x){
  if(par[x] == x){
    return x;
  }else{
    return par[x] = find(par[x]);
  }
}

void unite(int x, int y){
  x = find(x);
  y = find(y);
  if (x == y)
    return;

  if(rank[x] < rank[y]){
    par[x] = y;
    size[y] = size[x] + size[y];
  }else{
    par[y] = x;
    size[x] = size[x] + size[y];    
    if(rank[x] == rank[y])
      rank[x]++;
  }
}

bool same(int x, int y){
  return find(x) == find(y);
}


int main(void){
  init(10);
  unite(2,3);
  unite(4,5);
  for(int i=0;i<10;i++){
    std::cout << par[i] << std::endl;
  }
}

#include <iostream>
#include <vector>


class UnionFind{
private:
  std::vector<int> par;
  std::vector<int> rank;
  std::vector<int> size;

public:
  UnionFind(int n){
    par.assign(n, 0);
    rank.assign(n, 0);
    size.assign(n, 0);
    for(int i=0;i<n;i++){
      par[i] = i;
      rank[i] = 0;
      size[i] = 1;
    }    
  }

  virtual ~UnionFind(){}

  int find(int x){
    if(par[x] == x){
      return x;
    }else{
      return par[x] = find(par[x]);
    }
  }  

  int get_size(int x){
    return size[find(x)];
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
};



int main(void){
  UnionFind<int> uf(10);
  uf.unite(2,3);
  uf.unite(4,5);
  uf.unite(3,4);  
  std::cout << uf.same(2,5) << std::endl;
}

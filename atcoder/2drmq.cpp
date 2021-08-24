#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

#define INF 1 << 30

template<typename T>
class Segtree2D {
private:
  int H, W;
  std::vector<std::vector<T>> dat;
public:
  Segtree2D(std::vector<std::vector<T>> &f) {
    H = W = 1;
    while(H < (int)f.size()) H <<= 1;
    while(W < (int)f[0].size()) W <<= 1;
    dat.assign(2*H-1,std::vector<int>(2*W-1,INF));
    init(f);
  }
  
  void init(std::vector<std::vector<int>> &f) {
    for (int i = 0; i < (int)f.size(); i++)
      for (int j = 0; j < (int)f[0].size(); j++)
	dat[i+H-1][j+W-1] = f[i][j];
    for (int i = 2*H-2; i > H-2; i--)
      for (int j = W-2; j >= 0; j--)
	dat[i][j] = std::min(dat[i][2*j+1], dat[i][2*j+2]);
    for (int i = H-2; i >= 0; i--)
      for (int j = 0; j < 2*W-1; j++)
	dat[i][j] = std::min(dat[2*i+1][j], dat[2*i+2][j]);
    }

  // top-left (li, lj), bottom-right (ri, rj), bottom and right edges are not included
  int minimum(int li, int lj, int ri, int rj) {
    return minimum_h(li,lj,ri,rj,0,H,0);
  }
  
  int minimum_h(int li, int lj, int ri, int rj, int si, int ti, int k) {
    if(ri <= si or ti <= li) return INF;
    if(li <= si and ti <= ri) return minimum_w(lj,rj,0,W,k,0);
    const int mi = (si+ti)/2;
    return std::min(minimum_h(li,lj,ri,rj,si,mi,2*k+1), minimum_h(li,lj,ri,rj,mi,ti,2*k+2));
  }
  
    int minimum_w(int lj, int rj, int sj, int tj, int i, int k) {
      if(rj <= sj or tj <= lj) return INF;
      if(lj <= sj and tj <= rj) return dat[i][k];
      const int mj = (sj+tj)/2;
      return std::min(minimum_w(lj,rj,sj,mj,i,2*k+1),minimum_w(lj,rj,mj,tj,i,2*k+2));
    }
};


int main(void){
  std::vector<std::vector<int>> v;
  v.push_back({1,2,3,4,5,6});
  v.push_back({7,8,9,10,11,12});
  v.push_back({13,14,0,-5,-18,18});  
  Segtree2D<int> seg(v);
  std::cout <<  seg.minimum(1, 1, 3, 4) << std::endl;
}

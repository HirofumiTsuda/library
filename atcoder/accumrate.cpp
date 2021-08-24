#include <iostream>
#include <vector>
#include <memory>

template<typename T>
class Accumrate1D {
private:
  int n;
  std::unique_ptr<T []> ptr;
  std::unique_ptr<T []> dat;
public:
  Accumrate1D(int n) : n(n){
    ptr = std::make_unique<T []>(n);
    dat = std::make_unique<T []>(n+1);    
  }
  Accumrate1D(const std::vector<T>& v){
    n = v.size();
    ptr = std::make_unique<T []>(n);
    dat = std::make_unique<T []>(n+1);        
    for(int i=0;i<v.size();i++){
      ptr[i] = v[i];
    }
    build();
  }
  virtual ~Accumrate1D(){}
  void set(T x, int n){
    ptr[n] = x;
  }
  
  void build(){
    T tmp = 0;
    for(int i=0;i<n;i++){
      tmp += ptr[i];
      dat[i+1] = tmp;
    }
  }
  // 0-index r is not included 
  T get(int l, int r) const {
    return dat[r] - dat[l];
  }
};

template <typename T>
class Accumrate2D{
private:
  int H,W;
  std::vector<std::vector<T>> v;
  std::vector<std::vector<T>> dat;  
public:
  Accumrate2D(int h, int w) : H(h), W(w){
    v.assign(H, std::vector<T>(W));
    dat.assign(H, std::vector<T>(W));    
  }
  Accumrate2D(std::vector<std::vector<T>>& mat){
    H = mat.size();
    W = mat[0].size();
    v = mat;
    build();
  }
  void set(int x, int y, T c) {
    v[x][y] = c;
  }
  void add(int x, int y, T c) {
    v[x][y] += c;
  }
  void build() {
    dat = v;
    for(int h=0;h<H;h++){
      for(int w=0;w<W;w++){
	if (0 < h) dat[h][w] += dat[h - 1][w];
	if (0 < w) dat[h][w] += dat[h][w - 1];
	if (0 < h && 0 < w) dat[h][w] -= dat[h - 1][w - 1];	
      }
    }
  }
  // [4,4] - [1,1] rectangle
  T get(int tx, int ty, int sx, int sy) {
    if (tx < sx or ty < sy) return 0;
    T rs = dat[ty][tx];
    std::cout << rs << std::endl;
    if (0 < sx) rs -= dat[ty][sx - 1];
    if (0 < sy) rs -= dat[sy - 1][tx];
    if (0 < sx && 0 < sy) rs += dat[sy - 1][sx - 1];
    return rs;
  }    
  
};


  
int main(void){
  std::vector<std::vector<int>> v;
  for(int i=0;i<4;i++){
    std::vector<int> tmp;
    for(int j=1;j<=6;j++)
      tmp.push_back(j);
    v.push_back(tmp);
  }
  Accumrate2D<int> ac(v);
  std::cout << ac.get(3,3, 1,1) << std::endl;
}
  

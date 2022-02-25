#include <iostream>
#include <functional>
#include <vector>
#include <climits>
#include <algorithm>

const int MAX_N = 1 << 17;

template<typename T>
class Segtree{
private:
  int n;
  std::vector<T> dat;
  std::function<T(T, T)> f;
  T ivalue;
public:
  Segtree(int n_,  std::function<T(T, T)> f, T ivalue) : f(f), ivalue(ivalue) {
    n = 1;
    while(n < n_) n*=2;
    dat.assign(2*n, ivalue);
  }  

  virtual ~Segtree(){}

  void update(int k, int a){
    k += n-1;
    dat[k] = a;
    while(k > 0){
      k = (k-1)/2;
      dat[k] = f(dat[k * 2 + 1], dat[k * 2 + 2]);
    }
  }


  // get the minimum value in the range [a, b)
  // to execute, call get_min(a,b,0,0,n)
  T get_value(int a, int b, int k, int l, int r){
    // [a, b) does not have common element with [l, r)
    if(r <= a || b <= l) return ivalue;

    if (a <= l && r <= b){
      return dat[k];
    }else{
      T vl = get_value(a, b, k*2 + 1, l, (l+r)/2);
      T vr = get_value(a, b, k*2 + 2, (l+r)/2, r);
      return f(vl, vr);
    }
  }

  T get_value(int a, int b){
    return get_value(a,b,0,0,n);
  }

};





int main(){
  Segtree<int> rmq(10, [](int x, int y){return std::min(x, y);}, INT_MAX);
  for(int i=0;i<10;i++){
    rmq.update(i, i+4);
  }
  std::cout << rmq.get_value(2,4) << std::endl;
}

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

const int MAX_N = 1 << 17;

template<typename T>
class Segtree{
private:
  int n;
  std::vector<T> dat;
public:
  
  Segtree(int n_){
    n = 1;
    while(n < n_) n*=2;

    dat.assign(2*n, (T)MAX_N);
  }  

  virtual ~Segtree(){}

  void update(int k, int a){
    k += n-1;
    dat[k] = a;
    while(k > 0){
      k = (k-1)/2;
      dat[k] = std::min(dat[k * 2 + 1], dat[k * 2 + 2]);
    }
  }


  // get the minimum value in the range [a, b)
  // to execute, call get_min(a,b,0,0,n)
  int get_min(int a, int b, int k, int l, int r){
    // [a, b) does not have common element with [l, r)
    if(r <= a || b <= l) return INT_MAX;

    if (a <= l && r <= b){
      return dat[k];
    }else{
      int vl = get_min(a, b, k*2 + 1, l, (l+r)/2);
      int vr = get_min(a, b, k*2 + 2, (l+r)/2, r);
      return std::min(vl, vr);
    }
  }

  int get_min(int a, int b){
    return get_min(a,b,0,0,n);
  }

};





int main(){
  Segtree<int> st(10);
  for(int i=0;i<10;i++){
    st.update(i, i+4);
  }
  std::cout << st.get_min(1,2) << std::endl;
}

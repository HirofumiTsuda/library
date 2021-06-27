#include <iostream>
#include <climits>
#include <algorithm>

const int MAX_N = 1 << 17;

int n, dat[2 * MAX_N - 1];

void init(int n_){
  n = 1;
  while(n < n_) n*=2;

  for(int i=0;i<2*n-1;i++) dat[i] = INT_MAX;
}

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


int main(){
  init(3);
  for(int i=0;i<n;i++){
    update(i, i+4);
  }
  std::cout << get_min(1,4,0,0,n) << std::endl;
}

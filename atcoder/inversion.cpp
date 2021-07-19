#include <iostream>
#include <vector>

template<typename T>
class BIT{
private:
  std::vector<T> bit;
  int n;
public:
  BIT(int n) : n(n) {
    bit.assign(n, (T)0);
  }

  virtual ~BIT(){}

  // a1 + a2 + .... + ai
  int sum(int i){
    int s = 0;
    while(i > 0){
      s += bit[i];
      i -= i & -i;
    }
    return s;
  }

  void add(int i, T x){
    while(i <= n){
      bit[i] += x;
      i += i & -i;
    }
  }
};


void solve(){
  BIT<int> bit(100);
  std::vector<int> a(20);
  int ans = 0;
  for(int i=0;i<20;i++){
    a[i] = (3*i + 2)%13 + 1;
  }
  for(int j=0;j<a.size();j++){
    ans += j - bit.sum(a[j]);
    bit.add(a[j], 1);
  }
  std::cout << ans << std::endl;
}

int main(int argc, char *argv[])
{
  solve();
  return 0;
}


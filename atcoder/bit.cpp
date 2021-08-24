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

  // 1-index
  void add(int i, T x){
    while(i <= n){
      bit[i] += x;
      i += i & -i;
    }
  }
};

int main(int argc, char *argv[])
{
  BIT<int> bit(10);
  bit.add(1, 3);
  bit.add(4, 4);
  std::cout << bit.sum(4) << std::endl;
  return 0;
}




#include <iostream>
#include <vector>

template<typename T>
class Matrix{
private:
  int m,n;
  std::vector<std::vector<T>> mat;
public:
  Matrix(int m, int n) : m(m), n(n) {
    for(int i=0;i<m;i++){
      std::vector<ll> tmp(n);
      mat.push_back(tmp);
    }
  }
  virtual ~Matrix(){}
  ll at(int i, int j){
    return mat[i][j];
  }
  
};

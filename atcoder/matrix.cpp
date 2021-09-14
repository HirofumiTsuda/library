#include <iostream>
#include <vector>
#include <utility>

template<typename T>
class Matrix{
private:
  int m,n;
  std::vector<std::vector<T>> mat;
public:
  Matrix(int m, int n) : m(m), n(n) {
    for(int i=0;i<m;i++){
      std::vector<T> tmp(n);
      mat.push_back(tmp);
    }
  }
  virtual ~Matrix(){}
  T at(int i, int j){
    return mat[i][j];
  }
  void set(int i, int j, T x){
    mat[i][j] = x;
  }
  void anti_clockwise(){
    std::vector<std::vector<T>> tmp;
    for(int j=0;j<n;j++)
      tmp.push_back(std::vector<T>(m));
    for(int i=0;i<m;i++){
      for(int j=0;j<n;j++){
	tmp[n-j-1][i] = mat[i][j];
      }
    }
    std::swap(m, n);
    mat = std::move(tmp);
  }
  void clockwise(){
    std::vector<std::vector<T>> tmp;
    for(int j=0;j<n;j++)
      tmp.push_back(std::vector<T>(m));
    for(int i=0;i<m;i++){
      for(int j=0;j<n;j++){
	tmp[j][m-i-1] = mat[i][j];
      }
    }
    std::swap(m, n);
    mat = std::move(tmp);
  }  
  
};

int main(int argc, char *argv[])
{
  using namespace std;  
  Matrix<int> mat(3,4);
  for(int i=0;i<3; i++){
    for(int j=0;j<4;j++){
      mat.set(i, j, i+(j)*2);
    }
  }
  for(int i=0;i<3;i++){
    for(int j=0;j<4;j++){
      cout << mat.at(i,j);
    }
    cout << endl;
  }
  mat.clockwise();
  mat.anti_clockwise();
  for(int i=0;i<3;i++){
    for(int j=0;j<4;j++){
      cout << mat.at(i,j);
    }
    cout << endl;
  }  
  return 0;
}

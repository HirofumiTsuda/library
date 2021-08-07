#include <iostream>

template<typename T>
T gcd(T a, T b){
  if(b > a)
    return gcd(b, a);
  if(b == 0)
    return a;
  return gcd(b, a%b);
}



int main(void){
  int a = 35,b = 45;
  std::cout << gcd(a,b) << std::endl;
}

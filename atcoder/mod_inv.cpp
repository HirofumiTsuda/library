#include <iostream>

typedef long long int ll;

#define MOD 1000000007

ll mod_inv(ll x){
  ll p = MOD - 2;
  ll f = x;
  ll res = 1;
  while(p > 0){
    if((p & 1) == 1){
      res = (res * f)%MOD;
    }
    f = (f * f)%MOD;
    p = p >> 1;
  }
  return res;
}

int main(void){
  ll x = 8;
  std::cout << mod_inv(x) << std::endl;
}

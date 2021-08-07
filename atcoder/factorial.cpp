#include <iostream>
#include <vector>

#define MOD (int)(1e9 + 7.0)


//////////////////////////////////////////////////////////////
// https://drken1215.hatenablog.com/entry/2018/06/08/210000
//////////////////////////////////////////////////////////////

struct Factorial{
  int max, mod;
  std::vector<long long int> fac, inv, finv;
  Factorial(long long int max, long long int mod) : max(max), mod(mod) {
    fac.assign(max+1, 0);
    inv.assign(max+1, 0);
    finv.assign(max+1, 0);
    fac[0] = fac[1] = 1;
    finv[0] = finv[1] = 1;
    inv[1] = 1;
    for (int i = 2; i < max; i++){
        fac[i] = fac[i - 1] * i % mod;
        inv[i] = mod - inv[mod%i] * (mod / i) % mod;
        finv[i] = finv[i - 1] * inv[i] % mod;
    }    
  }

  long long int nCk(int n, int k){
    if (n < k) return 0;
    if (n < 0 || k < 0) return 0;
    return fac[n] * (finv[k] * finv[n - k] % mod) % mod;    
  }
};


int main(int argc, char *argv[])
{
  Factorial factorial(1000000, MOD);
  std::cout << factorial.nCk(6,3) << std::endl;
  return 0;
}

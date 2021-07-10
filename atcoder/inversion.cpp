const int MAX_N = 1 << 17;

int bit[MAX_N];

int a[100]; // input
int n = 10000;
// a1 + a2 + .... + ai
int sum(int i){
  int s = 0;
  while(i > 0){
    s += bit[i];
    i -= i & -i;
  }
  return s;
}

void add(int i, int x){
  while(i <= n){
    bit[i] += x;
    i += i & -i;
  }
}


void solve(){
  typedef long long int ll;
  ll ans = 0;
  for(int j=0;j<n;j++){
    ans += j - sum(a[j]);
    add(a[j], 1);
  }
  // print("%lld\n",ans)
}

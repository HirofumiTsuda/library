typedef long long int

#define MOD ((ll)1000000000);
#define rep(i,a,b) for(int i=a;i<b;i++)
//---------------------------------------------------------------------------------------------------
ll f[101010], rf[101010];
ll inv(ll x) {
    ll res = 1;
    ll k = mod - 2;
    ll y = x;
    while (k) {
        if (k & 1) res = (res * y) % mod;
        y = (y * y) % mod;
        k /= 2;
    }
    return res;
}
void init() {
    f[0] = 1;
    rep(i, 1, 101010) f[i] = (f[i - 1] * i) % mod;
    rep(i, 0, 101010) rf[i] = inv(f[i]);
}
//---------------------------------------------------------------------------------------------------
ll C(int n, int k) {
    ll a = f[n]; // = n!
    ll b = rf[n-k]; // = (n-k)!
    ll c = rf[k]; // = k!

    ll bc = (b * c) % mod;

    return (a * bc) % mod;
}

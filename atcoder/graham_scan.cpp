#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

class P{
private:
  double EPS = 1e-10;
  double add(double a, double b){
    if(std::abs(a+b) < EPS * (std::abs(a) + std::abs(b)))
      return 0;
    return a + b;
  }
public:
  double x, y;
  P(){}
  P(double x, double y) : x(x), y(y) {}
  P operator + (P p){
    return P(add(x, p.x), add(y, p.y));
  }
  P operator - (P p){
    return P(add(x, -p.x), add(y, -p.y));
  }

  P operator * (double d){
    return P(x * d, y * d);
  }

  P operator / (double d){
    return P(x / d, y / d);
  }

  double dot(P p){
    return add(x * p.x, y * p.y);
  }

  double det(P p){
    return add(x * p.y, -y * p.x);
  }        
};


bool cmp_x(const P& p, const P& q){
  if(p.x != q.x) return p.x < q.x;
  return p.y < q.y;
}

std::vector<P> convex_hull(std::vector<P> ps, int n){
  std::sort(ps.begin(), ps.end(), cmp_x);
  int k = 0;
  std::vector<P> qs(n * 2);

  // lower convex area
  for(int i=0;i<n;i++){
    while(k > 1 && (qs[k-1] - qs[k-2]).det(ps[i] - qs[k-1]) <= 0) k--;
    qs[k++] = ps[i];
  }
  // upper convex area
  for(int i=n-2, t = k ;i>=0;i--){
    while(k > t && (qs[k-1] - qs[k-2]).det(ps[i] - qs[k-1]) <= 0) k--;
    qs[k++] = ps[i];
  }
  qs.resize(k-1);
  return qs;
}



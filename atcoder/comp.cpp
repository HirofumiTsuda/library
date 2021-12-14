#include <iostream>
#include <vector>
#include <set>
#include <map>

void comp(std::vector<int>& v){
  std::map<int, int> m;
  std::set<int> s(v.begin(), v.end());
  std::vector<int> res(v.size());
  int cnt=0;
  for(auto iter=s.begin();iter!=s.end();iter++){
    m[*(iter)] = cnt;
    cnt++;
  }
  for(int i=0;i<v.size();i++){
    res[i] = m[v[i]];
  }
  return std::move(res);
}

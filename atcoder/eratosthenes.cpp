#include <iostream>

#include <vector>
#include <cmath>

std::vector<int> erathosthenes(int n){
  std::vector<bool> used(n+1);
  used.assign(n+1, true);
  used[1] = false;
  double end = std::sqrt(n);
  std::vector<int> ans;
  for(int i=1;i<=end;i++){
    if(!used[i])
      continue;
    for(int p=2*i;p<=n;p=p+i)
      used[p] = false;
  }
  for(int i=1;i<=n;i++){
    if(used[i])
      ans.push_back(i);
  }
  return ans;
}

int main(void){
  std::vector<int> v = erathosthenes(20);
  for(int e : v)
    std::cout << e << std::endl;
  return 0;
}

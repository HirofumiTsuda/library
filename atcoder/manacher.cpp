#include <iostream>
#include <vector>
#include <string>


// Manacher's algorithm can find a palindrome with the maximum odd length
// to find one with the maximum even length, invalid characters (e.g. $) should be inserted

std::vector<int> manacher(std::string s){
  std::vector<int> R(s.size());
  int c = 0;
  for (int i = 0; i < s.size(); ++i) {
    int l = c - (i-c);
    if (i+R[l] < c+R[c]) {
      R[i] = R[l];
    } else {
      int j = c+R[c] - i;
      while (i-j >= 0 && i+j < s.size() && s[i-j] == s[i+j])
	j++;
      R[i] = j;
      c = i;
    }
  }
  return std::move(R);
}

int main(void){
  std::string s = "abaaababa";
  std::vector<int> v = manacher(s);
  for(int i=0;i<v.size();i++)
    std::cout << v[i] << std::endl;
  return 0;
}

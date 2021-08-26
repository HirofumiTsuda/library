#include <iostream>
#include <vector>
#include <string>


// Manacher's algorithm can find a palindrome with the maximum odd length
// to find one with the maximum even length, invalid characters (e.g. $) should be inserted

std::vector<int> manacher(std::string s){
  std::vector<int> R(s.size());
  int i = 0, j = 0;
  while (i < s.size()) {
    while (i-j >= 0 && i+j < s.size() && s[i-j] == s[i+j]) ++j;
    R[i] = j;
    int k = 1;
    while (i-k >= 0 && k+R[i-k] < j) R[i+k] = R[i-k], ++k;
    i += k; j -= k;
  }
  return std::move(R);
}

int main(void){
  //"ababbb"
  //std::string s = "abaaababa";
  std::string s = "ababbb";
  s = "ggbswiymmlevedhkbdhntnhdbkhdevelmmyiwsbgg";
  std::vector<int> v = manacher(s);
  for(int i=0;i<v.size();i++)
    std::cout << v[i] << std::endl;
  return 0;
}

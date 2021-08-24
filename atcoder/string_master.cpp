#include <iostream>
#include <vector>
#include <algorithm>

// 'a' - 'z'
#define SIZE 26
#define TOP_CHAR 'a'

class StringMaster {
private:
  std::string s;
  int N;
  std::vector<int> nxt[SIZE];
  std::vector<int> bak[SIZE];
public:
  StringMaster(const std::string& s) { init(s); }
  virtual ~StringMaster(){}
  void init(const std::string& _s) {
    s = _s;
    N = s.length();
    for(int c=0;c<SIZE;c++){
      nxt[c].assign(N, 0);
      bak[c].assign(N, 0);
    }

    for(int c=0;c<SIZE;c++){
      for(int i=0;i<N;i++)
	nxt[c][i] = N;
    }

    for(int i=0;i<N;i++){
	nxt[s[i] - TOP_CHAR][i] = i;
    }

    for(int c=0;c<SIZE;c++){
      for(int i=N-2;i>=0;i--){
	nxt[c][i] = std::min(nxt[c][i], nxt[c][i+1]);	
      }
    }

    for(int c=0;c<SIZE;c++){
      for(int i=0;i<N;i++)
	bak[c][i] =-1;
    }

    for(int i=0;i<N;i++){
	bak[s[i] - TOP_CHAR][i] = i;
    }

    for(int c=0;c<SIZE;c++){
      for(int i=1;i<N;i++){
	bak[c][i] = std::max(bak[c][i], bak[c][i-1]);	
      }
    }    
  }
  int get_next(int cu, char c) {
    if (cu < 0) {
      if (s[0] == c) return 0;
      cu = 0;
    }
    if (N <= cu) return N;
    return nxt[c - TOP_CHAR][cu];
  }
  int get_back(int cu, char c) {
    if (cu < 0) return -1;
    return bak[c - TOP_CHAR][cu];
  }
};



int main(void){
  std::string s = "anpontan";
  StringMaster sm(s);
  std::cout << sm.get_next(0, 'p') << std::endl;
  std::cout << sm.get_back(s.size()-1, 'p') << std::endl;  
}

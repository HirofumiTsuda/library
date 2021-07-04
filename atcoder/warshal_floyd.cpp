#include <algorithm>
#define MAX_V (1 << 15)
int d[MAX_V][MAX_V]; // edge u-v, otherwise INF (i eq j => 0)
int V;

void warshall_floyd(){
  for(int k=0;k<V;k++){
    for(int i=0;i<V;i++){
      for(int j=0;j<V;j++){
	d[i][j] = std::min(d[i][j], d[i][k] + d[k][j]);
      }
    }
  }
}

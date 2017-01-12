/*
 * POJ 2392: Space Elevator
 * 题意：给出多种砖，属性包含高度、数量、高度阈值。求可以垒出的最大高度。
 * 类型：DP+贪心
 * 算法：将砖块按阈值升序排序，d[i]表示达到高度i时当前砖块最多剩余数。若达到i可以不使用当前类砖，则值为当前砖总数，否则从剩余大于0的高度转移。
 */


#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

int d[40010];

struct B{
  int h, c, a;
  bool operator<(const B& b) const {
    return a < b.a;
  }
}b[410];

int main() {
  int n, i, j, H = 0;
  scanf("%d", &n);
  for(i = 0; i < n; ++i) {
    scanf("%d%d%d", &b[i].h, &b[i].a, &b[i].c);
    H = max(H, b[i].a);
  }

  sort(b, b + n);

  memset(d, -1, sizeof(d));
  d[0] = 0;
  for(i = 0; i < n; ++i) {
    for(j = 0; j <= b[i].a; ++j) {
      if(d[j] != -1) {
        d[j] = b[i].c;
      } else if(j >= b[i].h && d[j - b[i].h] > 0){
        d[j] = d[j - b[i].h] - 1;
      }
    }
  }
  for(i = H; i >=0; --i) {
    if(d[i] != -1) {
      printf("%d\n", i);
      break;
    }
  }
  return 0;
}
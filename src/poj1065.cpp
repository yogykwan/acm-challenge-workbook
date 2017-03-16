/*
 * POJ 1065: Wooden Sticks
 * 题意：已知一堆木棍的长宽，启动一般的木棍需要1分钟，若该木棍长宽都不小于某已启动木棍，则替换原木棍并不需时间。求启动所有木棍的最短时间。
 * 类型：DP+贪心
 * 算法：将长宽转化为二维向量的点，每段斜率都非负的折线需要1分钟。多段折线互不相交，且最高点依次下降，折线条数转化为最高点组成的最长降序。
 */

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

typedef pair<int, int> pii;
pii s[5010];
int d[5010];

int main() {
  int T, n, i, j;
  scanf("%d", &T);
  while(T--) {
    scanf("%d", &n);
    for(i = 0; i < n; ++i) {
      scanf("%d%d", &s[i].first, &s[i].second);
    }
    sort(s, s + n);
    int ans = 0;
    for(i = 0; i < n; ++i) {
      d[i] = 1;
      for(j = 0; j < i; ++j) {
        if(s[i].second < s[j].second) {
          d[i] = max(d[i], d[j] + 1);
        }
      }
      ans = max(ans, d[i]);
    }
    printf("%d\n", ans);
  }
  return 0;
}
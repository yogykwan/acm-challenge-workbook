/*
 * AOJ 0189: Convenient Location
 * 题意：多个地点，多条双向边，每条边有时间花费。求到所有地点的时间的和最小的点。
 * 类型：最短路
 * 算法：用Floyd求到两两之间最短路，枚举总和最小的点。
 */

#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

int d[10][10];
int m;

void floyd() {
  for(int i = 0; i < m; ++i) {
    for(int j = 0; j < m; ++j) {
      for(int k = 0; k < m; ++k) {
        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
      }
    }
  }
}

int main() {
  int i, j, a, b, c, n;
  while(scanf("%d", &n) != EOF && n) {
    memset(d, 0x3f, sizeof(d));
    m = 0;
    while(n--) {
      scanf("%d%d%d", &a, &b, &c);
      d[a][b] = d[b][a] = c;
      m = max(m, max(a + 1, b + 1));
    }
    floyd();
    int ans, p, tmp;
    ans = 0x7fffffff;
    for(i = 0; i < m; ++i) {
      tmp = 0;
      for(j = 0; j < m; ++j) {
        if(i == j) continue;
        tmp += d[i][j];
      }
      if(tmp < ans) {
        ans = tmp;
        p = i;
      }
    }
    printf("%d %d\n", p, ans);
  }
  return 0;
}


/*
 * POJ 2139: Six Degrees of Cowvin Bacon
 * 题意：图中多条权为1的双向边，求到其他所有点的最短路的平均值最小的点。
 * 类型：最短路
 * 算法：用Floyd求到两两之间最短路，枚举和最小的点。
 */

#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

int d[310][310];
int tmp[310];

void floyd(int n) {
  for(int i = 1; i <= n; ++i) {
    for(int j = 1; j <= n; ++j) {
      for(int k = 1; k <= n; ++k) {
        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
      }
    }
  }
}

int main() {
  memset(d, 0x3f, sizeof(d));
  int n, m;
  scanf("%d%d", &n, &m);
  while(m--) {
    int t;
    scanf("%d", &t);
    for(int i = 0; i < t; ++i){
      scanf("%d", &tmp[i]);
      for(int j = 0; j < i; ++j) {
        d[tmp[i]][tmp[j]] = 1;
        d[tmp[j]][tmp[i]] = 1;
      }
    }
    floyd(n);
  }

  int ans, sum;
  ans = 0x7fffffff;
  for(int i = 1; i <= n; ++i) {
    sum = 0;
    for(int j = 1; j <= n; ++j) {
      if(i == j) continue;
      sum += d[i][j];
    }

    ans = min(ans, sum);
  }
  printf("%d\n", ans * 100 / (n - 1));
  return 0;
}
/*
 * POJ 2385: Apple Catching
 * 题意：苹果每分钟从两棵树的其中一棵落下，在树1和树2间可以跳换给定次数，问最多可以接到多少苹果，初始在树1。
 * 类型：DP
 * 算法：d[i][j]表示到达i时刻，已换树j次，位于j%2+1号树下。转移d[i][j]=max(d[i-1][j],d[i-1][j-1])+((j&1)+1==a[i])。
 */


#include <cstdio>
#include <iostream>

using namespace std;

int d[1010][33];
int a[1010];

int main() {
  int n, w, i, j, p;
  scanf("%d%d", &n, &w);
  for(i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    d[i][0] = (i? d[i - 1][0]: 0) + int(a[i] == 1);
  }
  for(i = 0; i <= w; ++i) {
    d[0][i] = ((i & 1) + 1 == a[0]);
  }
  for(i = 1; i < n; ++i) {
    for(j = 1; j <= w; ++j) {
      d[i][j] = max(d[i - 1][j - 1], d[i - 1][j]) + ((j & 1) + 1 == a[i]);
    }
  }
  int ans = 0;
  for(j = 0; j <= w; ++j) {
    ans = max(ans, d[n - 1][j]);
  }
  printf("%d\n", ans);
  return 0;
}
/*
 * POJ 2184: Cow Exhibition
 * 题意：一群奶牛，给出每头的IQ和EQ，范围是-1000到1000。选出一批奶牛，使得它们的IQ和、EQ和都非负。求IQ和加EQ和的最大值。
 * 类型：DP+01背包
 * 算法：d[i]表示IQ和为i时的EQ和最大值，由于和可为负数，用i加上一个大数作为数组下标。
 */

#include <cstdio>
#include <iostream>

using namespace std;

const int M = 100000;
int d[200010];

int main() {
  int i, j, n, iq, eq;
  scanf("%d", &n);
  for(i = 0; i <= (M<<1); ++i) {
    d[i] = -M - 1;
  }
  d[M] = 0;
  for(i = 0; i < n; ++i) {
    scanf("%d%d", &iq, &eq);
    if(iq <= 0 && eq <= 0) {
      continue;
    }
    if(iq > 0) {
      for(j = (M<<1); j >= iq ; --j) {
        if(d[j - iq] >= -M) {
          d[j] = max(d[j], d[j - iq] + eq);
        }
      }
    } else {
      for(j = 0; j <= (M<<1) + iq ;++j) {
        if(d[j - iq] >= -M) {
          d[j] = max(d[j], d[j - iq] + eq);
        }
      }
    }
  }
  int ans = 0;
  for(i = M; i <= (M<<1); ++i) {
    if(d[i] >= 0) {
      ans = max(ans, i - M + d[i]);
    }
  }
  printf("%d\n", ans);
  return 0;
}
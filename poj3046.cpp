/*
 * POJ 3046: Ant Counting
 * 题意：多族数量不定的蚂蚁，求组成一定规模范围的新蚁群的组合数。
 * 类型：DP
 * 算法：d[i][j]表示前i种蚂蚁，组成j规模的蚁群的组合数；每次由i-1中j的连续一段转移，所以用s[j]保存d[i]的前j项和。滚动数组降维。
 */

#include <cstdio>
#include <iostream>

using namespace std;

int c[1010];
int d[100010], s[100010];
int T, A, S, B;

int main() {
  scanf("%d%d%d%d", &T, &A, &S, &B);

  for(int i = 0; i < A; ++i) {
    int t;
    scanf("%d", &t);
    c[t]++;
  }

  d[0] = 1;
  for(int i = 0; i <= B; ++i) {
    s[i] = 1;
  }

  for(int i = 1; i <= T; ++i) {
    for(int j = 1; j <= B; ++j) {
      if(c[i] >= j) {
        d[j] = s[j];
      } else {
        d[j] = (s[j] - s[j - c[i] - 1] + 1000000) % 1000000;
      }
    }

    s[0] = 1;
    for(int j = 1; j <= B; ++j) {
      s[j] = (s[j - 1] + d[j]) % 1000000;
    }
  }
  printf("%d\n", (s[B] - s[S - 1] + 1000000) % 1000000);
  return 0;
}
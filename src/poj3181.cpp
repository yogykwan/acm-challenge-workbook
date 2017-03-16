/*
 * POJ 3181: Dollar Dayz
 * 题意：面值为1～K的货币，求凑成和为N的组合数。
 * 类型：DP+大数
 * 算法：滚动数组d[i]表示和为i时使用当前或之前货币的组合数，用int模拟大数加法。
 */

#include <cstdio>

const int LEN = 300;
const int MOD = 100000000;

void add(int* a, const int* b) {
  int jw = 0;
  for(int i = 0; i < LEN; ++i) {
    a[i] += b[i] + jw;
    jw = a[i] / MOD;
    a[i] %= MOD;
  }
}

void output(const int* a) {
  int i;
  for(i = LEN - 1; i >= 0; --i) {
    if(a[i] > 0) {
      break;
    }
  }
  printf("%d", a[i]);
  for(--i; i >= 0; --i) {
    printf("%08d", a[i]);
  }
  printf("\n");
}

int d[1010][LEN];
int n, k;

int main() {
  scanf("%d%d", &n, &k);
  d[0][0] = 1;
  for(int i = 1; i <= k; ++i) {
    for(int j = i; j <= n; ++j) {
      add(d[j], d[j - i]);
    }
  }
  output(d[n]);
  return 0;
}


/*
 * POJ 2976: Dropping tests
 * 题意：给出每场考试的总题数和得分，可以舍弃若干场考试的成绩。求剩余考试的得分总和除以总题数的最大值。
 * 类型：二分搜索+贪心
 * 算法：二分搜索最大的综合得分率，有E(a)/E(b)>=m，将成绩按ai-bj*m排序，取最大的k个相加看是否能大于等于0使得前式被满足。
 */

#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

typedef long long LL;

const double EPS = 1e-7;

LL a[1010], b[1010];

double c[1010];

int main() {
  int n, k;
  while (scanf("%d%d", &n, &k) != EOF && n) {
    for (int i = 0; i < n; ++i) {
      scanf("%lld", &a[i]);
    }
    for (int i = 0; i < n; ++i) {
      scanf("%lld", &b[i]);
    }

    double l, r, m;
    l = 0.0;
    r = 1.0;
    while (r - l > EPS) {
      m = (l + r) / 2;
      for (int i = 0; i < n; ++i) {
        c[i] = a[i] - m * b[i];
      }
      sort(c, c + n);
      double tmp = 0;
      for(int i = k; i < n; ++i) {
        tmp += c[i];
      }
      if(tmp > -EPS) {
        l = m;
      } else {
        r = m;
      }
    }

    printf("%0.0f\n", 100 * l);
  }
  return 0;
}
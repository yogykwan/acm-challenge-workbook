/*
 * POJ 3977: Subset
 * 题意：给出有正有负的序列，选取若干数，使得和的绝对值最小，绝对值相等则要求所选数个数最小。求最小的绝对值和以及对应元素个数。
 * 类型：折半枚举+双向搜索
 * 算法：将元素折半，二进制枚举各自n/2个元素的子集合的和。两边的和按和的增或减分别排序，保证和相同时元素少的排前面，双向搜索出和绝对值最小的组合。
 */

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

typedef long long LL;

inline LL ABS(LL x) {
  if (x >= 0) return x;
  return -x;
}

LL a[40];

struct Sum {
  LL s;
  int n;
} sa[1 << 17], sb[1 << 18];

bool cmpa(const Sum &s1, const Sum &s2) {
  if (s1.s != s2.s) return s1.s < s2.s;
  return s1.n < s2.n;
}

bool cmpb(const Sum &s1, const Sum &s2) {
  if (s1.s != s2.s) return s1.s > s2.s;
  return s1.n < s2.n;
}

LL ans;
int cnt;

void gao(int b, int n, Sum *s, int &nn, bool(*cmp)(const Sum &, const Sum &)) {
  for (LL i = (1ll << n) - 1; i; --i) {
    LL t = i, sum = 0;
    int num = 0;
    for (int j = b; j < b + n; ++j) {
      if (t & 1) {
        sum += a[j];
        ++num;
      }
      t >>= 1;
    }
    if (ABS(sum) < ans || ABS(sum) == ans && num < cnt) {
      ans = ABS(sum);
      cnt = num;
    }
//    printf("%d: %lld: %lld %d -> %lld %d\n", b, i, sum, num, ans, cnt);
    s[nn].s = sum;
    s[nn++].n = num;
  }
  sort(s, s + nn, cmp);
}

int main() {
  int n;
  while (scanf("%d", &n) != EOF && n) {
    for (int i = 0; i < n; ++i) scanf("%lld", &a[i]);
    ans = ABS(a[0]);
    cnt = 1;

    int na = 0, nb = 0;
    gao(0, n >> 1, sa, na, cmpa);
    gao(n >> 1, n - (n >> 1), sb, nb, cmpb);

    int i = 0, j = 0;
    while (i < na && j < nb) {
      LL ts = sa[i].s + sb[j].s;
      int tn = sa[i].n + sb[j].n;
      if (ABS(ts) < ans || ABS(ts) == ans && tn < cnt) {
        ans = ABS(ts);
        cnt = tn;
      }

      if (ts == 0) {
        ++i, ++j;
      } else if (ts < 0) {
        ++i;
      } else if (ts > 0) {
        ++j;
      }
    }

    printf("%lld %d\n", ans, cnt);
  }
  return 0;
}
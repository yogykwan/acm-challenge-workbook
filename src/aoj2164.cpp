/*
 * AOJ 2164: Revenge of the Round Table
 * 题意：来自两国的n个人围着圆桌坐下，要求相同国家坐在一起的不超过k个，问多少种方案（旋转后国籍序列重合视为一种）。
 * 类型：Pólya计数+DP
 * 算法：旋转i的循环节个数为gcd(n,i)，关键在于求长度为循环节个数i的不同串d[i]，然后代入公式L=|G|*(d[c(p1)]+d[c(p2)]+...+d[c(pk)])。t[0/1][i][j]表示长i且结尾j个相同字符、开头与结尾相同或不同的串数。d[i]表示长度为i且字符不全相同且不超过k个连续相同的数。
 */


#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;

const LL MOD = 1000003ll;
LL t[2][1010][1010], s[2][1010][1010], d[1010];

void Dp(LL n, LL k) {
  memset(t, 0, sizeof(t));
  memset(s, 0, sizeof(s));
  memset(d, 0, sizeof(d));


  t[0][1][1] = 1;
  s[0][1][1] = 1;

  for (LL i = 2; i <= n; ++i) {
    for (int c = 0; c < 2; ++c) {
      t[c][i][1] = s[c][i][1] = s[1 - c][i - 1][min(k, i - 1)];
    }
    for (LL j = 2; j <= min(i, k); ++j) {
      for (int c = 0; c < 2; ++c) {
        t[c][i][j] = t[c][i - 1][j - 1];
        s[c][i][j] = (s[c][i][j - 1] + t[c][i][j]) % MOD;
      }
    }
    for (LL j = min(i, k) + 1; j <= k; ++j) {
      for (int c = 0; c < 2; ++c) {
        s[c][i][j] = s[c][i][j - 1];
      }
    }
  }

  for (LL i = 1; i <= n; ++i) {
    d[i] = s[1][i][min(i, k)];
    for (LL p = 1; p <= min(k - 1, i - 2); ++p) {
      d[i] = (d[i] + s[1][i - p][min(k - p, i - 1 - p)]) % MOD;
    }
  }
}

LL Inverse(LL a, LL p) {
  if (a == 1) return 1;
  return ((-p / a * Inverse(p % a, p)) % p + p) % p;
}

LL Gcd(LL a, LL b) {
  for (LL t; t = b;) {
    b = a % b;
    a = t;
  }
  return a;
}

int main() {
//  freopen("/Users/yogy/acm-challenge-workbook/db.in", "r", stdin);
  LL n, k;
  while (scanf("%lld%lld", &n, &k) != EOF && n + k > 0) {
    if (n < k) k = n;
    LL ans = 0;
    Dp(n, k);
    for (LL i = 0; i < n; ++i) {
      ans = (ans + d[Gcd(n, i)]) % MOD;
    }
    ans = (ans * 2 * Inverse(n, MOD)) % MOD;
    if (k >= n) ans+=2; // 字符全部相同
    printf("%lld\n", ans);
  }
  return 0;
}

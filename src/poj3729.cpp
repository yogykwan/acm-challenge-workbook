/*
 * POJ 3729: Facer’s string
 * 题意：给出2个数串，求第一个数串的子串，使其满足长为k、该子串也是第二个数串的子串、该子串在第一个子串中增加一个后继字符不在第二个串中。求满足条件的子串的数量。
 * 类型：后缀数组
 * 算法：将两个数串用一个大数拼接，求后缀数组和高度数组。从两个方向遍历高度数组，求每个串1位置两侧的最近的串2和自己构成的范围最小值。
 */

#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

int s[100010];
int n, k, ns, nt;
int m;

int sa[100010];
int ra[100010], tr[100010];
int lcp[100010];

int l[50010], r[50010];

bool CmpSa(int a, int b) {
  if (ra[a] != ra[b]) return ra[a] < ra[b];
  int aa = a + k < n ? ra[a + k] : -1;
  int bb = b + k < n ? ra[b + k] : -1;
  return aa < bb;
}

void GaoSa() {
  for (int i = 0; i <= n; ++i) {
    sa[i] = i;
    ra[i] = i < n ? s[i] : -1;
  }
  for (k = 1; k <= n; k <<= 1) {
    sort(sa, sa + n + 1, CmpSa);
    tr[sa[0]] = 0;
    for (int i = 1; i <= n; ++i) {
      tr[sa[i]] = tr[sa[i - 1]] + CmpSa(sa[i - 1], sa[i]);
    }
    memcpy(ra, tr, sizeof(int) * (n + 1));
  }
}

void GaoLcp() {
  int tmp = 0;
  for (int i = 0; i < n; ++i) {
    int rk = ra[i];
    int j = sa[rk - 1];
    if (tmp > 0) --tmp;
    while (i + tmp < n && j + tmp < n && s[i + tmp] == s[j + tmp]) {
      ++tmp;
    }
    lcp[rk - 1] = tmp;
  }
}

int main() {
  freopen("/Users/yogy/acm-challenge-workbook/db.in", "r", stdin);
  while (scanf("%d%d%d", &ns, &nt, &m) != EOF) {
    n = ns + nt + 1;
    for (int i = 0; i < ns; ++i) scanf("%d", &s[i]);
    s[ns] = 10001;
    for (int i = ns + 1; i < n; ++i) scanf("%d", &s[i]);

    GaoSa();
    GaoLcp();

    memset(l, -1, sizeof(l));
    memset(r, -1, sizeof(r));

    int pre = -1;
    for (int i = 1; i < n - 1; ++i) {
      if (sa[i] > ns) {
        pre = lcp[i];
      } else {
        pre = min(pre, lcp[i]);
      }
      if (sa[i + 1] < ns) {
        l[sa[i + 1]] = pre;
      }
    }

    pre = -1;
    for (int i = n - 2; i > 0; --i) {
      if (sa[i + 1] > ns) {
        pre = lcp[i];
      } else {
        pre = min(pre, lcp[i]);
      }
      if (sa[i] < ns) {
        r[sa[i]] = pre;
      }
    }

    int ans = 0;
    for (int i = 0; i < ns; ++i) {
      if (max(l[i], r[i]) == m) ++ans;
    }
    printf("%d\n", ans);
  }
  return 0;
}

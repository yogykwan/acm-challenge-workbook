/*
 * POJ 1509: Glass Beads
 * 题意：给出一个循环字符串s，求字典序最小的起点下标。
 * 类型：后缀数组
 * 算法：将s和s拼接，用倍增法求后缀数组，由前一阶段的2个相邻rank得到目前的rank，直到得到长为原s长的rank停止。字典序最小的起点答案必须在第1个s内，如果排名相同选择下标小的。
 */

#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

char s[20010];
int n, k;

int sa[20010];
int ra[20010], tr[20010];

bool CmpSa(int a, int b) {
  if (ra[a] != ra[b]) return ra[a] < ra[b];
  int aa = a + k < n ? ra[a + k] : -1;
  int bb = b + k < n ? ra[b + k] : -1;
  return aa < bb;
}

void ConstructSa() {
  for (int i = 0; i < n; ++i) {
    sa[i] = i;
    ra[i] = s[i];
  }
  for (k = 1; k <= n >> 2; k <<= 1) {
    sort(sa, sa + n, CmpSa);
    tr[sa[0]] = 0;
    for (int i = 1; i < n; ++i) {
      tr[sa[i]] = tr[sa[i - 1]] + CmpSa(sa[i - 1], sa[i]);
    }
    memcpy(ra, tr, sizeof(int) * n);
  }
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%s", s);
    n = strlen(s);
    memcpy(s + n, s, sizeof(char) * n);
    n <<= 1;
    ConstructSa();
    int i, ans, rk;
    for (i = 0;; ++i) {
      if (sa[i] < n >> 1) {
        ans = sa[i];
        rk = ra[sa[i]];
        break;
      }
    }
    for (++i; i < n && ra[sa[i]] == rk; ++i) {
      ans = min(ans, sa[i]);
    }
    printf("%d\n", ans + 1);
  }
  return 0;
}

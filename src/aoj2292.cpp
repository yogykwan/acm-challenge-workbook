/*
 * AOJ 2292: Common Palindromes
 * 题意：给出两个字符串，从中各自取出长度相等的回文子串，起点终点的四元组构成一组合法解。求合法解个数。
 * 类型：后缀数组+回文DP+并查集
 * 算法：用Manacher求回文半径，倍增求后缀数组，尺取法求高度数组。按字符串奇偶分类，分别记录原串和复制串中符合长度的回文数量。按半径和lcp长度从大到小，枚举回文半径时更新对应中心的计数，将SA中相邻后缀合并时更新答案。
 */

#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <iostream>

using namespace std;

typedef long long LL;

char s[100010];
int n, k, ns, nt;
int m;

int sa[100010];
int ra[100010], tr[100010];
int lcp[100010];

char t[200010];
int rad[200010];

vector<int> q[100010], in[100010];
int pa[100010], ru[100010], a[100010], b[100010];

LL ret, ans;

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

void Manacher() {
  for (int i = 0; i < n; ++i) {
    t[i << 1] = '#';
    t[i << 1 | 1] = s[i];
  }
  t[n << 1] = '#';
  int i, j;
  i = j = 0;
  while (i <= n << 1) {
    while (i - j >= 0 && i + j <= (n << 1) && t[i - j] == t[i + j]) {
      ++j;
    }
    rad[i] = j;
    int k = 1;
    while (i - k >= 0 && rad[i] - k > rad[i - k]) {
      rad[i + k] = rad[i - k];
      ++k;
    }
    i += k;
    j = max(j - k, 0);
  }
}

int FindPa(int x) {
  if (pa[x] != x) pa[x] = FindPa(pa[x]);
  return pa[x];
}

void Merge(int x, int y) {
  x = FindPa(x);
  y = FindPa(y);
  if (x == y)return;
  if (ru[x] < ru[y]) {
    pa[x] = y;
    ret += 1ll * a[x] * b[y] + 1ll * a[y] * b[x];
    a[y] += a[x];
    b[y] += b[x];
  } else {
    pa[y] = x;
    ret += 1ll * a[x] * b[y] + 1ll * a[y] * b[x];
    a[x] += a[y];
    b[x] += b[y];
    if (ru[x] == ru[y]) ++ru[x];
  }
}

void AddA(int x) {
  x = FindPa(x);
  ret += b[x];
  ++a[x];
}

void AddB(int x) {
  x = FindPa(x);
  ret += a[x];
  ++b[x];
}

int main() {
//  freopen("/Users/yogy/acm-challenge-workbook/db.in", "r", stdin);
  scanf("%s", s);
  ns = strlen(s);
  s[ns] = '|';
  scanf("%s", s + ns + 1);
  n = strlen(s);

  GaoSa();
  GaoLcp();
  Manacher();

  // odd
  ret = 0;
  for (int i = 0; i <= n; i++) pa[i] = i;
  memset(ru, 0, sizeof(ru));
  memset(a, 0, sizeof(a));
  memset(b, 0, sizeof(b));
  for (int i = 0; i < n; ++i) {
    q[lcp[i]].push_back(i);
    in[rad[i << 1 | 1] - 1].push_back(i);
  }
  int m = n;
  if (m % 2 == 0) --m;
  for (int i = n; i > (m + 1) >> 1; --i) {
    for (auto &j: q[i]) {
      Merge(sa[j], sa[j + 1]);
    }
  }
  for (int i = m; i >= 1; i -= 2) {
    for (auto &j : in[i]) {
      if (j < ns) AddA(j);
      else if (j > ns) AddB(j);
    }
    for (auto &j: q[(i + 1) >> 1]) {
      Merge(sa[j], sa[j + 1]);
    }
    ans += ret;
  }

  //even
  ret = 0;
  for (int i = 0; i <= n; i++) pa[i] = i;
  memset(ru, 0, sizeof(ru));
  memset(a, 0, sizeof(a));
  memset(b, 0, sizeof(b));
  for (int i = 0; i <= n; ++i) {
    in[i].clear();
  }
  for (int i = 0; i <= n << 1; i += 2) {
    in[rad[i] - 1].push_back(i >> 1);
  }
  if (m % 2 == 1) --m;
  for (int i = n; i > m >> 1; --i) {
    for (auto &j: q[i]) {
      Merge(sa[j], sa[j + 1]);
    }
  }
  for (int i = m; i >= 2; i -= 2) {
    for (auto &j : in[i]) {
      if (j < ns) AddA(j);
      else if (j > ns) AddB(j);
    }
    for (auto &j: q[i >> 1]) {
      Merge(sa[j], sa[j + 1]);
    }
    ans += ret;
  }

  cout << ans << endl;

  return 0;
}

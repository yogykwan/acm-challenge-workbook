/*
 * CF 123D: String
 * 题意：给出一个字符串，枚举所有子串并按是否相同分组，若某组内个数为k，则答案累加上k(k+1)/2。求答案最终累加和。
 * 类型：后缀数组+栈
 * 算法：用'|'连接串和自己，求出后缀数组和高度数组。从正向和反向分别用栈得到每个点两侧最近的小于它的位置，则子串长度为它的串数为这段的数量。因为串重复了自己，所以除以2得到k。而固定开头后，子串可选长度为该点高度减去两侧比自己低的点中高的那个，由此避免重复计算。
 */

#include <cstdio>
#include <algorithm>
#include <stack>
#include <iostream>
#include <set>

using namespace std;

char s[200010];
int n, k;

int sa[200010];
int ra[200010], tr[200010];
int lcp[200010];

int l[200010], r[200010];
stack<int> ls, rs;
set<long long> ss;

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

inline long long Hash(int b, int c) {
  return b * 1000000ll + c;
}

int main() {
//  freopen("/Users/yogy/acm-challenge-workbook/db.in", "r", stdin);
  scanf("%s", s);
  n = strlen(s);
  s[n] = '|';
  memcpy(s + n + 1, s, sizeof(char) * n);
  n = 2 * n + 1;
  GaoSa();
  GaoLcp();

  for (int i = 0; i <= n; ++i) {
    while (!rs.empty() && lcp[rs.top()] > lcp[i]) {
      r[rs.top()] = i;
      rs.pop();
    }
    rs.push(i);
  }

  for (int i = n; i >= 0; --i) {
    while (!ls.empty() && lcp[ls.top()] > lcp[i]) {
      l[ls.top()] = i;
      ls.pop();
    }
    ls.push(i);
  }

  long long ans = 0;
  for (int i = 1; i < n - 1; ++i) {
    if (lcp[i]) {
      if (ss.find(Hash(lcp[i], l[i])) != ss.end()) continue;
      long long tmp = (r[i] - l[i]) / 2;
      tmp = tmp * (tmp + 1) / 2;
      ans += tmp * (lcp[i] - max(lcp[l[i]], lcp[r[i]]));
      ss.insert(Hash(lcp[i], l[i]));
    }
  }
  cout << ans << endl;

  return 0;
}

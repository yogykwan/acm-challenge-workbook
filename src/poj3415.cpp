/*
 * POJ 3415: Common Substrings
 * 题意：给出2个字符串和长度下限k，从2个字符串中取出长度相等且不小于下限的子串，若其相等则为一组合法解。求合法解的组数。
 * 类型：后缀数组+栈
 * 算法：将s和t用'|'拼接，求后缀数组和高度数组。将高度数组用小于k的点作为分割点分组，组内任意两个后缀的公共前缀为其所夹高度数组的最小值。组内用栈维护一个高度数组的值单调增的序列，记录当前累加和。当待选元素比栈顶小时，减法更新累加和并弹栈。
 */

#include <cstdio>
#include <algorithm>
#include <cstring>
#include <stack>

using namespace std;

typedef long long LL;

char s[200010], t[100010];
int n, k, ns, nt;

int sa[200010];
int ra[200010], tr[200010];

int lcp[200010];

int m;
int type[200010];
stack<pair<int, int> > st;

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

LL GaoStack(int a, int b) {
  while (!st.empty()) st.pop();
  LL ret = 0, tmp = 0;
  for (int i = 0; i < n; ++i) {
//    printf("%d %d %d %d\n", i, sa[i], lcp[i], type[i]);
    if (lcp[i] < m) {
      while (!st.empty()) st.pop();
      tmp = 0;
    } else {
      int cnt = 0;
      if (type[i] == a) {
        tmp += lcp[i] - m + 1;
        ++cnt;
      }
      while (!st.empty() && lcp[i] <= st.top().first) {
        cnt += st.top().second;
        tmp -= 1ll * (st.top().first - lcp[i]) * st.top().second;
        st.pop();
      }
      st.push(make_pair(lcp[i], cnt));
      if (type[i + 1] == b) {
        ret += tmp;
      }
    }
  }
  return ret;
}

int main() {
  while (scanf("%d", &m) != EOF && m) {
    scanf("%s%s", s, t);
    LL ans;
    ns = strlen(s);
    nt = strlen(t);
    s[ns] = '|';
    memcpy(s + ns + 1, t, sizeof(char) * nt);
    n = ns + nt + 1;
    GaoSa();
    GaoLcp();

    for (int i = 0; i <= n; ++i) {
      if (sa[i] < ns) {
        type[i] = 1;
      } else if (sa[i] > ns && sa[i] < n) {
        type[i] = 2;
      } else {
        type[i] = 0;
      }
    }

    ans = GaoStack(1, 2) + GaoStack(2, 1);
    printf("%lld\n", ans);
  }
  return 0;
}

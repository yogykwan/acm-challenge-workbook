/*
 * POJ 3280: Cheapest Palindrome
 * 题意：给出一个字符串，任意位置可以增加或删除字符，已知对应的代价。求让字符串转化为回文的最小代价。
 * 类型：DP
 * 算法：记忆化DP，d[i][j]表示使得s[0:i]和s[j:m]镜面的最小代价，根据s[i]和s[j]的关系，每次向左或向右转移1个字符。
 */

#include <cstdio>
#include <iostream>

using namespace std;

int d[2010][2010];
bool v[2010][2010];
int add[200];

char s[2010], ch[2];

int m;

int gao(int l, int r) {
  if(v[l][r]) {
    return d[l][r];
  }
  v[l][r] = 1;
  if(l == 0) {
    int a = 0;
    for(int i = r; i <=m; ++i) {
      a += add[s[i]];
    }
    return d[l][r] = a;
  } else if(r > m) {
    int a = 0;
    for(int i = l; i > 0; --i) {
      a += add[s[i]];
    }
    return d[l][r] = a;
  } else if(s[l] == s[r]) {
    return d[l][r] =  gao(l - 1, r + 1);
  } else {
    return d[l][r] = min(gao(l - 1, r) + add[s[l]], gao(l, r + 1) + add[s[r]]);
  }
}

int main () {
//  freopen("/Users/yogy/acm-challenge-workbook/db.in", "r", stdin);
  int n;
  scanf("%d%d%s", &n, &m, s+1);
  for(int i = 0; i < n; ++i) {
    scanf("%s", ch);
    int a, b;
    scanf("%d%d", &a, &b);
    add[ch[0]] = min(a, b);
  }
  int ans;
  ans = gao(0, 2);
  for(int i = 2; i <= m; ++i) {
      ans = min(ans, gao(i - 1, i + 1));
      ans = min(ans, gao(i - 1, i));
  }
  printf("%d\n", ans);

  return 0;
}
/*
 * CF 86C: Genetic Engineering
 * 题意：给出若干基因串作为字典，求长度为n且可由字典中的串完全可重叠覆盖的母串有多少种。
 * 类型：DP（／AC自动机）
 * 算法：所有前缀作为状态，预处理出通过在状态i最后添加某个基因字符转移到的长度最长的状态j，同时预处理出每个状态的后缀可以覆盖的最长的完整字典串。d[i][j][k]表示生成长为i的串且当前后缀匹配的最长状态为j时，最后有k个无法匹配字符的不同的母串数。
 */


#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

const int MOD = 1000000009;

string rule[11];
string prefix[110];
int maxrule[110];
int t[110][4];

char dic[] = {'A', 'C', 'G', 'T'};

int n, m, np;

int d[1010][110][11];

void GaoDic() {
  for (int i = 0; i < np; ++i) {
    for (int j = 0; j < m; ++j) {
      if (prefix[i].length() >= rule[j].length() &&
          prefix[i].substr(prefix[i].length() - rule[j].length()) == rule[j]) {
        maxrule[i] = max(maxrule[i], (int) rule[j].length());
      }
    }
  }
}

void GaoEdge() {
  for (int i = 0; i < np; ++i) {
    for (int k = 0; k < 4; ++k) {
      string ts = prefix[i] + dic[k];
      for (int j = 0; j < np; ++j) {
        if (ts.length() >= prefix[j].length() && ts.substr(ts.length() - prefix[j].length()) == prefix[j] &&
            prefix[j].length() > prefix[t[i][k]].length()) {
          t[i][k] = j;
        }
      }
    }
  }
}

void DP() {
  d[0][0][0] = 1;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < np; ++j) {
      for (int k = 0; k <= prefix[j].length(); ++k) {
        if (!d[i][j][k]) continue;
        for (int c = 0; c < 4; ++c) {
          int nj = t[j][c];
          if (maxrule[nj] >= k + 1) {
            d[i + 1][nj][0] = (d[i + 1][nj][0] + d[i][j][k]) % MOD;
          } else if (k + 1 <= prefix[nj].length()) {
            d[i + 1][nj][k + 1] = (d[i + 1][nj][k + 1] + d[i][j][k]) % MOD;
          }
        }
      }
    }
  }
}

int main() {
//  freopen("/Users/yogy/acm-challenge-workbook/db.in", "r", stdin);
  prefix[np++] = "";
  cin >> n >> m;
  for (int i = 0; i < m; ++i) {
    cin >> rule[i];
    for (int j = 1; j <= rule[i].length(); ++j) {
      prefix[np++] = rule[i].substr(0, j);
    }
  }
  sort(prefix, prefix + np);
  np = unique(prefix, prefix + np) - prefix;

  GaoDic();

  GaoEdge();

  DP();
  int ans = 0;
  for (int i = 0; i < np; ++i) {
    ans = (ans + d[n][i][0]) % MOD;
  }
  cout << ans << endl;
  return 0;
}

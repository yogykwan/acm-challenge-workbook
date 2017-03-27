/*
 * POJ 1795: DNA Laboratory
 * 题意：给出多个DNA串，求一个包含所有串的长串，且字典序最小。
 * 类型：状态DP
 * 算法：预处理去掉重复或被完全包含的串，计算两两间重叠部分构成边权。状态由最后的串号和已经包含的所有串组成，转移使用预处理得到的边。最小字典序解利用回溯，标记所有最优状态点，再一个个增加前驱正确的串，每次选择后缀字典序最小的。PS：记录每个状态的前驱或答案串都会MLE。
 */


#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

const int INF = 0x3f3f3f3f;

int e[15][15];  // 后缀权
string ss[15][15];  // 后缀串

int d[15][1 << 15]; // 最短长度
bool hb[15][1 << 15]; // 最优标记

string s[15]; // 输入串
int n;  // 输入串个数

int status[15][1 << 15];  // 二进制中特定个数1的数
int cnt[15];  // 二进制中特定个数1的数的个数

void pre_string() {
  sort(s, s + n);
  n = unique(s, s + n) - s;

  bool sub[15];
  memset(sub, 0, sizeof(sub));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i == j) continue;
      if (s[i].find(s[j]) != string::npos) {
        sub[j] = 1;
      }
    }
  }
  int m = 0;
  for (int i = 0; i < n; ++i) {
    if (!sub[i]) {
      s[m++] = s[i];
    }
  }
  n = m;
}

void pre_status() {
  memset(cnt, 0, sizeof(cnt));
  for (int i = (1 << n) - 2; i; --i) {
    int x = i, t = 0;
    while (x) {
      ++t;
      x -= x & -x;
    }
    status[t][cnt[t]++] = i;
  }
}

void pre_edge() {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i == j) continue;
      string &s1 = s[i], &s2 = s[j];
      int c = s2.length();
      string ts = s2;

      for (int k = s1.length() > s2.length() ? s1.length() - s2.length() : 0; k < s1.length(); ++k) {
        if (s1.substr(k) == s2.substr(0, s1.length() - k)) {
          c = s2.length() - s1.length() + k;
          ts = s2.substr(s1.length() - k);
          break;
        }
      }
      e[i][j] = c;
      ss[i][j] = ts;
    }
  }
}

void dp() {
  memset(d, 0x3f, sizeof(d));
  for (int i = 0; i < n; ++i) {
    d[i][1 << i] = s[i].length();
  }

  int ii[15], jj[15];
  int ci, cj;

  for (int r = 1; r < n; ++r) {
    for (int k = 0; k < cnt[r]; ++k) {
      int s1, t;
      ci = cj = 0;
      s1 = status[r][k];
      t = s1;
      for (int i = 0; i < n; ++i) {
        if (t & 1) ii[ci++] = i;
        else jj[cj++] = i;
        t >>= 1;
      }

      for (int u = 0; u < ci; ++u) {
        int i = ii[u];
        for (int v = 0; v < cj; ++v) {
          int j = jj[v];
          int s2 = 1 << j | s1;
          int dt = d[i][s1] + e[i][j];
          if (dt < d[j][s2]) {
            d[j][s2] = dt;
          }
        }
      }
    }
  }
}

void back(int j, int s2) {
  if (hb[j][s2]) return;
  hb[j][s2] = true;
  int s1 = 1 << j ^ s2;
  int t = s1;
  for (int i = 0; i < n && t; ++i) {
    if (t & 1) {
      if (d[i][s1] + e[i][j] == d[j][s2]) {
        back(i, s1);
      }
    }
    t >>= 1;
  }
}

void pre_back() {
  int ans = INF;
  int end = (1 << n) - 1;
  for (int i = 0; i < n; ++i) {
    if (d[i][end] < ans) {
      ans = d[i][end];
    }
  }
  memset(hb, 0, sizeof(hb));
  for (int i = 0; i < n; ++i) {
    if (d[i][end] == ans) {
      back(i, end);
    }
  }
}

string get_string() {
  string anss = "Z";
  int lp;
  int ls;
  for (int i = 0; i < n; ++i) {
    if (hb[i][1 << i]) {
      lp = i;
      ls = 1 << i;
      anss = s[i];
      break;
    }
  }
  for (int r = 1; r < n; ++r) {
    string tss = "Z";
    int tlp, tls;
    for (int j = 0; j < n; ++j) {
      int ts = 1 << j | ls;
      if (ts > ls && hb[j][ts] && d[lp][ls] + e[lp][j] == d[j][ts]) {
        if (ss[lp][j] < tss) {
          tlp = j;
          tls = ts;
          tss = ss[lp][j];
        }
      }
    }
    lp = tlp;
    ls = tls;
    anss += tss;
  }
  return anss;
}

int main() {
//  freopen("/Users/yogy/acm-challenge-workbook/db.in", "r", stdin);
  int T;
  cin >> T;
  for (int tc = 1; tc <= T; ++tc) {

    cin >> n;
    for (int i = 0; i < n; ++i) {
      cin >> s[i];
    }
    pre_string();

    if (n == 1) {
      printf("Scenario #%d:\n%s\n\n", tc, s[0].c_str());
      continue;
    }

    pre_status();

    pre_edge();

    dp();

    pre_back();

    string anss = get_string();

    printf("Scenario #%d:\n%s\n\n", tc, anss.c_str());  // cout输出空行
  }
  return 0;
}
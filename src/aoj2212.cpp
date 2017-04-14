/*
 * AOJ 2212: Stolen Jewel
 * 题意：地图上从起点走到终点，轨迹用四个方向的序列表示。同时给出多个禁止串，不允许轨迹序列中包含禁止字符串。此时，求到达终点的最小步数。
 * 类型：DP+最短路（／AC自动机）
 * 算法：禁止规则的所有前缀作为状态，预处理出通过在状态i最后添加某个方向字符转移到长度最长的状态j。d[x][y][i]表示从(x,y)轨迹后缀i的最小步数，用Dijkstra找到到达终点的最短路。
 */

#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>


using namespace std;


int m, n, nr, ns;
string mat[53];
string rule[13];

int d[53][53][113];
int t[113][4];
string suf[113];

int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};
char dc[] = {'U', 'R', 'D', 'L'};


struct Status {
  int x, y, s, d;

  Status() {}

  Status(int dd, int xx, int yy, int ss) : d(dd), x(xx), y(yy), s(ss) {}

  void Get(int &dd, int &xx, int &yy, int &ss) const {
    dd = d;
    xx = x;
    yy = y;
    ss = s;
  }

  bool operator<(const Status &ts) const {
    return d > ts.d;
  }
};

priority_queue<Status> pq;

int Dijkstra() {
  while (!pq.empty()) pq.pop();
  memset(d, 0x3f, sizeof(d));
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if (mat[i][j] == 'S') {
        d[i][j][0] = 0;
        pq.emplace(0, i, j, 0);
        goto L;
      }
    }
  }
  L:
  int ans = -1;
  while (!pq.empty()) {
    int pre, x, y, s;
    pq.top().Get(pre, x, y, s);
    pq.pop();
    if (pre > d[x][y][s]) continue;
    for (int k = 0; k < 4; ++k) {
      int xx, yy, ss;
      ss = t[s][k];
      if (ss == -1) continue;
      xx = x + dx[k];
      yy = y + dy[k];

      if (xx >= 0 && xx < m && yy >= 0 && yy < n && mat[xx][yy] != '#' && pre + 1 < d[xx][yy][ss]) {
        if (mat[xx][yy] == 'G') {
          ans = pre + 1;
          return ans;
        }
        d[xx][yy][ss] = pre + 1;
        pq.emplace(pre + 1, xx, yy, ss);
      }
    }
  }
  return ans;
}


bool IsSuf(string a, string b) {
  if (a.length() < b.length()) return false;
  return a.substr(a.length() - b.length()) == b;
}

void GaoEdge() {
  sort(suf, suf + ns);
  ns = unique(suf, suf + ns) - suf;
  memset(t, 0, sizeof(t));
  for (int i = 0; i < ns; ++i) {
    for (int k = 0; k < 4; ++k) {
      string ts = suf[i] + dc[k];
      for (int j = 0; j < nr; ++j) {
        if (IsSuf(ts, rule[j])) {
          t[i][k] = -1;
          break;
        }
      }
      if (t[i][k] != -1) {
        for (int j = 0; j < ns; ++j) {
          if (IsSuf(ts, suf[j]) && suf[j].length() > suf[t[i][k]].length()) {
            t[i][k] = j;
          }
        }
      }
    }
  }
}


int main() {
  //freopen("/Users/yogy/acm-challenge-workbook/db.in", "r", stdin);
  while (cin >> m >> n && m > 0 && n > 0) {
    for (int i = 0; i < m; ++i) {
      cin >> mat[i];
    }
    cin >> nr;
    ns = 0;
    suf[ns++] = "";
    for (int i = 0; i < nr; ++i) {
      cin >> rule[i];
      for (int j = 1; j < rule[i].length(); ++j) {
        suf[ns++] = rule[i].substr(0, j);
      }
    }
    GaoEdge();
    int ans = Dijkstra();
    cout << ans << endl;
  }
  return 0;
}

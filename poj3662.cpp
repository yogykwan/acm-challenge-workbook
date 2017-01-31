/*
 * POJ 3662: Telephone Lines
 * 题意：n个点之间有p条待选的边，选择若干使得1和n联通。为去除k条免费边后，需为剩余边中的最长边付费，求最小费用。
 * 类型：二分搜索+最短路
 * 算法：二分搜索付费边长m。规定大于m的边边权为1，否则为0，Dijkstra得到1到n的最短路。若最短路不超过k则更新下届，否则上界。
 */

#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

typedef pair<int, int> pii;

priority_queue<pii, vector<pii>, greater<pii> > pq;

int w[10010];

vector<pii> e[1010];

int d[1010];

int main() {
  int n, p, k;
  int u, v, c, du;
  scanf("%d%d%d", &n, &p, &k);
  for(int i = 1; i <= p; ++i) {
    scanf("%d%d%d", &u, &v, &c);
    e[u].push_back(make_pair(v, c));
    e[v].push_back(make_pair(u, c));
    w[i] = c;
  }
  w[0] = 0; // all cables can be free
  sort(w, w + p + 1);
  p = unique(w, w + p + 1) - w;

  int l, r, m;
  l = -1;
  r = p - 1;
  while(l + 1 < r) {
    m = (l + r) >> 1;

    memset(d, 0x3f, sizeof(d)); // Dijkstra
    while(!pq.empty()) pq.pop();
    d[1] = 0;
    pq.push(make_pair(0, 1));
    while(!pq.empty()) {
      u = pq.top().second;
      du = pq.top().first;
      pq.pop();
      if(d[u] < du) continue;
      if(u == n) break;
      for(vector<pii>::iterator it = e[u].begin(); it != e[u].end(); ++it) {
        v = (*it).first;
        c = (*it).second > w[m];
        if(du + c < d[v]) {
          d[v] = du + c;
          pq.push(make_pair(d[v], v));
        }
      }
    }

    if(d[n] > n) {
      printf("-1\n");
      return 0;
    }
    if(d[n] <= k) {
      r = m;
    } else {
      l = m;
    }
  }
  printf("%d\n", w[r]);
  return 0;
}
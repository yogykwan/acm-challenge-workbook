/*
 * POJ 3109: Inner Vertices
 * 题意：无限坐标系中给出一些黑点，每一步，如果一个白点横向和竖向都被两个黑点夹着，则将其染为黑色。求最后一共多少个黑点，不会停止则输出错误。
 * 类型：离散化+扫描线+树状数组（／线段树）
 * 算法：分析可知一步后总会停止，用树状数组统计新增黑点数。先将横纵坐标离散化，将点按x排序，得到每条x线，将其按单点、头、尾、中标记为4类，同时预处理出每个y对应最大x和最小x。再将点按y排序后，用y线扫描。查询前把尾中在树状数组中对应的x处-1；统计树状数组在最大最小x间的和为当前y线上新增黑点数；再将头中对应x处+1。
 */

#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <map>
#include <vector>

using namespace std;

const int MAXN = 100010;

class Node {
public:
  Node(): type(0) {}
  int x, y;
  int type;

  bool operator < (const Node &a) const{
    if (y != a.y) return y < a.y;
    return x < a.x;
  }

  bool operator== (const Node &a) const {
    return (x == a.x) && (y == a.y);
  }
};

Node ns[MAXN];
map<int, int> map_x, map_y;
vector<Node*> line[MAXN];
int x[MAXN], y[MAXN];
int max_y[MAXN], min_y[MAXN];

int bit[MAXN];
int n, nx, ny;

int low_bit(int x) {
  return x&-x;
}

void change(int x, int d) {
  ++x;
  while (x <= ny) {
    bit[x] += d;
    x += low_bit(x);
  }
}

int query(int x) {
  int ans = 0;
  ++x;
  while (x) {
    ans += bit[x];
    x -= low_bit(x);
  }
  return ans;
}

int main() {
//  freopen("/Users/yogy/acm-challenge-workbook/db.in", "r", stdin);
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d", &x[i], &y[i]);
    ns[i].x = x[i];
    ns[i].y = y[i];
  }

  if (n < 2) {
    printf("%d\n", n);
    return 0;
  }

  sort(x, x + n);
  sort(y, y + n);
  nx = unique(x, x + n) - x;
  ny = unique(y, y + n) - y;

  sort(ns, ns + n);
  int ans = n;

  memset(max_y, -1, sizeof(max_y));
  int i = 0;
  ns[i].x = lower_bound(x, x + nx, ns[i].x) - x;  // map will TLE, use lower_bound instead
  ns[i].y = lower_bound(y, y + ny, ns[i].y) - y;
  int xx = ns[i].x;
  min_y[xx] = max_y[xx] = ns[i].y;
  line[xx].push_back(&ns[i]);

  for (int i = 1; i < n; ++i) {
    ns[i].x = lower_bound(x, x + nx, ns[i].x) - x;
    ns[i].y = lower_bound(y, y + ny, ns[i].y) - y;
    int xx = ns[i].x;
    if (ns[i].y == ns[i - 1].y) {
      ns[i - 1].type |= 1;
      ns[i].type |= 2;
    }
    if (max_y[xx] == -1) {
      min_y[xx] = max_y[xx] = ns[i].y;
    } else {
      min_y[xx] = min(min_y[xx], ns[i].y);
      max_y[xx] = max(max_y[xx], ns[i].y);
    }
    line[xx].push_back(&ns[i]);
  }

  for (int i = 0; i < nx; ++i) {
    int y, type;
    vector<Node *>::iterator it;
    for (it = line[i].begin(); it != line[i].end(); ++it) {
      y = (*it)->y;
      type = (*it)->type;
      if (type & 2) {
        change(y, -1);
      }
    }

    ans += query(max_y[i]) - query(min_y[i] - 1);

    for (it = line[i].begin(); it != line[i].end(); ++it) {
      y = (*it)->y;
      type = (*it)->type;
      if (type & 1) {
        change(y, 1);
      }
    }
  }
  printf("%d\n", ans);

  return 0;
}
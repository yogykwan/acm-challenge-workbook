/*
 * POJ 1328: Radar Installation
 * 题意：给出海面上n个岛的坐标，在x轴上放置半径为d的雷达，使得所有岛被覆盖的雷达最少数量。
 * 类型：贪心
 * 算法：以每个岛为圆心，半径为画圆，得到与x轴相交形成的区间。将完全包含其他区间的大区间标记为删除，然后按左端点排序。遍历所有区间，每次取第1个并计数+1，标记删去所有与其相交的区间。判断浮点数大小关系要用EPS。
 */

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

const double EPS = 1e-6;

pair <double, double> pii[1010];

bool deleted[1010];

int main() {
  int n, d;
  bool ok;
  int tc = 0;
  while(scanf("%d%d", &n, &d) != EOF && n) {
    ok = true;
    for(int i = 0; i < n; ++i) {
      int x, y;
      scanf("%d%d", &x, &y);
      if(y > d || y < -d) {
        ok = false;
        continue;
      }
      pii[i].first = -sqrt(d * d - y * y) + x;
      pii[i].second = sqrt(d * d - y * y) + x;
    }

    printf("Case %d: ", ++tc);

    if(!ok) {
      printf("-1\n");
      continue;
    }

    memset(deleted, 0, sizeof(deleted));

    sort(pii, pii + n);
    for(int i = 0; i < n; ++i) {
      for(int j = i + 1; j < n; ++j) {
        if(pii[j].second < pii[i].second + EPS) { // <=
          deleted[i] = true;
        }
      }
    }

    int cnt = 0, i, j;
    for(i = 0; i < n; ) {
      while(deleted[i] && i < n){
        ++i;
      }
      if(i == n) break;
      ++cnt;
      for(j = i + 1; j < n; ++j) {
        if(pii[j].first > pii[i].second + EPS) {  // >
          break;
        }
      }
      i = j;
    }
    printf("%d\n", cnt);
  }
  return 0;
}
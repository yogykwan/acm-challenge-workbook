/*
 * POJ 1486: Sorting Slides
 * 题意：每张幻灯片上某个不定位置会有它的唯一编号，给出多个幻灯片的坐标范围和每个编号的坐标。求每张幻灯片正确对应的编号，如果编号不能唯一确定输出none。
 * 类型：二分匹配
 * 算法：根据坐标两两比较得到每张幻灯片可选的编号列表。匈牙利算法求最大二分匹配，编号在左，幻灯片在右，dfs时得到每张幻灯片的编号。为确定是否匹配唯一，可枚举第每张幻灯的编号，在图中不考虑这两个点看是否存在多次满匹配的情况。
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

bool e[30][30];
bool vis[30];
int rec[30];
int n1, n2;

int s, t;
int ans[30];
pair<int, int> out[30];

bool Dfs(int u) {
  for (int i = 0; i < n2; ++i) {
    if (i == t) continue;
    if (e[u][i] && !vis[i]) {
      vis[i] = 1;
      if (rec[i] == -1 || Dfs(rec[i])) {
        rec[i] = u;
        return true;
      }
    }
  }
  return false;
}

bool Hungary() {
  memset(rec, -1, sizeof(rec));
  int ans = 0;
  for (int i = 0; i < n1; ++i) {
    if (i == s) continue;
    memset(vis, 0, sizeof(vis));
    if (!Dfs(i)) return false;
  }
  return true;
}

struct Slide {
  int x1, x2, y1, y2;
} slide[30];

int main() {
//  freopen("/Users/yogy/acm-challenge-workbook/db.in", "r", stdin);
  int n;
  int tc = 0;
  while (scanf("%d", &n) != EOF && n) {
    n1 = n2 = n;
    memset(e, 0, sizeof(e));
    for (int i = 0; i < n; ++i) {
      scanf("%d%d%d%d", &slide[i].x1, &slide[i].x2, &slide[i].y1, &slide[i].y2);
    }
    for (int i = 0; i < n; ++i) {
      int x, y;
      scanf("%d%d", &x, &y);
      for (int j = 0; j < n; ++j) {
        if (x > slide[j].x1 && x < slide[j].x2 && y > slide[j].y1 && y < slide[j].y2) {
          e[i][j] = 1;
        }
      }
    }

    memset(ans, -1, sizeof(ans));
    for (int i = 0; i < n; ++i) {
      for (int j = 0 ; j < n; ++j) {
        if (!e[j][i]) continue;
        s = j;
        t = i;
        if (Hungary()) {
          if (ans[i] != -1) {
            ans[i] = -1;
            break;
          }
          ans[i] = j;
        }
      }
    }

    int cnt = 0;
    for (int i = 0; i< n; ++i) {
      if (ans[i] != -1)
      out[cnt++] = make_pair(i, ans[i]);
    }


    printf("Heap %d\n", ++tc);
    if (!cnt) {
      printf("none\n\n");
    } else {
      for (int i = 0; i < cnt; ++i) {
        printf("(%c,%d)%c", 'A' + out[i].first, out[i].second + 1, i < cnt - 1 ? ' ' : '\n');
      }
      printf("\n");
    }
  }
  return 0;
}

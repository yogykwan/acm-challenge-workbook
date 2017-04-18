/*
 * POJ 1011: Sticks
 * 题意：若干长度相同的棍子剪成若干节，给出剪完的结果，求原本完整棍子的最小长度。
 * 类型：DFS
 * 算法：候选长度一定大于等于最大的木棍节，并且为所有木棍长度和的约数。依次枚举待选解，DFS判断是否可行。DFS时将木棍从长到短排列，每次第一个没取的必须取。
 */

#include <cstdio>
#include <algorithm>
#include <cstring>


using namespace std;

int a[70];
int len;
int n;
int m;
bool vis[70];

bool dfs(int b, int cur, int cnt) {
  if (cur == len) {
    ++cnt;
    if (cnt == m) {
      return 1;
    } else {
      for (int i = 0; i < n; ++i) {
        if (!vis[i]) {
          vis[i] = 1;
          if (dfs(i + 1, a[i], cnt)) {
            return 1;
          } else {
            vis[i] = 0;
            return 0;
          }
        }
      }
    }
  } else {

    for (int i = b; i < n; ++i) {
      if (vis[i] || cur + a[i] > len || (i && !vis[i - 1] && a[i] == a[i - 1])) continue; // 重要剪枝：和前一个相同，前一个使用无效，则当前也会无效
      vis[i] = 1;

      if (dfs(i + 1, cur + a[i], cnt)) {
        return 1;
      }
      vis[i] = 0;
    }
  }
  return 0;
}

int main() {
//  freopen("/Users/yogy/acm-challenge-workbook/db.in", "r", stdin);
  int s;
  while (scanf("%d", &n) != EOF && n) {
    s = 0;
    for (int i = 0; i < n; ++i) {
      scanf("%d", &a[i]);
      s += a[i];
    }
    sort(a, a + n);
    reverse(a, a + n);

    int ans = s;
    for (len = a[0]; len < s; ++len) {
      if (s % len) continue;
      memset(vis, 0, sizeof(vis));
      m = s / len;
      vis[0] = 1;
      if (dfs(1, a[0], 0)) {
        ans = len;
        break;
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}
/*
 * CF 138D: World of Darkraft
 * 题意：n行m列的图，图上字符L表示从该点向左下和右上发射光波，沿路毁坏点，直到撞到之前毁坏过的点。R向左上和右下，X向上述4个方向。两人轮流选点，问先手胜负。
 * 类型：Grundy博弈
 * 算法：横纵坐标相加为奇数和偶数的两个游戏独立。整个图顺时针旋转45度，这样每次L就是横向分割，R就是纵向分割，X分为四块。枚举范围内所有点，得到周围子游戏seg的xor，更新当前的seg值。全局seg为0必败否则必胜。
 */

#include <cstdio>
#include <cstring>
using namespace std;

int sg[44][44][44][44][2];
char mat[22][22];
int m, n;

int dp(int x1, int x2, int y1, int y2, int odd) {
  if (x2 - x1 < 1 || y2 - y1 < 1) return 0;
  if (sg[x1][x2][y1][y2][odd] != -1) return sg[x1][x2][y1][y2][odd];
  bool vis[1700] = {0};
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if ((i + j) % 2 != odd) continue;
      int x, y, t = 0;
      x = i + j;
      y = j - i + m - 1;
      if (x >= x1 && x < x2 && y >= y1 && y < y2) {
        char ch = mat[j][i];
        if (ch == 'R') {
          t = dp(x1, x, y1, y2, odd) ^ dp(x + 1, x2, y1, y2, odd);
        } else if (ch == 'L') {
          t = dp(x1, x2, y1, y, odd) ^ dp(x1, x2, y + 1, y2, odd);
        } else if (ch == 'X') {
          t = dp(x1, x, y1, y, odd) ^ dp(x + 1, x2, y1, y, odd) ^
              dp(x1, x, y + 1, y2, odd) ^ dp(x + 1, x2, y + 1, y2, odd);
        }
        vis[t] = 1;
      }
    }
  }
  int i = 0;
  while (vis[i]) ++i;
  return sg[x1][x2][y1][y2][odd] = i;
}


int main() {
  memset(sg, -1, sizeof(sg));
  scanf("%d%d", &n, &m);
  for (int i = n - 1; i >= 0; --i) {
    scanf("%s", mat[i]);
  }
  int mn = m + n - 1;
  int ans = dp(0, mn, 0, mn, 0) ^ dp(0, mn, 0, mn, 1);
  printf("%s\n", ans > 0 ? "WIN" : "LOSE");
  return 0;
}

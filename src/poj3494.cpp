/*
 * POJ 3494: Largest Submatrix of All 1’s
 * 题意：给出一个01矩阵，求全为1的面积最大的子矩阵的面积。
 * 类型：栈
 * 算法：枚举子矩阵的下边界，预处理出从每个点向上最多能连续的1的高度。对于每个下边界，得到每列的左右最近的比它低的位置求面积。
 */

#include <cstdio>
#include <stack>
#include <cstring>

using namespace std;

int h[2010];
int l[2010], r[2010];

bool mat[2010][2010];

stack<int> s;

int main () {
//  freopen("/Users/yogy/acm-challenge-workbook/db.in", "r", stdin);
  int m, n;
  while (scanf("%d%d", &m, &n) != EOF) {
    for (int i = 1; i <= m; ++i) {
      for (int j = 1; j <= n; ++j) {
        scanf("%d", &mat[i][j]);
      }
    }
    int ans = 0;
    memset(h, 0, sizeof(h));
    for (int i = 1; i <= m; ++i) {
      for (int j = 1; j <= n; ++j) {
        if (mat[i][j]) {
          ++h[j];
        } else {
          h[j] = 0;
        }
      }
      h[0] = h[n + 1] = -1;

      while (!s.empty()) s.pop();
      for (int k = 1; k <= n + 1; ++k) {
        while (!s.empty()) {
          if (h[s.top()] > h[k]) {
            r[s.top()] = k;
            s.pop();
          } else break;
        }
        s.push(k);
      }
      while (!s.empty()) s.pop();
      for (int k = n; k >= 0; --k) {
        while (!s.empty()) {
          if (h[s.top()] > h[k]) {
            l[s.top()] = k;
            s.pop();
          } else break;
        }
        s.push(k);
      }
      for (int k = 1; k <= n; ++k) {
        if (h[k]) {
          ans = max(ans, h[k] * (r[k] - l[k] - 1));
        }
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}


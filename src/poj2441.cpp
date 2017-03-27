/*
 * POJ 2441: Arrange the Bulls
 * 题意：共n个牛，m个棚，每个牛有几个可选的牛棚。求使得每头牛都在不同牛棚中的方案数。
 * 类型：状态DP
 * 算法：二进制表示当前牛棚被选状态，每头牛加入时，对应将1的个数为牛数的dp值更新，转移采用或运算。
 */


#include <cstdio>
#include <vector>

using namespace std;

int d[1 << 20];
vector<int> s[20];
int b[20][20];
int c[20];

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &c[i]);
    for (int j = 0; j < c[i]; ++j) {
      scanf("%d", &b[i][j]);
      --b[i][j];
    }
  }
  if (n > m) {
    printf("0\n");
    return 0;
  }

  for (int i = (1 << m) - 1; i > 0; --i) {
    int x = i;
    int cnt = 0;
    while (x) {
      ++cnt;
      x -= x & -x;
    }
    s[cnt - 1].push_back(i);
  }

  int ans = 0;

  d[0] = 1;
  for (int i = 0; i < n; ++i) {
    for (int j = int(s[i].size() - 1); j >= 0; --j) {
      for (int k = 0; k < c[i]; ++k) {
        int op = 1 << b[i][k];
        if (s[i][j] & op) {
          d[s[i][j]] += d[s[i][j] ^ op];
        }
      }
      if (i == n - 1) {
        ans += d[s[i][j]];
      }
    }
  }

  printf("%d\n", ans);

  return 0;
}

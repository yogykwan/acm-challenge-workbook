/*
 * AOJ 2200: Mr. Rito Post Office
 * 题意：给出岛之间的若干水路和陆路，水路转为陆路时船就停在那，之后要陆路转水路还得从那开始。求按给出的可重复序列通过多个岛的最短时间。
 * 类型：最短路+DP
 * 算法：先用Floyd预处理出单独走水路s或陆路l的两两之间的最短路。d[i][j]表示到序列第i点时船停在j。状态转移：人从a到b，船从c到d，若船动加上l[a,c]+s[c,d]+l[d,b]，若船不动则只要加上l[a][b]。
 */


#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int s[210][210];
int l[210][210];
int d[1010][210];
int b[1010];

const int INF = 0x3f3f3f3f;

void Floyd(int n) {
  for (int k = 1; k <= n; ++k) {
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= n; ++j) {
        s[i][j] = min(s[i][j], s[i][k] + s[k][j]);
        l[i][j] = min(l[i][j], l[i][k] + l[k][j]);
      }
    }
  }
}

int main() {
  int n, m, r;
  int u, v, c;
  char tp[3];

  while (scanf("%d%d", &n, &m) != EOF && n) {
    memset(s, 0x3f, sizeof(s));
    memset(l, 0x3f, sizeof(l));
    memset(d, 0x3f, sizeof(d));

    while (m--) {
      scanf("%d%d%d%s", &u, &v, &c, tp);
      if (tp[0] == 'L') {
        l[u][v] = min(l[u][v], c);
        l[v][u] = min(l[v][u], c);
      } else {
        s[u][v] = min(s[u][v], c);
        s[v][u] = min(s[v][u], c);
      }
    }

    for (int i = 1; i <= n; ++i) {
      l[i][i] = 0;
      s[i][i] = 0;
    }

    scanf("%d", &r);

    for (int i = 1; i <= r; ++i) {
      scanf("%d", &b[i]);
    }

    Floyd(n);

    for (int i = 1; i <= n; ++i) {
      d[1][i] = min(d[1][i], s[b[1]][i] + l[i][b[1]]);
    }

    for (int i = 1; i <= r; ++i) {
      for (int j = 1; j <= n; ++j) {
        if (l[j][b[i]] >= INF) continue;
        for (int k = 1; k <= n; ++k) {
          if (d[i - 1][k] >= INF) continue;
          if (j == k) {
            if (l[b[i - 1]][b[i]] < INF) {
              d[i][j] = min(d[i][j], d[i - 1][k] + l[b[i - 1]][b[i]]);
            }
          } else {
            if (l[b[i - 1]][k] < INF && s[k][j] < INF && l[j][b[i]] < INF) {
              d[i][j] = min(d[i][j], d[i - 1][k] + l[b[i - 1]][k] + s[k][j] + l[j][b[i]]);
            }
          }
        }
      }
    }

    int ans = INF;
    for (int j = 1; j <= n; ++j) {
      ans = min(ans, d[r][j]);
    }
    printf("%d\n", ans);
  }
  return 0;
}

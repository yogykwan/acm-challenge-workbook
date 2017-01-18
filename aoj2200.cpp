/*
 * AOJ 2200: Mr. Rito Post Office
 * 题意：给出岛之间的若干水路和陆路，水路转为陆路时船就停在那，之后要陆路转水路还得从那开始。求按给出的可重复序列通过多个岛的最短时间。
 * 类型：最短路+DP
 * 算法：先用Floyd预处理出单独走水路s或陆路l的两两之间的最短路。d[i][j]表示已经达到序列第i个点，并将船停在了j的位置。人从a到b，船从c到d，则时间要加上l[a,c]+s[c,d]+l[d,b]。再用s[a,b]+l[b,a]的环路将船移动而人不动，使得可能出现的状态d值都合法。
 */

#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int s[210][210];
int l[210][210];
int q[210][210];
int d[1010][210];
int b[1010];

const int INF = 0x7ffffff;

void Floyd(int n) {
  for(int i = 1; i <= n; ++i) {
    for(int j = 1; j <= n; ++j) {
      for(int k = 1; k <= n; ++k) {
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

  while(scanf("%d%d", &n, &m) != EOF && n) {
    memset(s, 0x3f, sizeof(s));
    memset(l, 0x3f, sizeof(l));
    memset(d, 0x3f, sizeof(d));
    memset(q, 0x3f, sizeof(q));

    while(m--) {
      scanf("%d%d%d%s", &u, &v, &c, tp);
      if(tp[0] == 'L') {
        l[u][v] = min(l[u][v], c);
        l[v][u] = min(l[v][u], c);
      } else {
        s[u][v] = min(s[u][v], c);
        s[v][u] = min(s[v][u], c);
      }
    }

    for(int i = 1; i <= n; ++i) {
      l[i][i] = 0;
      s[i][i] = 0;
    }

    scanf("%d", &r);
    b[0] = 1;
    for(int i = 1; i <= r; ++i) {
      scanf("%d", &b[i]);
    }

    Floyd(n);

    for(int i = 1; i <= n; ++i) {
      for (int j = 1; j <= n; ++j) {
        if(s[i][j] < INF && l[i][j] < INF) {
          q[i][j] = s[i][j] + l[i][j];
        }
      }
    }

    d[0][1] = 0;

    for(int i = 1; i <= r; ++i) {
      for(int j = 1; j <= n; ++j) {
        if(l[j][b[i]] >= INF) continue;
        for(int k = 1; k <= n; ++k) {
          if(d[i-1][k] < INF && l[b[i-1]][k] < INF && s[k][j] < INF) {
            d[i][j] = min(d[i][j], d[i-1][k] + l[b[i-1]][k] + s[k][j] + l[j][b[i]]);
          }
        }
      }
      for(int j = 1; j <= n; ++j) {
        if(d[i][b[i]] < INF && q[b[i]][j] < INF) {
          d[i][j] = min(d[i][j], d[i][b[i]] + q[b[i]][j]);
        }
      }
    }

    int ans = INF;
    for(int j = 1; j <= n; ++j) {
      ans = min(ans, d[r][j]);
    }
    printf("%d\n", ans);
  }
  return 0;
}
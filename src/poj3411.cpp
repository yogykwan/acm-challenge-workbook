/*
 * POJ 3411: Paid Roads
 * 题意：给出一个只含单向的图，每条边的花费有两种方式支付，在制定点提前支付比在边终点支付费用优惠。求1到n的最小花费是多少？
 * 类型：状态DP+最短路
 * 算法：当前点和已经走过的点构成状态，每次从队列中取出头结点像所有它出发的边扩展，每次dp值更新则将边终点放入队列。
 */


#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

int m, n;

struct Edge {
  int b, c, P, R;
};

Edge e[12][12];
int cnt[12];

int d[12][1 << 10];

queue<pair<int, int> > pq;

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; ++i) {
    int a;
    scanf("%d", &a);
    --a;
    int t = cnt[a];
    scanf("%d%d%d%d", &e[a][t].b, &e[a][t].c, &e[a][t].P, &e[a][t].R);
    --e[a][t].b;
    --e[a][t].c;
    ++cnt[a];
  }
  if (n == 1) {
    printf("0\n");
    return 0;
  }
  memset(d, 0x3f, sizeof(d));
  d[0][1] = 0;
  pq.push(make_pair(0, 1));
  int ans = 0x3f3f3f3f;
  while (!pq.empty()) {
    int i, s1, s2, t;
    i = pq.front().first;
    s1 = pq.front().second;
    pq.pop();
    for (int j = 0; j < cnt[i]; ++j) {
      Edge &ee = e[i][j];
      if (1 << ee.c & s1) {
        t = d[i][s1] + ee.P;
      } else {
        t = d[i][s1] + ee.R;
      }
      s2 = 1 << ee.b | s1;
      if (t < d[ee.b][s2]) {
        d[ee.b][s2] = t;
        pq.push(make_pair(ee.b, s2));
        if (ee.b == n - 1) {
          ans = min(ans, t);
        }
      }
    }
  }
  if (ans == 0x3f3f3f3f) {
    printf("impossible\n");
  } else {
    printf("%d\n", ans);
  }

  return 0;
}


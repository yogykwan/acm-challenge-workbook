/*
 * POJ 3523: The Morning after Halloween
 * 题意：mxn的矩形里最多3只鬼，每一步可以选取若干个鬼向其四周移动一格，要求不发生碰撞。求最少多少步可将鬼复原到指定位置。
 * 类型：A*+Dijkstra+DFS
 * 算法：修改普通最短路算法最小堆的评价方式为到目前状态的步数d，加上评估从该步到终点的函数h。用Dijkstra提前预处理每个格子到目标的最短路作为h。
 */

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

typedef unsigned short US;  // 防MLE
typedef pair<US, int> psi;

int n, m, k;
char mat[16][17];
int sx[3], sy[3], tx[3], ty[3];
US h[3][16][16];

int dx[] = {0, -1, 0, 1, 0};
int dy[] = {0, 0, 1, 0, -1};

void GaoH(int t, int x, int y) {
  h[t][x][y] = 0;
  priority_queue<psi, vector<psi>, greater<psi> > pq;
  pq.push(make_pair(0, x << 4 | y));
  while (!pq.empty()) {
    US pre = pq.top().first;
    int xy = pq.top().second;
    pq.pop();
    x = xy >> 4;
    y = xy & 15;
    if (h[t][x][y] < pre) continue;
    for (int i = 1; i < 5; ++i) {
      int xx, yy;
      xx = x + dx[i];
      yy = y + dy[i];
      if (xx >= 0 && xx < m && yy >= 0 && yy < n && mat[xx][yy] != '#' && pre + 1 < h[t][xx][yy]) {
        h[t][xx][yy] = pre + (US)1;
        pq.push(make_pair(pre + 1, xx << 4 | yy));
      }
    }
  }
}

US d[1 << 24];


int GetId(int *x, int *y) {
  int id = 0;
  for (int i = 0; i < k; ++i) {
    id = id << 4 | x[i];
    id = id << 4 | y[i];
  }
  return id;
}

int GetXy(int id, int *x, int *y) {
  for (int i = k - 1; i >= 0; --i) {
    y[i] = id & 15;
    id >>= 4;
    x[i] = id & 15;
    id >>= 4;
  }
  return id;
}

US GetH(int *x, int *y) {
  US hd = 0;
  for (int i = 0; i < k; ++i) {
    hd = max(hd, h[i][x[i]][y[i]]);
  }
  return hd;
}

int mx[3], my[3];
int target;
priority_queue<psi, vector<psi>, greater<psi> > pq;

bool Legal(int *sx, int *sy, int *tx, int *ty) {
  for (int i = 0; i < k; ++i) {
    for (int j = i + 1; j < k; ++j) {
      if (tx[i] == tx[j] && ty[i] == ty[j]) return false;
      if (sx[i] == tx[j] && sy[i] == ty[j] && sx[j] == tx[i] && sy[j] == ty[i]) return false;
    }
  }
  return true;
}

bool Dfs(int cur, US pre) {
  if (cur == k) {
    if (Legal(sx, sy, mx, my)) {
//      for (int i = 0; i < k; ++i) printf("%d: %d %d -> %d %d\n", i, sx[i], sy[i], mx[i], my[i]);
      int id = GetId(mx, my);
      if (id == target) {
        d[id] = pre + (US)1;
        return true;
      }
      if (pre + (US)1 < d[id]) {
        d[id] = pre + (US)1;
        int hd = GetH(mx, my);
        pq.push(make_pair(d[id] + hd, id));
      }
    }
    return false;
  }

  for (int i = 0; i < 5; ++i) {
    mx[cur] = sx[cur] + dx[i];
    my[cur] = sy[cur] + dy[i];
    if (mx[cur] >= 0 && mx[cur] < m && my[cur] >= 0 && my[cur] < n && mat[mx[cur]][my[cur]] != '#') {
      if(Dfs(cur + 1, pre)) return true;
    }
  }
  return false;
}

US AStar() {
  target = GetId(tx, ty);
  int id = GetId(sx, sy);
  int hd = GetH(sx, sy);
  d[id] = 0;
  pq.push(make_pair(hd, id));
  while (!pq.empty()) {
    id = pq.top().second;
    pq.pop();
    GetXy(id, sx, sy);
    if (Dfs(0, d[id])) return d[target];
  }
  return d[target];
}

int main() {
  while (scanf("%d%d%d", &n, &m, &k) != EOF && n) {
    for (int i = 0; i < m; ++i) {
      getchar();
      for (int j = 0; j < n; ++j) {
        scanf("%c", &mat[i][j]);
        if (mat[i][j] >= 'A' && mat[i][j] <= 'Z') {
          tx[mat[i][j] - 'A'] = i;
          ty[mat[i][j] - 'A'] = j;
        } else if (mat[i][j] >= 'a' && mat[i][j] <= 'z') {
          sx[mat[i][j] - 'a'] = i;
          sy[mat[i][j] - 'a'] = j;
        }
      }
    }

    memset(h, 0x3f, sizeof(h));
    for (int i = 0; i < k; ++i) {
      GaoH(i, tx[i], ty[i]);
    }

    memset(d, 0x3f, sizeof(d));
    while (!pq.empty()) pq.pop();
    printf("%u\n", AStar());
  }
  return 0;
}

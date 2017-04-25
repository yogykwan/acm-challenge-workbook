/*
 * POJ 2723: Get Luffy Out
 * 题意：n对钥匙开m扇门，每扇门有2把锁，开任意一个门就可以打开。每对钥匙选其中一个就要丢弃另一个，顺序给出门上的锁对。问最多可以开多少扇门。
 * 类型：2-SAT+二分
 * 算法：一对钥匙ab等价a=>!b,b=>!a；开一扇锁为ab的门等价!a=>b,!b=>a。将钥匙的关系全部建边后，二分枚举开门数量并添加锁的边，每次强连通分量判定2-SAT即可。
 */

#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

vector<int> e[1 << 12];
vector<int> re[1 << 12];
vector<int> id;
bool vis[1 << 12];

int tot;
int tp[1 << 12];


void Dfs(int i) {
  vis[i] = 1;
  for (vector<int>::iterator it = e[i].begin(); it != e[i].end(); ++it) {
    if (!vis[*it]) {
      Dfs(*it);
    }
  }
  id.push_back(i);
}

void RDfs(int i) {
  vis[i] = 1;
  tp[i] = tot;
  for (vector<int>::iterator it = re[i].begin(); it != re[i].end(); ++it) {
    if (!vis[*it]) {
      RDfs(*it);
    }
  }
}

void AddEdge(int i, int j) {
  e[i].push_back(j);
  re[j].push_back(i);
}

bool Scc(int n) {
  id.clear();
  memset(vis, 0, sizeof(vis));
  for (int i = 0; i < n << 1; ++i) {
    if (!vis[i]) Dfs(i);
  }

  tot = 0;
  memset(vis, 0, sizeof(vis));
  for (vector<int>::iterator it = id.end() - 1; it >= id.begin(); --it) {
    if (!vis[*it]) {
      RDfs(*it);
      ++tot;
    }
  }

  bool ok = true;
  for (int i = 0; i < n; ++i) {
    if (tp[i] == tp[i + n]) {
      ok = false;
      break;
    }
  }
  return ok;
}

int key[1 << 10][2];
int lock[1 << 11][2];

void BuildGraph(int n, int m) {
  for (int i = (n << 2) - 1; i >= 0; --i) {
    e[i].clear();
    re[i].clear();
  }

  for (int i = 0; i < n; ++i) {
    AddEdge(key[i][0], key[i][1] + (n << 1));
    AddEdge(key[i][1], key[i][0] + (n << 1));
  }
  for (int i = 0; i < m; ++i) {
    AddEdge(lock[i][0] + (n << 1), lock[i][1]);
    AddEdge(lock[i][1] + (n << 1), lock[i][0]);
  }
}

int main() {
  int n, m;
  while (scanf("%d%d", &n, &m) != EOF && n) {
    for (int i = 0; i < n; ++i) {
      scanf("%d%d", &key[i][0], &key[i][1]);
    }
    for (int i = 0; i < m; ++i) {
      scanf("%d%d", &lock[i][0], &lock[i][1]);
    }
    int l, r, mid;
    l = 0, r = m + 1;
    while (l + 1 < r) {
      mid = (l + r) >> 1;
      BuildGraph(n, mid);
      if (Scc(n << 1)) {
        l = mid;
      } else {
        r = mid;
      }
    }
    printf("%d\n", l);
  }
  return 0;
}

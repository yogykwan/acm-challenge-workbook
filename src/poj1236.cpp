/*
 * POJ 1236: Network of Schools
 * 题意：给n个可连通的学校装软件，每个学校有自己的传输下继。求最少给多少个学校发送首批软件，经过若干次传输拷贝后所有学校最终都可以得到。另外还要求当随机某点已有软件时，还需要在传输下继名单增加多少个学校。
 * 类型：强连通分量
 * 算法：用2次DFS进行强连通分量分解，缩点得到有向无环图。第1次DFS时选取任意未访问结点，回溯时顺序标号。第2次DFS时先将图中边反向，每次从未遍历的标号最大的点出发。得到DAG后，入度为0的点数为答案1。由于将入度为0的点和出度为0的点连接可使得DAG变为SCC，所以将出度和入度为0的点数的更大者为答案2。
 */

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> e[110];
vector<int> re[110];
vector<int> id;

int tot;
int tp[110];

bool vis[110];
bool mat[110][110];

int in[110], out[110];


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

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    int j;
    while (scanf("%d", &j) != EOF && j) {
      e[i].push_back(j);
      re[j].push_back(i);
    }
  }

  memset(vis, 0, sizeof(vis));
  for (int i = 1; i <= n; ++i) {
    if (!vis[i]) Dfs(i);
  }

  memset(vis, 0, sizeof(vis));
  for (vector<int>::iterator it = id.end() - 1; it >= id.begin(); --it) {
    if (!vis[*it]) {
      RDfs(*it);
      ++tot;
    }
  }

  if (tot == 1) {
    printf("1\n0\n");  // 只有1个scc时特判
    return 0;
  }

  for (int i = 1; i <= n; ++i) {
    int t = tp[i];
    for (vector<int>::iterator it = e[i].begin(); it != e[i].end(); ++it) {
      int s = tp[*it];
      if (t != s && !mat[t][s]) {
        ++out[t];
        ++in[s];
        mat[t][s] = 1;
      }
    }
  }

  int ans1, ans2;
  ans1 = ans2 = 0;
  for (int i = 0; i < tot; ++i) {
    if (in[i] == 0) {
      ++ans1;
    }
    if (out[i] == 0) {
      ++ans2;
    }
  }

  printf("%d\n%d\n", ans1, max(ans1, ans2));

  return 0;
}

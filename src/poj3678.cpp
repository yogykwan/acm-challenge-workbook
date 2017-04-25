/*
 * POJ 3678: Katu Puzzle
 * 题意：给出由或、与、异或构成若干个两元子句，及它们期望的答案，求是否存在一组变量，使得每个子句都成立。
 * 类型：2-SAT
 * 算法：结点0～n-1表示x，n～2n-1表示!x。a&b=1等价!a=>a,!b=>b；a&b=0等价a=>!b,b=>!a；a|b=1等价!a=>b,!b=>a；a|b=0等价a=>!a,b=>!b；a^b=1等价a=>!b,!a=>b,b=>!a,!b=>a；a^b=0等价a=>b,!a=>!b,b=>a,!b=>!a。
 */

#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

vector<int> e[2010];
vector<int> re[2010];
vector<int> id;
bool vis[2010];

int tot;
int tp[2010];


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

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  while (m--) {
    int i, j, r;
    char op[5];
    scanf("%d%d%d%s", &i, &j, &r, op);
    if (op[0] == 'A') {
      if (r == 1) {
        AddEdge(i + n, i);
        AddEdge(j + n, j);
      } else {
        AddEdge(i, j + n);
        AddEdge(j, i + n);
      }
    } else if (op[0] == 'O') {
      if (r == 1) {
        AddEdge(i + n, j);
        AddEdge(j + n, i);
      } else {
        AddEdge(i, i + n);
        AddEdge(j, j + n);
      }
    } else {
      if (r == 1) {
        AddEdge(i, j + n);
        AddEdge(j, i + n);
        AddEdge(i + n, j);
        AddEdge(j + n, i);
      } else {
        AddEdge(i, j);
        AddEdge(j, i);
        AddEdge(i + n, j + n);
        AddEdge(j + n, i + n);
      }
    }
  }

  memset(vis, 0, sizeof(vis));
  for (int i = 0; i < n << 1; ++i) {
    if (!vis[i]) Dfs(i);
  }

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

  printf("%s\n", ok ? "YES" : "NO");

  return 0;
}

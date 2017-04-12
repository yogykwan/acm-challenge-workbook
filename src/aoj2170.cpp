/*
 * AOJ 2170: Marked Ancestor
 * 题意：给出一棵树，两种操作，将某点染色，或查询某个点的最近的已染色祖先。初始只有根染色了，对于每次询问输出最近染色祖先编号。
 * 类型：并查集+dfs+栈（／线段树+dfs）
 * 算法：所有的染色和询问请求放入栈内，先染好所有点，dfs得到每点的最近祖先，相同祖先相当于在并查集的同一集合里。再倒着把染色一一变暗，去染色时将该点与它父亲所在集合合并。（／线段树法：dfs得到树的中序遍历，每标记一个点，找到该子树对应的中序区间，线段树懒惰标记。）
 */

#include <cstdio>
#include <iostream>
#include <stack>
#include <cstring>
#include <vector>

using namespace std;

typedef pair<char, int> pci;

stack<pci> s;

int fa[100010];
int p[100010];
int vis[100010];

vector<int> e[100010];

int n;

void dfs(int i, int f = 1) {
  if(vis[i]) {
    f = i;
  }
  fa[i] = f;
  vector<int> &ei = e[i];
  for(vector<int>::iterator it = ei.begin(); it != ei.end(); ++it) {
    dfs(*it, f);
  }
}

int find(int x) {
  if(x == fa[x]) return x;
  return fa[x] = find(fa[x]);
}

int main() {
  int i, j, q;
  long long ans;
  char op[3];
  while(scanf("%d%d", &n, &q) != EOF && n > 0) {
    memset(vis, 0, sizeof(vis));
    for(i = 1; i <= n; ++i) {
      e[i].clear();
    }
    ans = 0;

    vis[1] = 1;
    for(i = 2; i <= n; ++i) {
      scanf("%d", &j);
      e[j].push_back(i);
      p[i] = j;
    }
    for(i = 0; i < q; ++i) {
      scanf("%s%d", op, &j);
      if(op[0] == 'M') {
        ++vis[j];
      }
      s.push(make_pair(op[0], j));
    }
    dfs(1);

    while(!s.empty()) {
      i = s.top().second;
      if(s.top().first == 'M') {
        if(--vis[i] == 0) {
          fa[i] = find(p[i]);
        }
      } else {
        ans += find(i);
      }
      s.pop();
    }

    printf("%lld\n", ans);

  }
  return 0;
}

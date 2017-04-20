/*
 * POJ 2046: Gap
 * 题意：给出4套1～7的卡牌，放在4行8列的格子里。现将1的卡牌顺序放在第一列，然后每次挑选一个空格，将它左侧邻居的同组里的后继（如果存在）放入空格。最后要求全部有序，问最少放置步数。
 * 类型：BFS+哈希
 * 算法：每个状态构成字符串，用哈希或unordered_set保证不重复。每个状态保存字符串、4个空格的位置、每个数字对应的位置、最短路径长。按路径长用最小堆优化维护。
 */

#include <cstdio>
#include <string>
#include <cstring>
#include <queue>
#include <vector>
#include <set>
//#include <unordered_set>

using namespace std;


//unordered_set<string> ss;

const int MOD = 1000007;

bool vis[MOD];

int Hash(const string &s) {
  unsigned int v = 0;
  for (int i = 0; i <= 31; i++) v = v * 7 + s[i];
  return v % MOD;
}

struct S {
  string s;
  int p[29];
  int b[4];
  int d;

  S() {}

  S(const string &t) : s(t), d(0) {
    int cnt = 0;
    for (int i = 0; i < 32; ++i) {
      if (s[i] == 30) {
        b[cnt++] = i;
      } else {
        p[s[i]] = i;
      }
    }
  }

  S(const S &st) : s(st.s), d(st.d) {
    memcpy(p, st.p, sizeof(p));
    memcpy(b, st.b, sizeof(b));
  }

  bool operator<(const S &st) const {
    return d > st.d;
  }
};

priority_queue<S> pq;

int main() {
//  freopen("/Users/yogy/acm-challenge-workbook/db.in", "r", stdin);
  string target(32, ' ');
  int cnt = 0;
  for (int i = 0; i < 4; ++i) {
    for (int j = 1; j <= 7; ++j) {
      target[cnt++] = char(7 * i + j);
    }
    target[cnt++] = char(30);
  }

  int T;
  scanf("%d", &T);
  while (T--) {
//    ss.clear();
    memset(vis, 0, sizeof(vis));
    while (!pq.empty()) pq.pop();
    cnt = 0;
    string s(32, ' ');
    for (int i = 0; i < 4; ++i) {
      s[cnt++] = char(i * 7 + 1);
      for (int j = 0; j < 7; ++j) {
        int x;
        scanf("%d", &x);
        if (x % 10 == 1) {
          s[cnt++] = char(30);
        } else {
          s[cnt++] = char((x / 10 - 1) * 7 + x % 10);
        }
      }
    }

    if (s == target) {
      printf("0\n");
      continue;
    }
    pq.push(S(s));
    int h = Hash(s);
    vis[h] = 1;
    int ans = -1;
    while (!pq.empty()) {
      S u(pq.top());
      pq.pop();
      for (int i = 0; i < 4; ++i) {
        int bp = u.b[i];
        char pre = u.s[bp - 1];
        if (pre == 30 || pre % 7 == 0) {
          continue;
        }
        int np = u.p[pre + 1];

        S v(u);
        v.s[bp] = char(pre + 1);
        v.s[np] = char(30);
        h = Hash(v.s);
        if (!vis[h]){
          vis[h] = 1;
//        if (ss.find(v.s) == ss.end()) {
//          ss.insert(v.s);
          ++v.d;
          if (v.s == target) {
            ans = v.d;
            goto L;
          }

          v.p[pre + 1] = bp;
          v.b[i] = np;
          pq.push(v);
        }
      }
    }
    L:
    printf("%d\n", ans);
  }
  return 0;
}

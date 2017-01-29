/*
 * POJ 3126: Prime Path
 * 题意：给出两个四位素数，每步可变化任意一位，要求每步变化后所得都是素数。求最少步数。
 * 类型：素数+最短路
 * 算法：素数筛法打表，以素数为点，两个只相差一位的素数间连线，Dijkstra求最短路。
 */


#include <cstdio>
#include <queue>
#include <vector>
#include <iostream>
#include <cstring>

using namespace std;

typedef long long LL;
typedef pair<int, int> pii;

const int MAXN = 10010;
int p[MAXN>>3];
bool np[MAXN];
int cntp;
int d[MAXN];

vector<int> e[MAXN];
priority_queue<pii, vector<pii>, greater<pii> > pq;


void SievePrime(int n) {
  LL t;
  for(int i = 2; i < n; ++i) {
    if(!np[i]) p[cntp++] = i;
    for(int j = 0; j < cntp && (t = 1ll * i * p[j]) < n; ++j) {
      np[t] = true;
      if(i % p[j] == 0) break;
    }
  }
}

void InitGraph() {
  for(int i = 0; i < cntp; ++i) {
    if(p[i] < 1000) continue;
    if(p[i] >= 10000) break;
    for(int j = i + 1; j < cntp; ++j) {
      int a = p[i], b = p[j];
      if(a/10==b/10 || a/100==b/100 && a%10==b%10 || a/1000==b/1000 && a%100==b%100 || a%1000==b%1000) {
        e[a].push_back(b);
        e[b].push_back(a);
      }
    }
  }
}

int Dijkstra(int s, int t) {
  while(!pq.empty()) pq.pop();
  memset(d, 0x3f, sizeof(d));
  d[s] = 0;
  pq.push(make_pair(d[s], s));
  while(!pq.empty()) {
    pii tmp = pq.top();
    pq.pop();
    int du = tmp.first, u = tmp.second;
    if(d[u] < du) continue;
    if(u == t) return du;
    for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it) {
      int v = *it;
      if(d[v] > du + 1) {
        d[v] = du + 1;
        pq.push(make_pair(d[v], v));
      }
    }
  }
  return -1;
}

int main() {
  SievePrime(10000);
  InitGraph();
  int T;
  scanf("%d", &T);
  while(T--) {
    int a, b;
    scanf("%d%d", &a, &b);
    int ans = Dijkstra(a, b);
    int v = b;
    if(ans == -1) printf("Impossible\n");
    else printf("%d\n", ans);
  }
  return 0;
}

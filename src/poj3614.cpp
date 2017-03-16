/*
 * POJ 3614: Sunscreen
 * 题意：每只奶牛有自己的有效防晒区间，给出多种不同数量的防晒霜，求最多可以让多少只奶牛成功防晒。
 * 类型：贪心+优先队列
 * 算法：将区间按左端点升序排序，将防晒霜按防晒指数升序排序。对于每种防晒霜，将区间左端点不超过它的牛加入最小堆，每次从堆头贪心。
 */


#include <cstdio>
#include <algorithm>
#include <queue>

using namespace std;

typedef pair<int, int> pii;
pii c[2510], l[2510];

priority_queue<int, vector<int>, greater<int> > pq;


int main() {
  int n, m, i, j;
  scanf("%d%d", &n, &m);
  for(i = 0; i < n; ++i) scanf("%d%d", &c[i].first, &c[i].second);
  for(i = 0; i < m; ++i) scanf("%d%d", &l[i].first, &l[i].second);
  sort(c, c + n);
  sort(l, l + m);
  j = 0;
  int ans = 0;
  for(i = 0; i < m; ++i) {
    while(j < n && c[j].first <= l[i].first) {
      pq.push(c[j].second);
      ++j;
    }
    while(!pq.empty() && l[i].second > 0) {
      int tmp = pq.top();
      pq.pop();
      if(tmp >= l[i].first) {
        ++ans;
        --l[i].second;
      }
    }
  }
  printf("%d\n", ans);
  return 0;
}


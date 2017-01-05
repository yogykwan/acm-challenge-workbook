/*
 * POJ 3190: Stall Reservations
 * 题意：n头奶牛有自己的产奶时间区间，现在要建一批牛栏，使得每头牛产奶时都独处在某个牛栏里。求最少牛栏数，并给出牛和牛栏的分配关系。
 * 类型：贪心
 * 算法：将区间按左端点排序，用最小堆维护每个牛栏内最右端点坐标。对于每头牛，若其左端点大于堆顶元素，则可以插入该元素对应的牛栏并更新堆，否则新建牛栏。
 */

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>

using namespace std;

struct Cow{
  int first, second;
  int id;
  bool operator< (const Cow &c) const{
    return first < c.first;
  }
}cows[50010];

int ans[50010];

priority_queue <pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;

int main() {
  int n, i, j, cnt;

  scanf("%d", &n);
  for(i = 0; i < n; ++i) {
    scanf("%d%d", &cows[i].first, &cows[i].second);
    cows[i].id = i;
  }

  sort(cows, cows + n);

  cnt = 0;

  for(i = 0; i < n; ++i) {
    if(pq.empty() || cows[i].first <= pq.top().first) {
      ans[cows[i].id] = ++cnt;
      pq.push(make_pair(cows[i].second, cnt));
    } else {
      ans[cows[i].id] = pq.top().second;
      pq.pop();
      pq.push(make_pair(cows[i].second, ans[cows[i].id]));
    }
  }

  printf("%d\n", cnt);
  for(i = 0; i < n; ++i) {
    printf("%d\n", ans[i]);
  }

  return 0;
}
/*
 * POJ 2010: Moo University - Financial Aid
 * 题意：从申请者里录取规定的n个，n为奇数，要求他们需要的开销和不超过预算，求被录取者的得分最大可能的中位数。
 * 类型：优先队列（／二分搜索）
 * 算法：按分数升序排序，把每个点作中位数看待，用最大堆得到每个点左侧及右侧，n/2个最小的开销的和。找到左右和相加不超过预算的最大中位数。
 */

#include <iostream>
#include <cstdio>
#include <queue>
#include <algorithm>

using namespace std;

typedef pair<int, int> pii;

pii c[100010];
long long l[100010], r[100010];
priority_queue<int> pq;

int main() {
//  freopen("/Users/yogy/acm-challenge-workbook/db.in", "r", stdin);
  int m, n, i, j;
  long long tmp;
  long long t;
  scanf("%d%d%lld\n", &m, &n, &t);
  for(i = 0; i < n; ++i) {
    scanf("%d%d", &c[i].first, &c[i].second);
  }
  sort(c, c + n);
  if(m == 1) {
    for(i = n - 1; i >= 0; --i) {
      if(c[i].second <= t) {
        printf("%d\n", c[i].first);
        break;
      }
    }
    printf("-1\n");
    return 0;
  }

  tmp = 0;
  for(i = 0; i < m/2; ++i) {
    pq.push(c[i].second);
    tmp += c[i].second;
  }
  l[i] = tmp;
  for(++i; i <= n - m/2 - 1; ++i) {
    if(pq.top() <= c[i - 1].second) {
      l[i] = l[i - 1];
    } else {
      l[i] = l[i - 1] - pq.top() + c[i - 1].second;
      pq.pop();
      pq.push(c[i - 1].second);
    }
  }

  while(!pq.empty()) {
    pq.pop();
  }
  tmp = 0;
  for(i = n - 1; i > n - m/2 -1; --i) {
    pq.push(c[i].second);
    tmp += c[i].second;
  }
  r[i] = tmp;
  for(--i; i >= m/2; --i) {
    if(pq.top() <= c[i + 1].second) {
      r[i] = r[i + 1];
    } else {
      r[i] = r[i + 1] - pq.top() + c[i + 1].second;
      pq.pop();
      pq.push(c[i + 1].second);
    }
  }

  int ans = -1;
  for(i = n - m/2 - 1; i >= m/2; --i) {
    if(l[i] + r[i] + c[i].second <= t) {
      ans = c[i].first;
      break;
    }
  }
  printf("%d\n", ans);
  return 0;
}


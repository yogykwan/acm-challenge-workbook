/*
 * POJ 2823: Sliding Window
 * 题意：给出一个数列和固定大小的滑动窗口，求窗口移动过程中每次窗口内的最小和最大值。
 * 类型：双端队列
 * 算法：若要求窗口内最小值，则每个点左侧大于等于它的点可去除，所以保留窗口内的递增序列；同理，求最大值则保留窗口内的递减序列。（c++ ac, g++ tle）
 */

#include <cstdio>
#include <deque>

using namespace std;

int a[1000010];
int mi[1000010], ma[1000010];
deque<int> q, q2;

int main () {
//  freopen("/Users/yogy/acm-challenge-workbook/db.in", "r", stdin);
  int n, k;
  scanf("%d%d", &n, &k);
  if (k > n) k = n;
  for (int i = 0; i < n; ++i) scanf("%d", &a[i]);

  for (int i = 0; i < n; ++i) {
    if (!q.empty() && q.front() == i - k) q.pop_front();
    if (!q2.empty() && q2.front() == i - k) q2.pop_front();

    while (!q.empty() && a[q.back()] >= a[i]) q.pop_back();
    q.push_back(i);

    while (!q2.empty() && a[q2.back()] <= a[i]) q2.pop_back();
    q2.push_back(i);

    if (i >= k - 1) {
      mi[i] = a[q.front()];
      ma[i] = a[q2.front()];
    }
  }

  for (int i = k - 1; i < n - 1; ++i) printf("%d ", mi[i]);
  printf("%d\n", mi[n - 1]);

  for (int i = k - 1; i < n - 1; ++i) printf("%d ", ma[i]);
  printf("%d\n", ma[n - 1]);

  return 0;
}


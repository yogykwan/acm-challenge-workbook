/*
 * POJ 3250: Bad Hair Day
 * 题意：一排奶牛面向东站着，给出身高，每头牛可以看到它东边的牛的头顶直到被身高不低于它的牛挡住。求所有牛可以看到的牛头顶的数量。
 * 类型：栈
 * 算法：将身高从左向右压入栈，当栈顶小于等于当前身高时，栈顶的牛被当前待压入栈的牛挡住。
 */

#include <cstdio>
#include <stack>

using namespace std;

int h[80010];
stack<int> s;

int main() {
  int n;
  long long ans = 0;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &h[i]);
  }
  h[n] = 2000000000;
  for (int i = 0; i <= n; ++i) {
    while (!s.empty()) {
      if (h[s.top()] <= h[i]) {
        ans += i - s.top() - 1;
        s.pop();
      } else break;
    }
    s.push(i);
  }
  printf("%lld\n", ans);

  return 0;
}
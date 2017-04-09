/*
 * POJ 2082: Terrible Sets
 * 题意：一排相邻的矩形，给出各自的高度和宽度。求一个面积最大的矩形，被之前的矩形完全包含。
 * 类型：栈
 * 算法：用栈得到某个矩形靠它最近的比它矮的左边和右边，得到它对应的宽度，相乘为待选解。
 */

#include <cstdio>
#include <stack>

using namespace std;

int h[50010], w[50010];
int s[50010];
int l[50010], r[50010];

stack<int> st;

int main() {
  int n;
  while (scanf("%d", &n) != EOF && n != -1) {
    int ans = 0;
    s[0] = 0;
    for (int i = 1; i <= n; ++i) {
      scanf("%d%d", &w[i], &h[i]);
      s[i] = s[i - 1] + w[i];
    }
    h[0] = h[n + 1] = -1;

    while (!st.empty()) st.pop();
    for (int i = 1; i <= n + 1; ++i) {
      while (!st.empty()) {
        if (h[st.top()] > h[i]) {
          r[st.top()] = i;
          st.pop();
        } else break;
      }
      st.push(i);
    }

    while (!st.empty()) st.pop();
    for (int i = n; i >= 0; --i) {
      while (!st.empty()) {
        if (h[st.top()] > h[i]) {
          l[st.top()] = i;
          st.pop();
        } else break;
      }
      st.push(i);
    }

    for (int i = 1; i <= n; ++i) {
      ans = max(ans, h[i] * (s[r[i] - 1] - s[l[i]]));
    }

    printf("%d\n", ans);
  }
  return 0;
}
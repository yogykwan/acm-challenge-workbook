/*
 * POJ 1180: Batch Scheduling
 * 题意：多个进程有各自的运行时间和等待代价系数，将其有序切分到多个处理器里，每个处理器依次处理，启动时间为s。一个进程的代价等于它的系数乘以它所在处理器完成其上所有任务闭的时间点。求最小代价。
 * 类型：斜率DP+双端队列
 * 算法：di表示从i到最后的最小花费，预处理从i到最后的累加时间和累加代价系数为ti和ci。di=min{(s+ti-tj)*ci+dj,i<j<=n}，常数项提出变形di=(s+ti)*ci+min{-tj*ci+dj}。倒着遍历，ci增大，斜率-tj减小，所以可以用双端队列保存可能存在最小解的直线。
 */

#include <cstdio>

using namespace std;

int t[10010], c[10010];
int d[10010];

struct Line {
  int a, b;
  Line() {}
  Line(int aa, int bb) : a(aa), b(bb) {}
};

bool useless(const Line &l1, const Line &l2, const Line &l3) {
  return (l2.a - l1.a) * (l3.b - l2.b) >= (l3.a - l2.a) * (l2.b - l1.b);
}

Line q[10010]; // use array instead of deque, because we need 2 elements either from head or tail at the same time

int foo(const Line& l, int x) {
  return l.a * x + l.b;
}


int main() {
//  freopen("/Users/yogy/acm-challenge-workbook/db.in", "r", stdin);
  int n, s;
  int begin, end;
  begin = end = 0;
  scanf("%d%d", &n, &s);
  t[n] = c[n] = 0;
  for (int i = 0; i < n; ++i) {
    scanf("%d%d", &t[i], &c[i]);
  }
  for (int i = n - 1; i >= 0; --i) {
    t[i] += t[i + 1];
    c[i] += c[i + 1];
  }
  q[0] = Line(0, 0);
  ++end;
  for (int i = n - 1; i >= 0; --i) {
    while (end - begin > 1 && foo(q[begin], c[i]) >= foo(q[begin + 1], c[i])) {
      ++begin;
    }
    d[i] = (s + t[i]) * c[i] + foo(q[begin], c[i]);
//    printf("%d : %d %d %d\n", i, d[i], (s + t[i]) * c[i], foo(q[begin], c[i]));
    while (end - begin > 1 && useless(q[end - 2], q[end - 1], Line(-t[i], d[i]))) {
      --end;
    }
    q[end++] = Line(-t[i], d[i]);
  }
  printf("%d\n", d[0]);
  return 0;
}


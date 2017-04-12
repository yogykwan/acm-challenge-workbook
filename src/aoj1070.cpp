/*
 * AOJ 1070: FIMO sequence
 * 题意：初始为空的序列有10种操作：末尾插入从未出现过的数；中位数删除；求前／后半段最大／小；假想重复删除中位数至空，每次删除前输出前／后半段最大／小的数，求其中第i大的。
 * 类型：双端队列
 * 算法：维护6个双端队列，前后半段的数列、单调升、单调降。对于每个给出的操作，分配到队列上就是头尾插入、头尾删除、随机读取。
 */

#include <cstdio>

const int MAXN = 200010;

int la[MAXN], ls[MAXN], lb[MAXN], ra[MAXN], rs[MAXN], rb[MAXN];
int la1, la2, ls1, ls2, lb1, lb2, ra1, ra2, rs1, rs2, rb1, rb2, m;

void left_push_back(int x) {
  la[la2++] = x;
  if (ls2 == ls1 || ls[ls2 - 1] > x) {
    ls[ls2++] = x;
  }
  if (lb2 == lb1 || lb[lb2 - 1] < x) {
    lb[lb2++] = x;
  }
}

void right_push_back(int x) {
  ra[ra2++] = x;
  while (rs2 > rs1 && rs[rs2 - 1] > x) {
    --rs2;
  }
  rs[rs2++] = x;
  while (rb2 > rb1 && rb[rb2 - 1] < x) {
    --rb2;
  }
  rb[rb2++] = x;
}

int right_pop_front() {
  if (ra[ra1] == rs[rs1]) ++rs1;
  if (ra[ra1] == rb[rb1]) ++rb1;
  ++ra1;
  return ra[ra1 - 1];
}

int left_pop_back() {
  if (la[la2 - 1] == ls[ls2 - 1]) --ls2;
  if (la[la2 - 1] == lb[lb2 - 1]) --lb2;
  --la2;
  return la[la2];
}

void f0_add() {
  int x;
  scanf("%d", &x);
  if (m == 0) {
    left_push_back(x);
  } else {
    right_push_back(x);
    if (!(m & 1)) {
      int y = right_pop_front();
      left_push_back(y);
    }
  }
  ++m;
}

void f1_del() {
  int x = left_pop_back();
  printf("%d\n", x);
  if (!(m & 1)) {
    int y = right_pop_front();
    left_push_back(y);
  }
  --m;
}

void f2_ls() {
  int x = ls[ls2 - 1];
  printf("%d\n", x);
}

void f3_rs() {
  int x = rs[rs1];
  printf("%d\n", x);
}

void f4_ls_() {
  int i, x;
  scanf("%d", &i);
  x = ls[ls2 - i];
  printf("%d\n", x);
}

void f5_rs_() {
  int i, x;
  scanf("%d", &i);
  x = rs[rs1 + i - 1];
  printf("%d\n", x);
}

void f6_lb() {
  int x = lb[lb2 - 1];
  printf("%d\n", x);
}

void f7_rb() {
  int x = rb[rb1];
  printf("%d\n", x);
}

void f8_lb_() {
  int i, x;
  scanf("%d", &i);
  x = lb[lb2 - i];
  printf("%d\n", x);
}

void f9_rb_() {
  int i, x;
  scanf("%d", &i);
  x = rb[rb1 + i - 1];
  printf("%d\n", x);
}

int main() {
//  freopen("/Users/yogy/acm-challenge-workbook/db.in", "r", stdin);
  int n;
  while (scanf("%d", &n) != EOF && n) {
    m = la1 = la2 = ls1 = ls2 = lb1 = lb2 = ra1 = ra2 = rs1 = rs2 = rb1 = rb2 = 0;
    while (n--) {
      int t;
      scanf("%d", &t);
      switch (t) {
        case 0:
          f0_add();
          break;
        case 1:
          f1_del();
          break;
        case 2:
          f2_ls();
          break;
        case 3:
          f3_rs();
          break;
        case 4:
          f4_ls_();
          break;
        case 5:
          f5_rs_();
          break;
        case 6:
          f6_lb();
          break;
        case 7:
          f7_rb();
          break;
        case 8:
          f8_lb_();
          break;
        case 9:
          f9_rb_();
          break;
      }
    }
    printf("end\n");
  }
  return 0;
}

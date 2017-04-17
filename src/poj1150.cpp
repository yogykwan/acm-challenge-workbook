/*
 * POJ 1150: The Last Non-zero Digit
 * 题意：求排列数A(n,m)最后的非0位是什么数字。
 * 类型：数论
 * 算法：找到(n-m,n]的乘积里有多少2和5次幂，定义fn为n去除以其中所有的2和5因子。求f1*f2*...*fn中个位数各有多少个，其中偶数又可以通过除以2归结到奇数有多少个，所以关键在于求出3、7、9结尾的有多少个。而3、7、9结尾的奇数fn又可以通过除5归结到下一个阶段。
 */


#include <cstdio>

int CountFactor(int n, int a) {
  int ans = 0;
  while (n) {
    ans += n / a;
    n /= a;
  }
  return ans;
}

int CountLastOdd(int n, int a) {
  if (!n) return 0;
  return n / 10 + (n % 10 >= a) + CountLastOdd(n / 5, a);
}

int CountLast(int n, int a) {
  if (!n) return 0;
  return CountLast(n / 2, a) + CountLastOdd(n, a);
}

int PowLast(int a, int b) {
  b %= 4; // 3，7，9，2的幂循环周期都为4或4的因子
  if (!b) b = 4; // 2的4次幂不等于0次幂
  int ans = 1;
  while (b--) ans *= a;
  return ans % 10;
}

int main() {
  int n, m;

  while (scanf("%d%d", &n, &m) != EOF) {
    int b = n - m;
    int two = CountFactor(n, 2) - CountFactor(b, 2);
    int five = CountFactor(n, 5) - CountFactor(b, 5);

    if (five > two) {
      printf("5\n");
      continue;
    }

    int three = CountLast(n, 3) - CountLast(b, 3);
    int seven = CountLast(n, 7) - CountLast(b, 7);
    int nine = CountLast(n, 9) - CountLast(b, 9);

    int ans = 1;
    if (two > five) ans *= PowLast(2, two - five);
    ans *= PowLast(3, three);
    ans *= PowLast(7, seven);
    ans *= PowLast(9, nine);

    printf("%d\n", ans % 10);
  }
  return 0;
}

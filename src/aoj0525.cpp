/*
 * AOJ 0525: Osenbei
 * 题意：R行C列的矩阵，点为0或1。每次可对整行或整列的点进行翻转，求最多可能出现多少个0。
 * 类型：穷竭搜索＋位运算
 * 算法：最多10行，可对行的翻转情况用全排列遍历，同时修改每列1的个数。列翻转可等价于将0或1的个数用于求和。
 */


#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int m, n;
int mat[11][10001];
int one[10001], _one[10001];
int ans;

void solve() {
  ans = 0;
  memset(one, 0, sizeof(one));
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      cin >> mat[i][j];
      one[j] += mat[i][j];
    }
  }
  for (int no = (1 << m) - 1; no >= 0; --no) {
    int _no = no;
    for (int i = 0; i < n; ++i) {
      _one[i] = one[i];
    }
    for (int i = 0; i < m; ++i) {
      if (_no & 1) {
        for (int j = 0; j < n; ++j) {
          _one[j] += mat[i][j] ? -1 : 1;
        }
      }
      _no >>= 1;
    }
    int tmp = 0;
    for (int i = 0; i < n; ++i) {
      tmp += max(_one[i], m - _one[i]);
    }
    ans = max(ans, tmp);
  }

}

int main() {
  while (cin >> m >> n && m > 0 && n > 0) {
    solve();
    cout << ans << endl;
  }
  return 0;
}

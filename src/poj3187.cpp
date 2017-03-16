/*
 * POJ 3187: Backward Digit Sums
 * 题意：给出1～n的排列后，将相邻数相加写到下一行，重复以上动作，直到只剩1个数，最终得到一个倒三角。现在给出n值和倒三角的最底行的数，求满足的1～n的最小字典序排列。
 * 类型：穷竭搜索＋全排列
 * 算法：将1～n按字典序全排列，计算每次的倒三角最底行数，直到找到满足条件的解。
 */


#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

int n, m;
int a[10], b[10];

void solve() {
    for(int i = 1; i <= n; ++i) {
        a[i - 1] = i;
    }
    do {
        for(int i = 0; i < n; ++ i) {
            b[i] = a[i];
        }
        for(int i = n - 1; i >= 1; --i) {
            for(int j = 0; j < i; ++j) {
                b[j] = b[j] + b[j + 1];
            }
        }
        if(b[0] == m) {
            return;
        }
    } while(next_permutation(a, a + n));
}

int main() {
    cin >> n >> m;
    solve();
    for(int i = 0; i < n - 1; ++i){
        cout << a[i] << " ";
    }
    cout << a[n - 1] << endl;
    return 0;
}


/*
 * POJ 1979: Red and Black
 * 题意：m＊n矩阵中，给出初始位置和每个点是否允许踩的状态，向上下左右4个方向移动，求多少点能到达。
 * 类型：DFS＋记忆化搜索（／BFS／并查集）
 * 算法：从某点出发，若该点可踩且未标记，结果＋1，将该点标记（记忆化），并向其4个方向的点继续递归搜索。
 */

#include <cstdio>
#include <iostream>

using namespace std;

char mat[100][100];
int dx[4] = {-1, 0, 0, 1};
int dy[4] = {0, 1, -1, 0};
int m, n, ans;

void dfs(int x,int y) {
	if(mat[x][y] != '.') return;
	++ans;
	mat[x][y] = 'x';
	int xx, yy;
	for(int i = 0; i < 4; ++i) {
		xx = x + dx[i];
		yy = y + dy[i];
		if(xx >= 0 && xx < m && yy >= 0 && yy < n){
			dfs(xx, yy);
		}
	}
}

void solve() {
	ans = 0;
	for(int i = 0; i < m; ++i) {
		cin >> mat[i];
	}
	for(int i = 0; i < m; ++i) {
		for(int j = 0; j< n; ++j) {
			if(mat[i][j] == '@') {
				mat[i][j] = '.';
				dfs(i, j);
				return;
			}
		}
	}
}

int main() {
	while(cin >> n >> m && m > 0 && n > 0) {
		solve();
		cout << ans << endl;
	}
	return 0;
}

/*
 * POJ 3669: Meteor Shower
 * 题意：给出M次流星的落点和时间，流星会摧毁该点和上下左右四点，矩阵内每点只在摧毁前才可到达。从左上角出发，求能够到达永不会被摧毁的点最短时间。
 * 类型：BFS（／DFS）
 * 算法：预处理出每点最早被摧毁的时间，使用边界和摧毁时间作入队限制，直到队列空或到达不会被摧毁的点。注意初始状态可能为被摧毁或永不摧毁。
 */

#include <cstdio>
#include <iostream>
#include <queue>

using namespace std;

typedef pair<int, int> pii;

const int INF = 10000;

int d[402][402];
int ms[402][402];
int dx[5] = {-1, 0, 0, 1, 0};
int dy[5] = {0, 1, -1, 0, 0};

int bfs() {
    if(ms[0][0] == INF) return 0;
	memset(d, -1, sizeof(d));
	queue <pii> q;
	if(ms[0][0] > 0){
		q.push(make_pair(0, 0));
		d[0][0] = 0;
	}
	while(!q.empty()) {
		pii p = q.front();
		q.pop();
		int xx, yy, x, y;
		x = p.first;
		y = p.second;
		for(int i = 0; i < 4; ++i) {
			xx = x + dx[i];
			yy = y + dy[i];
			if(xx >= 0 && xx <= 400 && yy >= 0 && y<= 400 && d[xx][yy] == -1 && ms[xx][yy] > d[x][y] + 1) {
				d[xx][yy] = d[x][y] + 1;
				if(ms[xx][yy] == INF) {
					return d[xx][yy];
				}
				q.push(make_pair(xx, yy));
			}
		}
	}
	return -1;
}

int solve() {
	for(int i = 0; i <= 400; ++i) {
		for(int j = 0; j <= 400; ++j){
			ms[i][j] = INF;
		}
	}
	int m;
	cin >> m;
	while(m--) {
		int x, y, t, xx ,yy;
		cin >> x >> y >> t;
		for(int i = 0 ; i < 5; ++i) {
			xx = x + dx[i];
			yy = y + dy[i];
            if(xx >= 0 && xx <= 400 && yy >= 0 && y<= 400) {
                ms[xx][yy] = min(ms[xx][yy], t);
            }
		}
	}
	return bfs();
}

int main() {
	cout << solve() << endl;
	return 0;
}

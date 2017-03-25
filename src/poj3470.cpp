/*
 * POJ 3470: Walls
 * 题意：二维平面中有n个墙，共m只小鸟，可以向上下左右飞，每只鸟选择的方向都会使它最早撞墙。求最后每个墙被多少鸟撞了。
 * 类型：线段树+扫描线+离散化
 * 算法：离散化一次处理所有数。因为墙都有宽度1，所以看作矩形。若鸟向左飞，将鸟和矩形左边都按x增序快排。扫描y线从左向右，将矩形y范围内的线段树更新为矩形id。其他方向同理。最后按离散前距离差为每个鸟选择合适的方向，并更新对应矩形计数器。
 */

#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>

using namespace std;

const int MAXN = 50010;
const int MAXM = 1 << 19;

int nums[MAXN * 6];
int m, n, t;
int ans[MAXN];

struct Wall {
  int x[4];
} walls[MAXN];

struct Bird {
  int x[2];
  int hit[4];
} birds[MAXN];

bool cmpx(const Bird &a, const Bird &b) {
  return a.x[0] < b.x[0];
}

bool cmpy(const Bird &a, const Bird &b) {
  return a.x[1] < b.x[1];
}

ostream& operator<<(ostream &os, const Bird &s) {
  os << s.x[0] << ", " << s.x[1] << endl;
  return os;
}

struct Seg {
  int a, b, c, id;

  bool operator<(const Seg &s) const {
    return c < s.c;
  }
} segs[MAXN];

ostream& operator<<(ostream &os, const Seg &s) {
  os << s.a << "-" << s.b << " " << s.c << " : " << s.id << endl;
  return os;
}

#define lchild rt << 1, l, m
#define rchild rt << 1 | 1, m + 1, r

int last[MAXM];

void update(int rt, int l, int r, int ql, int qr, int c) {
  if (ql <= l && r <= qr) {
    last[rt] = c;
    return;
  }
  int m = (l + r) >> 1;
  if (last[rt] != -1) {
    last[rt << 1] = last[rt << 1 | 1] = last[rt];
    last[rt] = -1;
  }
  if (ql <= m) {
    update(lchild, ql, qr, c);
  }
  if (qr > m) {
    update(rchild, ql, qr, c);
  }
}

int query(int rt, int l, int r, int ql) {
  if (l == r || last[rt] != -1) {
    return last[rt];
  }
  int m = (l + r) >> 1;
  return ql <= m ? query(lchild, ql) : query(rchild, ql);
}

void SWAP(int &a, int &b) {
  int t = a;
  a = b;
  b = t;
}

int ABS(int x) {
  if (x >= 0) return x;
  return -x;
}

int main() {
//  freopen("/Users/yogy/acm-challenge-workbook/db.in", "r", stdin);
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < 4; ++j) {
      scanf("%d", &nums[t]);
      walls[i].x[j] = nums[t];
      ++t;
    }
    if (walls[i].x[0] > walls[i].x[2]) SWAP(walls[i].x[0], walls[i].x[2]);
    if (walls[i].x[1] > walls[i].x[3]) SWAP(walls[i].x[1], walls[i].x[3]);
  }
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < 2; ++j) {
      scanf("%d", &nums[t]);
      birds[i].x[j] = nums[t];
      ++t;
    }
  }

  sort(nums, nums + t);
  t = int(unique(nums, nums + t) - nums);

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < 4; ++j) {
      walls[i].x[j] = int(lower_bound(nums, nums + t, walls[i].x[j]) - nums);
    }
  }
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < 2; ++j) {
      birds[i].x[j] = int(lower_bound(nums, nums + t, birds[i].x[j]) - nums);
    }
  }

  // x
  for (int i = 0; i < n; ++i) {
    segs[i].a = walls[i].x[1];
    segs[i].b = walls[i].x[3];
    segs[i].c = walls[i].x[0];
    segs[i].id = i;
//    cout << segs[i];
  }
  sort(segs, segs + n);
  sort(birds, birds + m, cmpx);

  // left
  memset(last, -1, sizeof(last));
  int j = 0;
  for (int i = 0; i < m; ++i) {
//    cout << birds[i];
    for (; j < n && segs[j].c < birds[i].x[0]; ++j) {
      update(1, 0, t - 1, segs[j].a, segs[j].b, segs[j].id);
    }
    birds[i].hit[2] = query(1, 0, t - 1, birds[i].x[1]);
  }

  // right
  memset(last, -1, sizeof(last));
  j = n - 1;
  for (int i = m - 1; i >= 0; --i) {
    for (; j >= 0 && segs[j].c > birds[i].x[0]; --j) {
      update(1, 0, t - 1, segs[j].a, segs[j].b, segs[j].id);
    }
    birds[i].hit[0] = query(1, 0, t - 1, birds[i].x[1]);
  }

  // y
  for (int i = 0; i < n; ++i) {
    segs[i].a = walls[i].x[0];
    segs[i].b = walls[i].x[2];
    segs[i].c = walls[i].x[1];
    segs[i].id = i;
  }
  sort(segs, segs + n);
  sort(birds, birds + m, cmpy);

  // down
  memset(last, -1, sizeof(last));
  j = 0;
  for (int i = 0; i < m; ++i) {
    for (; j < n && segs[j].c < birds[i].x[1]; ++j) {
      update(1, 0, t - 1, segs[j].a, segs[j].b, segs[j].id);
    }
    birds[i].hit[3] = query(1, 0, t - 1, birds[i].x[0]);
  }

  // up
  memset(last, -1, sizeof(last));
  j = n - 1;
  for (int i = m - 1; i >= 0; --i) {
    for (; j >= 0 && segs[j].c > birds[i].x[1]; --j) {
      update(1, 0, t - 1, segs[j].a, segs[j].b, segs[j].id);
    }
    birds[i].hit[1] = query(1, 0, t - 1, birds[i].x[0]);
  }

  for (int i = 0; i < m; ++i) {
    int id = -1;
    int dis = -1;
    for (int j = 0; j < 4; ++j) {
      int tid = birds[i].hit[j];
      if (tid != -1) {
        int tmp = ABS(nums[birds[i].x[j & 1]] - nums[walls[tid].x[j]]);
        if (dis == -1 || tmp < dis) {
          id = tid;
          dis = tmp;
        }
      }
    }
    ++ans[id];
  }
  for (int i = 0; i < n; ++i) {
    printf("%d\n", ans[i]);
  }

  return 0;
}

# 1 前言

项目为[《挑战程序设计竞赛（第2版）》](http://www.ituring.com.cn/book/1044)习题册，含详细题解。

* 题量约200道，配合书籍或笔记，系统学习算法。
* 难度总体高于Leetcode，部分接近ACM地区赛。
* 代码均AC，题解个人向；Bug或优化请建Issue或Pull Request。
* _持续更新，预计2017年3月完成。_

# 1.1 题库来源
- Google Code Jam（[GCJ](https://code.google.com/codejam)）
- Peking University Online Judge（[POJ](http://poj.org/)）
- Aizu Online Judge（[AOJ](http://judge.u-aizu.ac.jp/onlinejudge/index.jsp?lang=en)）
- CodeForces（[CF](http://codeforces.com/)）
- LeetCode（[LC](https://leetcode.com/)）

# 1.2 算法笔记
- [初级篇](http://jennica.space/2016/10/14/acm-challenge-easy/)
- [中级篇](http://jennica.space/2016/11/16/acm-challenge-medium/)
- [高级篇](http://jennica.space/2016/11/30/acm-challenge-hard/)

# 1.3 题库目录

* 初级： 
[穷竭搜索](#21-穷竭搜索)、
[贪心法](#22-贪心法)、
[动态规划](#23-动态规划)、
[数据结构](#24-数据结构)、
[图论](#25-图论)、
[数论](#26-数论)

* 中级：
[二分搜索](二分搜索)、
[常用技巧](常用技巧)、
[数据结构（二）](数据结构（二）)、
[动态规划（二）](动态规划（二）)、
[网络流](网络流)、
[计算几何](计算几何)

* 高级：
[数论（二）](数论（二）)、
[博弈论](博弈论)、
[图论（二）](图论（二）)、
[常用技巧（二）](常用技巧（二）)、
[智慧搜索](智慧搜索)、
[分治](分治)、
[字符串](字符串)



# 2 初级算法

# 2.1 穷竭搜索
- 深度优先搜索
  - [x] [POJ 1979: Red and Black](http://poj.org/problem?id=1979)
  - [x] [AOJ 0118: Property Distribution](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0118)
  - [x] [AOJ 0033: Ball](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0033)
  - [x] [POJ 3009: Curling 2.0](http://poj.org/problem?id=3009)

- 宽度优先搜索
  - [x] [AOJ 0558: Cheese](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0558)
  - [x] [POJ 3669: Meteor Shower](http://poj.org/problem?id=3669)
  - [x] [AOJ 0121: Seven Puzzle](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0121)

- 穷竭搜索
  - [x] [POJ 2718: Smallest Difference](http://poj.org/problem?id=2718)
  - [x] [POJ 3187: Backward Digit Sums](http://poj.org/problem?id=3187)
  - [x] [POJ 3050: Hopscotch](http://poj.org/problem?id=3050)
  - [x] [AOJ 0525: Osenbei](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0525)

# 2.2 贪心法
- 区间贪心
  - [x] [POJ 2376: Cleaning Shifts](http://poj.org/problem?id=2376)
  - [x] [POJ 1328: Radar Installation](http://poj.org/problem?id=1328)
  - [x] [POJ 3190: Stall Reservations](http://poj.org/problem?id=3190)
  
- 其他贪心
  - [x] [POJ 2393: Yogurt factory](http://poj.org/problem?id=2393)
  - [x] [POJ 1017: Packets](http://poj.org/problem?id=1017)
  - [x] [POJ 3040; Allowance](http://poj.org/problem?id=3040)
  - [x] [POJ 1862: Stripies](http://poj.org/problem?id=1862)
  - [x] [POJ 3262: Protecting the Flowers](http://poj.org/problem?id=3262)
  
# 2.3 动态规划
- 基础DP
  - [x] [POJ 3176: Cow Bowling](http://poj.org/problem?id=3176)
  - [x] [POJ 2229: Sumsets](http://poj.org/problem?id=2229)
  - [x] [POJ 2385: Apple Catching](http://poj.org/problem?id=2385)
  - [x] [POJ 3616: Milking Time](http://poj.org/problem?id=3616)
  - [x] [POJ 3280: Cheapest Palindrome](http://poj.org/problem?id=3280)

- 优化递推式
  - [x] [POJ 1742: Coins](http://poj.org/problem?id=1742)
  - [x] [POJ 3046: Ant Counting](http://poj.org/problem?id=3046)
  - [x] [POJ 3181: Dollar Dayz](http://poj.org/problem?id=3181)
  
- 进阶DP
  - [x] [POJ 1065: Wooden Sticks](http://poj.org/problem?id=1065)
  - [x] [POJ 1631: Bridging signals](http://poj.org/problem?id=1631)
  - [x] [POJ 3666: Making the Grade](http://poj.org/problem?id=3666)
  - [x] [POJ 2392: Space Elevator](http://poj.org/problem?id=2392)
  - [x] [POJ 2184: Cow Exhibition](http://poj.org/problem?id=2184)
  
# 2.4 数据结构
- 优先队列
  - [ ] [POJ 3614:](http://poj.org/problem?id=3014)
  - [ ] [POJ 2010:](http://poj.org/problem?id=2010)
  
- 并查集
  - [ ] [POJ 2236:](http://poj.org/problem?id=2236)
  - [ ] [POJ 1703:](http://poj.org/problem?id=1703)
  - [ ] [AOJ 3614:](http://poj.org/problem?id=2170)


# 1 前言

项目为[《挑战程序设计竞赛（第2版）》](http://www.ituring.com.cn/book/1044)习题册攻略，已完结。可配合书籍或笔记，系统学习算法。

* 题量：约200道，代码注释内含详解。
* 难度：总体高于Leetcode，部分接近ACM。
* 题解：代码均AC，题解个人向；Bug或优化请建Issue或Pull Request。

# 1.1 题库来源
- Google Code Jam（[GCJ](https://code.google.com/codejam)）
- Peking University Online Judge（[POJ](http://poj.org/)）
- Aizu Online Judge（[AOJ](http://judge.u-aizu.ac.jp/onlinejudge/index.jsp?lang=en)）
- UVa Online Judge（[UVa](https://uva.onlinejudge.org/)）
- CodeForces（[CF](http://codeforces.com/)）

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
[二分搜索](#31-二分搜索)、
[常用技巧](#32-常用技巧)、
[数据结构（二）](#33-数据结构二)、
[动态规划（二）](#34-动态规划二)、
[网络流](#35-网络流)、
[计算几何](#36-计算几何)

* 高级：
[数论（二）](#41-数论二)、
[博弈论](#42-博弈论)、
[图论（二）](#43-图论二)、
[常用技巧（二）](#44-常用技巧二)、
[智慧搜索](#45-智慧搜索)、
[分治](#46-分治)、
[字符串](#47-字符串)

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
  - [x] [POJ 3614: Sunscreen](http://poj.org/problem?id=3614)
  - [x] [POJ 2010: Moo University - Financial Aid](http://poj.org/problem?id=2010)
  
- 并查集
  - [x] [POJ 2236: Wireless Network](http://poj.org/problem?id=2236)
  - [x] [POJ 1703: Find them, Catch them](http://poj.org/problem?id=1703)
  - [x] [AOJ 2170: Marked Ancestor](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2170)

# 2.5 图论
- 最短路
  - [x] [AOJ 0189: Convenient Location](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0189)
  - [x] [POJ 2139: Six Degrees of Cowvin Bacon](http://poj.org/problem?id=2139)
  - [x] [POJ 3259: Wormholes](http://poj.org/problem?id=3259)
  - [x] [POJ 3268: Silver Cow Party](http://poj.org/problem?id=3268)
  - [x] [AOJ 2249: Road Construction](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2249)
  - [x] [AOJ 2200: Mr. Rito Post Office](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2200)
  
- 最小生成树
  - [x] [POJ 1258: Agri-Net](http://poj.org/problem?id=1258)
  - [x] [POJ 2377: Bad Cowtractors](http://poj.org/problem?id=2377)
  - [x] [AOJ 2224: Save Your Cats](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2224)
  - [x] [POJ 2395: Out of Hay](http://poj.org/problem?id=2395)
  
# 2.6 数论
- 辗转相除法
  - [x] [AOJ 0005: GCD and LCM](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0005)
  - [x] [POJ 2429: GCD & LCM Inverse](http://poj.org/problem?id=2429)
  - [x] [POJ 1930: Dead Fraction](http://poj.org/problem?id=1930)
  
- 素数
  - [x] [AOJ 0009: Prime Number](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0009)
  - [x] [POJ 3126: Prime Path](http://poj.org/problem?id=3126)
  - [x] [POJ 3421: X-factor Chains](http://poj.org/problem?id=3421)
  - [x] [POJ 3292: Semi-prime H-numbers](http://poj.org/problem?id=3292)
  
- 快速幂
  - [x] [POJ 3641: Pseudoprime numbers](http://poj.org/problem?id=3641)
  - [x] [POJ 1995: Raising Modulo Numbers](http://poj.org/problem?id=1995)
  
# 3 中级算法

# 3.1 二分搜索
- 最大化最小值
  - [x] [POJ 3258: River Hopscotch](http://poj.org/problem?id=3258)
  - [x] [POJ 3273: Monthly Expense](http://poj.org/problem?id=3273)
  - [x] [POJ 3104: Drying](http://poj.org/problem?id=3104)
  - [x] [POJ 3045: Cow Acrobats](http://poj.org/problem?id=3045)

- 01分数规划
  - [x] [POJ 2976: Dropping tests](http://poj.org/problem?id=2976)
  - [x] [POJ 3111: K Best](http://poj.org/problem?id=3111)
  
- 第k大值
  - [x] [POJ 3579: Median](http://poj.org/problem?id=3579)
  - [x] [POJ 3685: Matrix](http://poj.org/problem?id=3685)
  
- 最小化第k大值
  - [x] [POJ 2010: Moo University - Financial Aid](http://poj.org/problem?id=2010)
  - [x] [POJ 3662: Telephone Lines](http://poj.org/problem?id=3662)
  
- 其他二分搜索
  - [x] [POJ 1759: Garland](http://poj.org/problem?id=1759)
  - [x] [POJ 3484: Showstopper](http://poj.org/problem?id=3484)
  
# 3.2 常用技巧
- 尺取法
  - [x] [POJ 2566: Bound Found](http://poj.org/problem?id=2566)
  - [x] [POJ 2739: Sum of Consecutive Prime Numbers](http://poj.org/problem?id=2739)
  - [x] [POJ 2100: Graveyard Design](http://poj.org/problem?id=2100)

- 反转
  - [x] [POJ 3185: The Water Bowls](http://poj.org/problem?id=3185)
  - [x] [POJ 1222: EXTENDED LIGHTS OUT](http://poj.org/problem?id=1222)
  
- 弹性碰撞
  - [x] [POJ 2674: Linear world](http://poj.org/problem?id=2674)
  
- 折半枚举
  - [x] [POJ 3977: Subset](http://poj.org/problem?id=3977)
  - [x] [POJ 2549: Sumsets](http://poj.org/problem?id=2549)
  
- 离散化
  - [x] [AOJ 0531: Paint Color](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0531)
  
# 3.3 数据结构（二）
- 树状数组
  - [x] [POJ 1990: MooFest](http://poj.org/problem?id=1990)
  - [x] [POJ 3109: Inner Vertices](http://poj.org/problem?id=3109)
  - [x] [POJ 2155: Matrix](http://poj.org/problem?id=2155)
  - [x] [POJ 2886: Who Gets the Most Candies?](http://poj.org/problem?id=2886)

- 线段树和平方分割
  - [x] [POJ 3264: Balanced Lineup](http://poj.org/problem?id=3264)
  - [x] [POJ 3368: Frequent values](http://poj.org/problem?id=3368)
  - [x] [POJ 3470: Walls](http://poj.org/problem?id=3470)
  - [x] [POJ 1201: Intervals](http://poj.org/problem?id=1201)
  - [x] [UVa 11990: "Dynamic" Inversion](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3141)
  
# 3.4 动态规划（二）
- 状态压缩DP
  - [x] [POJ 2441: Arrange the Bulls](http://poj.org/problem?id=2441)
  - [x] [POJ 3254: Corn Fields](http://poj.org/problem?id=3254)
  - [x] [POJ 2836: Rectangular Covering](http://poj.org/problem?id=2836)
  - [x] [POJ 1795: DNA Laboratory](http://poj.org/problem?id=1795)
  - [x] [POJ 3411: Paid Roads](http://poj.org/problem?id=3411)

- 矩阵的幂
  - [x] [POJ 3420: Quad Tiling](http://poj.org/problem?id=3420)
  - [x] [POJ 3735: Training little cats](http://poj.org/problem?id=3735)

- 数据结构与DP
  - [x] [POJ 3171: Cleaning Shifts](http://poj.org/problem?id=3171)
  
# 3.5 网络流
- 最大流与最小割
  - [x] [POJ 3713: Transferring Sylla](http://poj.org/problem?id=3713)
  - [x] [POJ 2987: Firing](http://poj.org/problem?id=2987)
  - [x] [POJ 2914: Minimum Cut](http://poj.org/problem?id=2914)
  - [x] [POJ 3155: Hard Life](http://poj.org/problem?id=3155)
  
- 二分图匹配
  - [x] [POJ 1274: The Perfect Stall](http://poj.org/problem?id=1274)
  - [x] [POJ 2112: Optimal Milking](http://poj.org/problem?id=2112)
  - [x] [POJ 1486: Sorting Slides](http://poj.org/problem?id=1486)
  - [x] [POJ 1466: Girls and Boys](http://poj.org/problem?id=1466)
  - [x] [POJ 3692: Kindergarten](http://poj.org/problem?id=3692)
  - [x] [POJ 2724: Purifying Machine](http://poj.org/problem?id=2724)
  - [x] [POJ 2226: Muddy Fields](http://poj.org/problem?id=2226)
  - [x] [AOJ 2251: Merry Christmas](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2251)
  
- 最小费用流
  - [x] [POJ 3068: "Shortest" pair of paths](http://poj.org/problem?id=3068)
  - [x] [POJ 2195: Going Home](http://poj.org/problem?id=2195)
  - [x] [POJ 3422: Kaka's Matrix Travels](http://poj.org/problem?id=3422)
  - [x] [AOJ 2266: Cache Strategy](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2266)
  - [x] [AOJ 2230: How to Create a Good Game](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2230)
  
# 3.6 计算几何
- 极限
  - [x] [POJ 1981: Circle and Points](http://poj.org/problem?id=1981)
  - [x] [POJ 1418: Viva Confetti](http://poj.org/problem?id=1418)
  - [x] [AOJ 2201: Immortal Jewels](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2201)
  
- 平面扫描
  - [x] [POJ 3168: Barn Expansion](http://poj.org/problem?id=3168)
  - [x] [POJ 3293: Rectilinear polygon](http://poj.org/problem?id=3293)
  - [x] [POJ 2482: Stars in Your Window](http://poj.org/problem?id=2482)
  
# 4.1 数论（二）
- 模运算
  - [x] [POJ 1150: The Last Non-zero Digit](http://poj.org/problem?id=1150)
  - [x] [POJ 1284: Primitive Roots](http://poj.org/problem?id=1284)
  - [x] [POJ 2115: C Looooops](http://poj.org/problem?id=2115)
  - [x] [POJ 3708: Recurrent Function](http://poj.org/problem?id=3708)
  - [x] [POJ 2720: Last Digits](http://poj.org/problem?id=2720)
  - [x] [GCJ 2011 Final B: Bacterial Reproduction](https://code.google.com/codejam/contest/dashboard?c=1363489#s=p1)

- 矩阵
  - [x] [POJ 2345: Central heating](http://poj.org/problem?id=2345)
  - [x] [POJ 3532: Resistance](http://poj.org/problem?id=3532)
  - [x] [POJ 3526: The Teacher’s Side of Math](http://poj.org/problem?id=3526)
  
- 计数
  - [x] [POJ 2407: Relatives](http://poj.org/problem?id=2407)
  - [x] [POJ 1286: Necklace of Beads](http://poj.org/problem?id=1286)
  - [x] [POJ 2409: Let it Bead](http://poj.org/problem?id=2409)
  - [x] [AOJ 2164: Revenge of the Round Table](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2164)
  - [x] [AOJ 2214: Warp Hall](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2214)
  
# 4.2 博弈论
- 博弈DP
  - [x] [POJ 1082: Calendar Game](http://poj.org/problem?id=1082)
  - [x] [POJ 2068: Nim](http://poj.org/problem?id=2068)
  - [x] [POJ 3688: Cheat in the Game](http://poj.org/problem?id=3688)
  - [x] [POJ 1740: A New Stone Game](http://poj.org/problem?id=1740)

- Nim和Grundy数
  - [x] [POJ 2975: Nim](http://poj.org/problem?id=2975)
  - [x] [POJ 3537: Crosses and Crosses](http://poj.org/problem?id=3537)
  - [x] [CF 138D: World of Darkraft](http://codeforces.com/problemset/problem/138/D)
  - [x] [POJ 2315: Football Game](http://poj.org/problem?id=2315)
  
# 4.3 图论（二）
- 强连通分量
  - [x] [POJ 3180: The Cow Prom](http://poj.org/problem?id=3180)
  - [x] [POJ 1236: Network of Schools](http://poj.org/problem?id=1236)
  
- 2-SAT
  - [x] [POJ 3678: Katu Puzzle](http://poj.org/problem?id=3678)
  - [x] [POJ 2723: Get Luffy Out](http://poj.org/problem?id=2723)
  - [x] [POJ 2749: Building roads](http://poj.org/problem?id=2749)
  
- LCA
  - [x] [POJ 1986: Distance Queries](http://poj.org/problem?id=1986)
  - [x] [POJ 3728: The merchant](http://poj.org/problem?id=3728)

# 4.4 常用技巧（二）
- 栈
  - [x] [POJ 3250: Bad Hair Day](http://poj.org/problem?id=3250)
  - [x] [POJ 2082: Terrible Sets](http://poj.org/problem?id=2082)
  - [x] [POJ 3494: Largest Submatrix of All 1’s](http://poj.org/problem?id=3494)
  
- 双端队列
  - [x] [POJ 2823: Sliding Window](http://poj.org/problem?id=2823)
  - [x] [POJ 3260: The Fewest Coins](http://poj.org/problem?id=3260)
  - [x] [POJ 1180: Batch Scheduling](http://poj.org/problem?id=1180)
  - [x] [AOJ 1070: FIMO sequence](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1070)

# 4.5 智慧搜索
- 剪枝
  - [x] [POJ 1011: Sticks](http://poj.org/problem?id=1011)
  - [x] [POJ 2046: Gap](http://poj.org/problem?id=2046)
  - [x] [POJ 3134: Power Calculus](http://poj.org/problem?id=3134)
  
- A\*与IDA\*
  - [x] [POJ 3523: The Morning after Halloween](http://poj.org/problem?id=3523)
  - [x] [POJ 2032: Square Carpets](http://poj.org/problem?id=2032)
  - [x] [UVa 10181: 15-Puzzle Problem](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=13&page=show_problem&problem=1122)

# 4.6 分治
- 数列分治
  - [x] [POJ 1854: Evil Straw Warts Live](http://poj.org/problem?id=1854)

- 平面分治
  - [x] [GCJ 2009 Final B: Min Perimeter](https://code.google.com/codejam/contest/dashboard?c=311101#s=p1)
  - [x] [CF 97B: Superset](http://codeforces.com/problemset/problem/97/B)
  
- 树分治
  - [x] [POJ 2114: Boatherds](http://poj.org/problem?id=2114)
  - [x] [UVa 12161: Ironman Race in Treeland](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&category=243&problem=3313)
  - [x] [SPOJ 2939: Query on a tree V](http://www.spoj.com/problems/QTREE5/)
  
# 4.7 字符串
- 字符串DP
  - [x] [AOJ 2212: Stolen Jewel](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2212)
  - [x] [CF 86C: Genetic Engineering](http://codeforces.com/problemset/problem/86/C)
  
- 字符串匹配
  - [x] [CF 25E: Test](http://codeforces.com/problemset/problem/25/E)
  - [x] [AOJ 1312: Where's Wally](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1312)

- 后缀数组
  - [x] [POJ 1509: Glass Beads](http://poj.org/problem?id=1509)
  - [x] [POJ 3415: Common Substrings](http://poj.org/problem?id=3415)
  - [x] [POJ 3729: Facer’s string](http://poj.org/problem?id=3729)
  - [x] [AOJ 2292: Common Palindromes](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2292)
  - [x] [CF 123D: String](http://codeforces.com/problemset/problem/123/D)

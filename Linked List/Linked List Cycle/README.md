## 如何判断单链表存在环 「LeetCode 141」

利用快慢指针方法，设定两个指针 slow、fast，初始都指向头指针，其中 slow 每次前进一步，fast 每次前进二步；如果单链表存在环，那么 fast 必定先进入环，而 slow 后进入环，必定会相遇。否则不存在环，fast 遇到 NULL 退出。

## 对于存在环的单链表，求出环的入口点 「LeetCode 142」

![](https://github.com/steveLauwh/Data-Structures-And-Algorithms/raw/master/Linked%20List/Linked%20List%20Cycle/Linked%20List%20Cycle.PNG)

推理：

fast 与 slow 相遇时，slow 肯定没有遍历完链表，而 fast 已经在环内循环了 n 圈(n>=1)。

标记三个点，起始点为 X，环的入口点为 Y，相遇点为 Z。

设整个链表长度为 L，起始点到环的入口点距离为 a，环的入口点到相遇点距离为 b，相遇点到环的入口点距离是c。(起始点是开始，方向性)

假设 slow 走 s 步，则 fast 走了 2s 步(fast 步数还等于 s 加上 在环上多转的 n 圈)，环长为 r；

得出关系：2s = s + nr，所以 s = nr。

此时，slow 和 fast 相遇， 得出关系：a + b = s = nr。

a + b = nr = (n-1)r + r = (n-1)r + L -a

a = (n-1)r + (L - a - b)

其实 (L - a - b) 就是相遇点到环的入口点的距离，等于 c。

表达式关系表明：从链表头到环的入口点 等于 (n-1)个环 + 相遇点到环的入口点。其中 (n-1)个环 最终还是它自己的起点，于是从链表头开始走和从相遇点开始走，
每一次各走一步，两个指针必定会相遇，且相遇第一点就是环的入口点。


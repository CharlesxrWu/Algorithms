## Plus One Linked List「LeetCode 369」

题目：链表加1

```
Given a non-negative number represented as a singly linked list of digits, plus one to the number.

The digits are stored such that the most significant digit is at the head of the list.

Example:
Input:
1->2->3

Output:
1->2->4
```

解题思路：

此题从链表末尾加1，考虑进位，最容易想到的先把链表反转，再加1，然后求出结果，再把链表反转。

1. 反转链表
2. 循环遍历，从链表首元素开始加1，考虑进位
3. 再反转链表


另一种方法：可以利用栈的特性，先进后出

1. 先把链表节点全部入栈
2. 链表的尾节点最先出栈，加 1 操作，如果进位，继续出栈相加；当栈的最后一个节点(链表头节点)出栈，加进位操作，如果 carry 大于0，那么需要在链表头部插入一个新节点。

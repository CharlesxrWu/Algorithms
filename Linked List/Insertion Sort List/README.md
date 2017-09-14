## Insertion Sort List「LeetCode 147」

题目：使用插入排序算法排序一个链表

```
Sort a linked list using insertion sort.
```

解题思路：

1. 插入排序使用链表中，思想与使用数组中一样，时间复杂度为 O(n^2), 空间复杂度为 O(1)
2. 借助哑节点 dummy，每次遍历，把当前节点插入到已排序的链表中，这里已排序链表是当前遍历节点前的已排序链表
3. 如何插入已排序链表，其实也需要遍历，值大小判断
4. 找到插入的位置，涉及到链表插入操作
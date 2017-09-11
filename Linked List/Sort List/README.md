## Sort List「LeetCode 」

题目：使用常数级的空间复杂度，时间复杂度为 O(nlogn) 排序一个链表。

```
Sort a linked list in O(n log n) time using constant space complexity.
```

解题思路：

1. 排序算法时间复杂度为 O(nlogn)，可以使用归并排序、快速排序、堆排序实现
2. 此题使用归并排序求解，之前针对数组使用归并排序，空间复杂度 O(N)，需要复制出相等的空间来进行赋值归并。

由于链表进行归并排序，根据链表特性，并不需要复制相等的空间进行赋值归并：

1. 如何找出链表的中间点
2. 两部分递归，递归完后，两部分已排序
3. 最后对两个已排序链表进行合并操作(Merge Two Sorted Lists) 



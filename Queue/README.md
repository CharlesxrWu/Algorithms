## Queue

queue 是一种先进先出的数据结构。

queue 允许新增元素、移除元素、从最底端加入元素、从最顶端取出元素。

```c++
// STL C++
push(x): 将 x 入队列的末端。

pop(): 弹出队列的第一个元素。

front(): 访问队首元素。

back(): 访问队尾元素。

empty(): 判断队列空。

size(): 队列中的元素个数。
```

> **为什么 C++ STL queue 需要 front/pop ?**

C++ STL的 std::queue 类是个容器适配器，即由其它容器(deque)包装而成的特殊数据结构。

pop 和 front 这两个成员函数，一个删除队首顶素，一个获得队首元素，在绝大多数情况下，必须联合使用才能完成我们需要的动作。
因为我们在使用队列时，最常用的操作就是把队首元素从队列中“取”出来并进行处理。

```c++
#include <queue>

queue<A> q;

// 基于 pop 返回的对象来构造对象 a，这是拷贝构造；如 A 类的拷贝构造函数抛出了异常，不符合关于异常安全的 “强保证” 要求。
A a = q.pop(); 
```

所以 STL std::queue 结合 front 和 pop 两个函数，在其元素类型的拷贝构造函数可能抛出异常的情况下，仍然能达到强异常安全级别。

## LeetCode Queue

* [Moving Average from Data Stream](https://github.com/steveLauwh/Data-Structures-And-Algorithms/tree/master/Queue/Moving%20Average%20from%20Data%20Stream)

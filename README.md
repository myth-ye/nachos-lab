# nachos-lab

## lab1

usage : ./nachos -q [threadNum] -N [itemNum] -E [errorNum] -d t

errorNum meanings

1. 在往空链表添加第一个元素时Yield。last指针没有正确添加，last指针为NULL 造成segment fault。
2. 更新链表最小元素时Yield。
3. 更新last元素时Yield。
4. 删除链表里唯一一个元素时Yield。



未解决bug：用指定的char指针创建进程名



参考：多线程生成随机数 http://blog.csdn.net/jfkidear/article/details/52854166

## lab2

usage : ./nachos -M [testMode]-q [threadNum] -N [itemNum] -E [errorNum]  t

###参数解释

- threadNum : 线程数量
- itemNum : 添加item个数
- errorNum : 错误种类
- t : 线程模式下运行
- testMode
  - 1 : 多线程链表操作实验
  - 2 : 生产者/消费者测试实验
  - 3 : 线程表测试实验

完成了实验附加题以外的部分。

删除了DEBUG函数的使用，十分鸡肋并且有BUG，直接改用printf。

一些坑

1. 编译报错：Lock does not name a type。原来是dllist.h里没添加lock的头文件，编译器真蠢。
2. ASSERT((index >= 0) && (index < tsize)); 一开始边界测试index>0 第一个表项就读不出来吓坏了。 

## About

This is nachos programming project used for computer system organization at New York University in spring  2005.
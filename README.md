# nachos-lab

## lab1

usage : ./nachos -q <threadNum> -N <itemNum> -E <errorNum> -d t

errorNum meanings

1. 在往空链表添加第一个元素时Yield。last指针没有正确添加，last指针为NULL 造成segment fault。
2. 更新链表最小元素时Yield。
3. 更新last元素时Yield。
4. 删除链表里唯一一个元素时Yield。



未解决bug：用指定的char指针创建



参考：多线程生成随机数 http://blog.csdn.net/jfkidear/article/details/52854166



## About

This is nachos programming project used for computer system organization at New York University in spring  2005.
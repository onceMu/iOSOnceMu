<h3>Runtime Pragramming Guide<h>

OC  总是将更多的决策从编译时间和链接时间延迟到运行期间。尽可能的动态窒息性代码。OC不仅需要编译器，还需要runtime系统来运行已编译的代码。

OC源代码

NSObject 方法

Runtime 方法

消息messaging

objc_msgSend 方法

​	在OC中，消息只有在运行时才会绑定到实现方法。编译器会把一个消息表达式

[receiver message] 转化成一次对消息函数objc_msgSend 的调用。

​	Objc_msgSend 函数将消息的接收者和消息中的方法名作为参数，任何在消息中传递的参数也同样会被objc_msgSend处理。

​	objc_msgSend(receiver, selector, arg1 ,arg2 …);

Objc_msgSend 提供了动态绑定所有需要的准备

​	1.首先会找到选择器引用的过程（方法实现），由于相同的方法可以被不同的类实现，因此最终找到的过程依赖于接收者的类；

​	2.然后会调用这个过程，传给它接收的对象（指向它的数据的指针），以及这个方法需要的其它参数。

​	3.它将整个过程的返回值当成自己的返回值。

消息发送的关键在于编译器为每个类和对象生成的结构，每个类结构都包含两个基本元素：

1.指向superclass 的指针；

2.一个类分配表。这个表的条目包含方法的选择器和特定类的方法地址的映射。

当一个对象被创建之后，内存会被分配，它的实例变量会被初始化。实例变量中包含了一个指针指向了它的类结构。这个指针就是isa，通过isa能够访问它的类，并且通过这个类能够访问它的所有父类。



消息传递过程 ——方法被动态绑定到消息的方式

1.当消息发送给一个对象时，消息函数随着isa指针在其类的消息分发表中查找对应的selector，

2.如果没有找到对应的selector，objc_msgSend 会跟随指向父类的指针并在其dispatch table中查找对应的selector，如果一直失败objc_msgSend 会沿着继承体系不断向上，直到到达NSObject类，

3.如果找到selector，消息函数会调用该方法并将接收对象的数据结构传递给它。

为了加速消息的处理，Runtime系统会缓存selector和使用过的method address。每个类都有一个独立的缓存，能存储从父类继承来的方法以及自己独特的methid selector。在检索dispatch table之前，messaging routine （消息路由）会检查接受消息对象的类的缓存，如果在缓存中命中，那么消息处理仅仅比方法调用慢一点。



隐藏参数

objc_msgSend 在调用过程中会传递两个隐藏的参数：

1.receiver

2.selector

这两个参数没有在方法的源代码中明确的声明，而是在编译期间插入实现中的。

尽管这两个参数没有被明确声明，但是源代码仍然可以引用他们。self 来引用接受对象（receiver），_cmd 来引用selector。



获取方法地址

避免动态绑定的唯一方法就是获取方法的地址然后直接调用它，就好像函数一样。在一些罕见的情况下，你可能想要特定的方法按书序执行很多次但又想避免每次方法执行时发消息的开销。

通过NSObject类中的methodForSelector：方法，能够查询实现一个方法的函数指针，然后可以用这个指针调用这个函数。methodForSelector：方法返回的函数指针必须被小心地转换成合适的类型，包含返回值和参数。



动态方法解析

有时候，可能需要动态地给一个方法提供实现。

https://developer.apple.com/documentation/objectivec/objective_c_runtime

https://blog.csdn.net/syd_programming/article/details/49340955
https://artandlogic.com/2014/01/digging-into-the-objective-c-runtime/

看完。



​	

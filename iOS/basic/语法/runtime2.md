Runtime 应用

1.automatic ivar / method searches

​	KVC(键值编码)已经做了这件事情。你给KVC一个名称，然后KVC会基于这个名称去查找方法或者ivar，

2.automatically register/ invoke subclasses 自动注册/调用子类

​	通过objc_getClassList 可以获取到运行时系统所知的所有的类列表，通过追踪类的继承关系，你可以确定一个类的子类。

3.automatically call a method on every class 自动在每一个类中调用一个方法



4.override method at runtime  在运行时重载方法

运行时提供了一套完整的工具方法来自定义完成调整方法，这样你可以在不接触源代码的情况下去修改某个类。

5.Automatically deallocate synthesized properties 自动释放合成属性

@synthesize 关键词方便编译器生成setter和getter方法，但是你任然需要在dealloc 方法中写释放代码。

6.Bridging  桥接





Runtime message  消息

Definitions 定义

​	很多人不清楚到底什么是“方法”和”消息“。
	方法：跟一个类联系起来的实际的代码，并且有一个特定的名称。例如：

​		-(int)meaning { return 42 ;}

​	消息：一个名称和一个参数发送给一个对象。例如：

​		给0x12345678 发送一个没有参数的消息 meaning

​	selector：特定的方式代表一条消息或者方法的名称，SEL 类型。selector本质上是通过不透明的字符串进行管理，这样可以简单的使用equality来比较它们。例如@selector(meaning)

​	消息发送 message send: 一个消息找到适合的接收者并且执行的过程



这个文章看起来还是很晦涩





Runtime基础

Runtime是 OC 区别于C 语言这种静态语言的一个非常重要的特性，C语言的函数调用在编译期间就已经决定好，在编译完成之后按顺序执行就可以，但OC是一门动态语言，函数调用变成了消息发送，在编译期不能知道要调用哪个函数。



Objc/runtime.h 中基础定义

Struct objc_class {

​	Class isa OBJC_ISA_AVAILABILITY;

# if !__OBJC2__

​	Class super_class  OBJC2_UNAVAILABLE;

​	const char *name   OBJC2_UNAVAILABLE;

​	long version.            OBJC2_UNAVAILABLE;

​	long instance_size.   OBJC2_UNAVAILABLE;

​	struct objc_ivar_list *ivars.      OBJC2_UNAVAILABLE;//成员变量列表

​	struct objc_method_list **methodList2.  OBJC2_UNAVAILABLE;//方法地址列表

​	struct objc_cache *cache. OBJC2_UNAVAILABLE;//缓存最近使用的方法地址，提高查找效率

​	struct objc_protocol_list *protocols   OBJC2_UNAVAILABLE;//协议列表

}OBJC2_UNAVAILABLE;



SEL 与 IMP

​	typedef stuct objc_selector *SEL;

​	struct objc_selector {

​		char *name;

​		char *types;

}

IMP为函数指针，指向了最终的实现

SEL与IMP的关系类似哈希表中的key与value的关系，OC不支持函数重载的原因是因为一个类的方法列表中不能存在两个相同的SEL，但是多个方法确可以在不同的类中有一个相同的SEL，不同类的实例对象执行相同的SEL时，会在各自的方法列表中根据SEL去寻找对应的IMP，这样间接支持函数重载。



消息传递机制

当对象调用[recevier message]的时候，实际上是调用了runtime的objc_msgSend 函数，具体流程为：

1.首先[receiver message] 函数会被改写成为objc_msgSend(self,_cmd); self 是runtime过程中的隐藏参数，self指向接收对象的指针，__cmd 是该selector

id returnValue = objc_msgSend(someObject,@selector(messageName:),parameeter);

2.方法需要在接收者所属的类中搜寻其 方法列表，list of methods，如果能找到与selector名称相符的方法，就跳至其实现代码，如果找不到，就沿着继承体系继续向上查找，等找到合适的方法之后再跳转，如果最终找不到相符的方法，就执行消息转发操作。

3.objc_msgSend会将匹配结果缓存在fast map里面，（fast map是一个hashtable）。每个类都会有一块缓存，如果稍后还会向该类发送与selector相同的消息，执行就会快很多。这种fast path 与 静态绑定的函数调用操作比较起来，会慢不少，但是假如selector缓存之后，就不会慢很多。messagee dispatch并不是应用程序的瓶颈所在。

边界条件

1.待发送的消息需要返回结构体，可以由objc_msgSend_stret函数处理。只有当CPU的寄存器能容纳下消息返回类型时，函数才能处理消息。

2.返回的是浮点数，有objc_msgSend_fpret处理。

3.给父类发送消息[supert message:parameter];有objc_msgSendSuper处理。



消息转发

对象在收到无法解读的消息之后会发生什么？

如果想让类能够理解某条消息，我们必须实现对应的方法才行。但是，在编译期向类发送了其无法解读的消息并不会报错，因为在运行期可以继续向类中添加方法，所以编译器在编译时还无法确知类中到底会不会有某个方法实现。当类接收到无法解读的消息后，就会启动消息转发机制。

消息转发的两个阶段

1.先征询receiver以及所属的类，能否动态的添加selector对应的方法，来处理unknown selector。

2.完整的消息转发机制。



1.对象在收到无法解读的消息后，首先调用其所属类的类方法：

+(BOOL)resolveInstanceMethod:(SEL)selector;

首先将selector 转换成字符串 NSString *method = NSStringFromSelector(selector);



https://blog.csdn.net/qq_36819141/article/details/75125648








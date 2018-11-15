NSObject 对象

+(void)alloc方法

 _objc_rootAlloc(self)

callAlloc(Class cls,bool checkNil, bool allocWithZone=false)

https://my.safaribooksonline.com/book/programming/objective-c/9780132908641/3dot-memory-management/ch03



直接访问实例变量的速度比点语法要快，在ARC下直接访问实例变量，并不会触发set方法，只会保留新值释放旧值

直接访问实例变量，不会触发KVO通知

在惰性初始化中，必须使用点语法来访问属性，否则实例变量可能会永远不会初始化。





关联对象方法以及对应的内存管理语义

void objc_setAssociatedObject

void objc_getAssociatedObject

void objc_removeAssociatedObject



C语言属于静态绑定，编译期间就能决定运行时对应调用的函数。



void objc_msgSend(id self, SEL cmd,...)

方法在接收者所属的类中搜寻其方法列表，如果找到与sel名称相符的方法，就直接跳至其实现代码。如果找不到，就沿着继承体系继续向上寻找，等找到合适的方法之后再跳转。

如果找不到对应的方法，就执行消息转发，message forwarding

消息转发第一阶段：

征询接收者，所属的类，看其是否能动态添加方法，用来处理当前的未知selector

消息转发第二阶段：

先看有没有其他对象能处理这条笑嘻嘻，如果有，则消息会转发给那个对象，消息转发结束

如果没有接收者，则启动完整消息转发机制，封装到NSInvocation对象中













数组：

查询O(1)

删除O(n)

插入O(n)





链表

单链表

双重链表



链表插入与删除都是O(1)








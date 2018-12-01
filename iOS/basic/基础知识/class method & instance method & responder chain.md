类方法和 实例方法

 	+ (void)foo;

​        -  (void)foo;

类方法(静态方法) 在程序开始的时候就生成内存，内存分配在堆上

实例方法在程序运行中生成内存，内存分配在栈上

类方法可以直接调用，实例方法需要先生成实例对象，然后通过实例对象来调用。

类方法中不可以直接使用实例变量。

类方法可以调用类方法，但是不能直接调用实例方法，可以通过创建实例对象来访问实例方法。

实例方法中的self 是对象的首地址

类方法中的self，是Class对象。





响应者链与Hit-Test Chain

app在启动之后会生成一个UIApplication 单例对象

三种事件来源

1.UIControl Action，以target/action 

2.User events，toucher、shakes、motion等等

3.System events：memory、rotation等

所有的事情在被分发到正确的接收者之前都要被application的单例对象处理。

事件分类Event

1.Touch Event（触摸事件）

2.Motion Event (运动事件)

3.Remote-Control Events (远程控制事件)





UIControl Action

调用addTarget:action:forControlEvents: 

事件处理过程：

1.事件发生时，先进行事件传递

​	App(UIApplication)  ---> window（UIWindow） ---> View（hit-test view）

2.寻找响应者

​	第一响应者是第一个接收事件的View对象。如果first responder 无法响应事件，就会传递给next responder，如果没有人响应，就会直接丢弃掉该事件



Next responder

UIWindow 的next responder 是UIApplication

UIApplication的下一个是nil










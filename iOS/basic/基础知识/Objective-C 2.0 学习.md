Effective-C 2.0学习

1.语言起源

​	OC属于面向对象的语言，OC使用消息结构，而不是函数调用。使用消息调用的语言，其运行时所执行的代码由运行环境来决定，而使用函数调用的语言，由编译器决定。消息调用的语言，总是在运行时去查找所要执行的方法。

​	对象所占内存总是分配在堆空间，而绝不会分配在栈上。

​	NSString *a = @"x"; NSString *b = a;

​	这个时候a 、b都是分配在栈上的， "x" 分配在堆上，a、b 都指向“x”；

​	分配在堆中的内存必须直接管理，而分配在栈上用于保存变量的内存都会在其栈帧弹出时自动清理。OC将堆内存管理抽象出来了，不需要用malloc以及free来分配或释放对象所占内存。

​	OC中也会有遇到不带 * 的变量，可能会存储在栈空间，如CGRect

2.向前申明，.h文件中少 #import文件

3.多用字面量方法，少用与之等价的方法

4.多用类型常量，少用#define 预处理指令 如果常量紧限于编译单元，即.m文件中，则在前面加字母k，如果常量在类之外可见，则通常以类名未前缀。static const 也尽量不在.h文件中出现，这样相当于声明了一个全局变量。变量一定要同时用static 和const 来声明，如果视图修改由const修饰符所声明的变量，编译器会报错。而static 修饰符意味着该变量仅在定义此变量的编译单元可见。

5.多用枚举值表示状态、选项、状态码。多了解位运算

6.理解属性概念

​	OC对象通常会把其所需要的数据保存为各种实例变量。实例变量一般通过存取方法访问。getter用来读取变量，setter用于写入变量值，

​	解决地址偏移问题，OC把实例变量当做一种存储偏移量所用的特殊变量，交由类对象保管，偏移量会在运行期间进行查找，如果类的定义变了，那么存储的偏移量也会变化，无论何时访问实例变量，总能使用正确的偏移量。

​	尽量不直接访问实例变量，而是通过存取方法来做。

​	属性的基本特质

1.原子性

​	默认情况下，编译器会通过同步锁确保原子性（atomicity）。如果属性具备nonatomic，则不使用同步锁。

2.读/写权限

​	readwrite，拥有getter、setter方法。如果属性由@synthesize实现，编译器会自动生成setter、getter方法

​	readonly，只拥有getter方法，只有属性由@synthesize实现时，编译器才会为其合成获取方法，

3.内存管理语义

​	属性用于封装数据，数据则要有具体的所有权语义，编译器在合成存取方法时，根据内存语义来决定所生成的代码。

​	assign、设置方法，主要用于纯量类型，CGFloat、NSInteger等赋值操作，MRC时候会把delegate设置为assgin

​	strong、表明属性定义一种拥有关系，用strong的时候，属性设置新值的时候，会先保留新值，然后释放旧值，再设置新值

​	weak、非拥有关系，设置新值的时候，setter既不会保留新值，也不释放旧值，与assign类似，属性所指的对象遭到摧毁时，属性也会被清空

​	unsafa_unretained、与assign相同，但适用于对象类型，(object-type)，表达一种非拥有关系，当目标对象遭到摧毁时，属性值不会自动清空

​	copy、与strong类似，但是设置方法并不会保留新值，而是将其copy。当类型为NSString时，经常用copy来保护其封装性。

4.方法名

​	getter=<name> 指定获取方法的方法名

​	setter=<name>指定设置方法的方法名



7.在对象内部尽量直接访问实例变量

​	在对象之外访问实例变量时，总是应该通过属性来做，在对象内部访问实例变量时，在读取的时候采用直接访问的形式没在设置实例变量的时候通过属性来做。需要注意的是lazy initialization，必须通过 获取方法来访问属性，否则实例变量会永远不会初始化。

8.对象等同性

​	==操作符比较出来的是两个指针而本身，而不是其所指的对象。

​	指针相等，意味着指向同一个对象

​	

​	NSObject协议中有两个判断等同性的关键方法

 - （BOOL）isEqual:(id)object；

 -   (NSUInteger)hash;

   isEqual 返回YES时候，hash返回的值肯定是同一个，hash值是同一个的时候，isEqual并不一定返回YES

   

		isEqual:
	
		isEqualToString:
	
		后面的方法性能会优于第一个方法
	
		NSArray、NSDictionary也有对应的判断等同性的方法，OC在编译期不做强类型检查，容易不小心传入类型错误的对象，开发者应保证所传对象的类型是正确的。
	
		数组判断等同性时，先判断两个数组对象个数是否相同，如果相同，则在每个对应位置的两个对象上调用isEqual方法，如果都相等，那么两个数组相等，叫做等同性判定。
	
		如果在collection中加入可变对象时，如果加入的可变对象在不断的变换，那么set的行为很难预料，可能存在一个set中存在两个一样的值

9.类族模式隐藏实现细节

​	类族可以隐藏抽象基类背后的实现细节。比如UIButton方法，初始化的时候可以调用类方法，+(UIButton *)buttonWithType:(UIButtonType)typee;这样使用者无须关心创建出来的按钮具体属于哪个子类，也不用考虑按钮的绘制方式等实现细节。

10.在已有的类中使用关联对象存放自定义数据

​	关联对象，associated object ，可以给某对象关联许多其对象，这个对象通过键来区分。存储对象值时，可以指明storage policy（存储策略），用于维护相应的内存管理语义。

|             关联类型              | 等效的@property属性 |
| :-------------------------------: | :-----------------: |
|      OBJC_ASSOCIATION_ASSIGN      |       assign        |
| OBJC_ASSOCIATION_RETAIN_NONATOMIC |  nonatomic、retain  |
|  OBJC_ASSOCIATION_COPY_NONATOMIC  |   nonatomic、copy   |
|      OBJC_ASSICIATION_RETAIN      |       retain        |
|       OBJC_ASSOCIATION_COPY       |        copy         |

可以使用下列方法管理关联对象

1.void objc_setAssociatedObject (id object,void *key,id value,objc_associationPolicy policy)

​	object :关联对象，一般为self

​	*key: key对应的指针地址

​	value: 关联的value

​	objc_associationPolicy: 内存管理语义

2.void objc_removeeAssociatedObjects(id object)

​	移除全部的关联对象

3.void objc_getAssociatedObject(id object,void *key)

​	获取object对象的  key指针地址对应的关联对象

设置关联对象时用到的key是个不透明的指针，opaque pointer，如果在两个键上调用isEqual方法时，返回的是YES，在设置关联对象时，若想要两个键匹配到同一个值，则而知必须是完全相同的指针才行。因此设置关联对象值时，通常使用静态全局变量作为key。很多第三方库都利用了这个特性，为对象关联了其余的属性。



11.理解 objc_msgSend的作用

​	在对象上调用OC方法，被称为消息传递。消息有 name、selector、可以接受的参数、而且可能还有返回值。

​	C语言中，使用静态绑定（static binding），也就是在编译器决定运行时所调用的函数。编译器在编译代码的时候就已经知道程序中的函数，于是会直接函数的指令，函数地址实际上是硬编码在指令中的。

​	void objc_msgSend(id self, SEL cmd,…..)

​	对下面的方法调用

​	id returnValue = [someObject messageName:parameter];

​	编译器会转换成

​	id returnValue = objc_msgSend(someObject,@selector(messageName:),parameter);

​	objc_msgSend 函数会依据接收者与selector的类型来调用适当的方法，为了完成操作，方法需要在接收者所属的类中搜索期  方法列表，list of methods.如果能找到与selector 名称相符的方法，就跳转至其实现代码，如果找不到，就沿着继承体系继续向上查找，等找到合适的方法之后再跳转，如果最终还是找不到相符的方法，就会窒息性 消息转发（message forwarding）操作。

​	objc-msgSend 会将匹配结果缓存在快速映射表中，每个类都有这样一块缓存，如果稍后还会向该类发送与selector相同的方法，执行就会很快。fast path 还是没有statically bound founction call 迅速。message dispatch并不会成为应用的瓶颈。

​	边界情况出路

​	objc_msgSend_stret,如果待发送的消息要返回结构体，由此函数处理，如果CPU的寄存器能容纳下消息返回类型时，才能处理，如果不能容纳，就会由另外函数进行处理。

​	objc_msgSend_fpret，处理浮点数

​	objc_msgSendSuper，需要给父类发消息，由此函数处理

​	

​	selector 特性

​	1.OC 维护了一个巨大的selector列表

​	2.在使用@selector 的时候，会从和这个selector 列表中根据 selector 名字查找对应的SEL，如果没有找到，会生成一个SEL 并添加到表中

​	3.在编译期间会扫描全部的头文件以及实现文件，将其中的方法以及使用@selector 生成的 selector 加入到列表中



12.理解消息转发机制

​	在编译期向类发送无法解读的消息并不会报错，因为在运行期可以继续向类中添加方法，当对象接受到无法解读的消息，就会启用 消息转发 message forwarding 机制。

​	消息转发的阶段

 	1. 动态方法解析（dynamic method resolution）  征询接收者、其所属的类，看其是否能动态添加方法，以处理当前这个未知的selector。
		2. 完整的消息转发机制，如果在运行期系统把第一阶段都执行了，那么接收者自己就无法再用动态新增方法的手段来响应包含该selector的消息，此时，系统会请求接收者以其他手段来处理与消息相关的方法调用。首先，查看是否有其他对象能处理该消息，如果有，则系统会将消息转发给可以处理的对象，于是消息转发结束。如果没有，则启动完整的消息转发机制，系统会把与消息有关的全部细节都封装在NSInvication对象中，再给接受者最后一次机会，令其设法解决当前还未处理的消息。

动态方法解析 dynamic method resolution

​	在接收到无法解读的消息后，首先调用对象所属类的 类方法

 + （BOOL）resolveInstanceMethod:(SEL)selector

   参数就是未知的selector，返回BOOL值，表明这个类是否能新增一个实例方法来处理该selector，如果未实现的方法不是实例方法而是类方法，会调用 resolveClassMethod：

询问其余的接收者

​	当前接收者第二次机会处理未知的selector，系统会询问，能否把消息转给其余的selector 来处理

 - （id）forwiardingTargetForSelector:(SEL)selector

   如果找到就将其返回，如果找不到就返回nil

完整的消息转发

​	如果没有找到可以转发的对象，那么就会启用完整的消息转发机制。首先会创建NSInvovation对象，把未处理的消息封装在其中，（包含selector、target、参数）；然后mesage-dispatch system 会把消息指派给目标对象

- （void）forwardInvocation:(NSInvocation *)invocation



13.method swizzling

​	与selector 相同的方法可以在运行期间进行改变。类的方法列表会把selector的名称映射到相关的实现方法上，这样method swizzling可以根据找到应该调用的方法，这些方法会以函数指针IMP 的形式来表示。 

​	id (*IMP )(id,SEL，…)；

​	1.互换两个已经写好的方法

​	void mehtod_exchangeImplementations(Method m1, Method m2);

​	上述函数的参数可以用下面的方法来获取

​	Method class_geInstanceMethod(Class aClass, SEL aSelector);



14.类对象

关于runtime相关的单独总结。



15.前缀来避免命名空间冲突

​	OC没有命名空间，所以需要避免出现潜在的命名冲突。

​	常见的错误

​	duplicate symbol

​	duplicate symbol error

16.提供全能初始化方法

​	把可以为对象提供必要信息以便其能完成工作的初始化方法叫做指定初始化方法(designated initializer)。

​	如果子类的指定初始化方法与父类的指定初始化方法名称不同，那么需要覆写父类的指定初始化方法。

​	如果子类不愿意覆写父类的指定初始化方法，常见的解决办法是覆写父类的指定初始化方法，并抛出异常。

​	在类中提供全能初始化方法，其余初始化方法都需要调用此方法

​	如果指定初始化方法与父类中不同，则应该覆写父类的对应方法

​	如果父类的指定初始化方法不适用于子类，那么应该覆写这个父类方法，并在其中抛出异常。



17.实现description方法

​	在覆盖的description方法中，还是需要打印出类的对象和指针地址，尽量详细。



18.尽量使用不可变对象

​	尽量创建不可变的对象

​	如果某属性仅可用于对象内部修改，则在 class-continuation分类中将由readonly属性扩展成为readwrite属性

​	不要把可变的collection做为属性公开，而应该提供向相关方法，一次修改对象中的可变collection



19.使用清晰而协调的命名方式

​	

20.为私有方法名加前缀



21.理解OC的错误类型

​	ARC在默认情况下不是异常安全的。如果抛出异常，那么本应该在作用域末尾释放的对象现在确不会自动释放了。

​	在ARC下，NSError * 会被转换成 NSError *__autoreleasing *

22.理解NSCopying协议

	- (id)copyWithZone:(NSZone *)zone

以前的程序，会根据此方法把内存分成不同的区，而对象会创建在某个区了，现在每个程序只有一个区。

浅拷贝与深拷贝

浅拷贝之后的内容与原始内容均指向相同对象。

深拷贝之后的内容所指对象时原始内容中相关对象的一份拷贝。

23.协议

24.将类的实现代码分散到便于管理的数个分类之中

25.总是为第三方类的分类名称加前缀

26.尽量不在分类中声明属性

​	虽然可以在分类中声明属性，但是尽量避免这种做法，除了 class-continyation分类，其它分类都无法向类中新增实例变量。

​	把封装数据所用的全部属性都定义在主接口中；

​	在class-continuation分类之外的分类中，可以定义存储方法，尽量不要定义属性。

2 7.class-continuation 分类隐藏实现细节

28

29.理解引用计数

retain 递增保留计数

release 递减保留计数

autorelease 自动释放池

属性存取方法中的内存管理，保留新值，释放旧值，然后更新实例变量，指向新值。如果还未保留新值就把旧值释放掉，然后两个值又指向同一个对象，那么先执行的release操作可能导致系统将此对象永久回收，而后续的retaion操作则无法令整个已经彻底回收的对象浮生，于是实例变量变成了悬垂指针。

Autorelease会在稍后递减计数，通常是在下一个 event loop 递减。

Retain Cycle

30.ARC简化引用计数

31.dealloc 方法中只释放引用并解除监听

ARC中编译器会通过自动生成.cxxx_destruct 方法

32.编写异常安全代码时留意内存管理问题

33.以弱引用避免保留环 retain cycle

__unsafe_unretained 与 assign 区别：前者多用于对象类型，后者通常用于int、float、struct等。

__unsafe_unretained 与 weak 区别，weak指定的对象被回收之后，会自动置为nil，前者修饰的对象被回收之后还是会指向该对象，访问会crash掉。

34.自动释放池降低内存峰值

35.用僵尸对象调试内存管理问题

系统在即将回收对象时，如果发现运行环境变量启用了僵尸对象功能，那么还将执行一个附加步骤，把对象转化为僵尸对象，不彻底回收。

在运行期间生成一个_NSZombie_ 对象

36.不要使用retainCount，返回的只是保留计数只是某个给定时间点上的值。

37.block问题

​	全局block、栈block、堆block

​	定义block的时候，所占的内存区域是分配在栈中的，也就是说，block只在定义它的那个范围内有效。

​	void (^block)();

​	if(a) {

​		block = ^ {};	

​	}else {

​		block = ^{};

​	}

​	block();

​	上述代码中，定义在if和else 语句中的两个block都分配在栈内存中，编译器会给每个块分配好内存，然后等离开相应的范围之后，编译器有可能把分配给块的内存覆写掉。于是，这两个块只能保证在对应的if或else语句范围内有效。 

​	可以给block 发送消息copy，这样可以把block 	从栈上复制到堆上。block就从栈block变成了堆block。

​	global block

​	如果block捕捉的变量是对象类型，那么就会自动保留它。

38.为常用的块类型创建typedef

​	每个块都有固有类型。

39.用handler block 降低代码分散程度

​	尽量把成功和失败的信息放在同一个block中，

40.block 中的retain cycle

41.多用GCD，少用synchronization block（同步锁）

​	synchronization block 会根据给定的对象，自动创建一个锁，并等待块中的代码执行完成，执行到代码结尾处，锁就释放了。@synchronized（self）会降低代码效率，共用一个锁的同步块，都必须按顺序执行，

​	NSLock对象，NSRecursiveLock（递归锁），线程能多次持有该锁，不会出现死锁的现象。

​	串行同步队列，将读取操作及写入操作都安排在同一个队列。

42.多用GCD，少用performSelector

43.掌握GCD及操作队列的使用时机

...

50.使用NSCache来构建缓存，而不是NSDictionary

​	NSCache好处：

​	1.当系统资源耗尽时，可以自动删减缓存，如果是字典，需要自己手动删除缓存

​	2.NSCache会自动删减最久未使用的对象

​	3.NSCache不会拷贝键，只会retain键

​	4.NSCache是线程安全的，NSDictionary不是线程安全的。

​	

51.简化+ （void）load 和 +（void）initialize方法

load方法在执行其子类load方法之前，必定先执行所有super的load方法，如果代码还依赖了其他程序库，那么程序库里相关类的load方法必定先执行。在load方法中使用其他类是不安全的。

load方法并不遵从继承规则，如果某个类本身没实现load方法，那么不管其super是否实现此方法，系统都不会调用load方法。分类和其所属的类都可能会出现load方法，此时两种代码都会调用，类的实现要比分类的实现先执行。

load方法务必精简一点，尽量减少其所执行的操作，load方法在执行的时候会阻塞整个程序。不要在load中等待锁，也不要调用可能会加锁的方法。



+ (void)initialize 方法

  整个方法会在程序首次调用该类之前调用，且只调用一次。由运行时来调用，绝不应该通过代码调用。

两者区别：

​	1.initialize方法是惰性调用，只有当程序用到了相关的类，才会调用。load方法是应用程序必须阻塞等着所有类的load都执行完，才能继续。

​	2.initialize方法是线程安全的

​	3.initialize 如果该类没实现，但是super 实现了，就会运行super的实现代码。

​	load 和 initialize 都实现的时候，会先调用load 方法，再调用子类的laod方法，当子类的load方法调用完成之后，再调用父类的initialize方法，然后子类的initialize方法





52.NSTimer 会保留对象

​	

​	




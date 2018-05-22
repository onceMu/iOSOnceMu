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

   

​	isEqual:

​	isEqualToString:

​	后面的方法性能会优于第一个方法

​	NSArray、NSDictionary也有对应的判断等同性的方法，OC在编译期不做强类型检查，容易不小心传入类型错误的对象，开发者应保证所传对象的类型是正确的。

​	数组判断等同性时，先判断两个数组对象个数是否相同，如果相同，则在每个对应位置的两个对象上调用isEqual方法，如果都相等，那么两个数组相等，叫做等同性判定。

​	如果在collection中加入可变对象时，如果加入的可变对象在不断的变换，那么set的行为很难预料，可能存在一个set中存在两个一样的值

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

​	
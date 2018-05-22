@property & instance variable 区别

@property 包含对实例变量的get/set方法

self.var 是对属性的访问，_var是对实例变量的访问

@property 声明之后，在ARC下，编译器会自动生成对私有实例变量的setter/getter方法，在.m文件中调用_var方法，不会调用setter/getter方法，但是在外部调用self.var 会调用setter/getter

在getter方法中，必须需使用_var进行访问，如果在getter中使用self.var访问，则会触发getter方法，就会进入一个死循环，同理在setter方法中也是一样的。

在懒加载中，必须使用_var 来访问实例变量，用self.var 会进入到死循环



self.xx = @"xx"  等同于  [self setXx:@"xx"];

property 是一个更加抽象的概念，instance variable 字面意思 只是一个 存储位置，



@property 属性

​	property是OC中的一个特性，把类对象中的实例变量及其读写方法统一封装起来，OC将这些实例变量封装成为一个属性变量，系统可以自动生成getter和setter方法，同时仍然允许开发者利用读写属性参数(readwirte,readonly)  @synthesize  @dynamic关键字去选择性自定义读写方法和方法名。

点语法

​	使用OC的property属性，编译器会自动按照OC的严格存取函数命名规范自动生成对应的存取函数，通过存取函数就可以根据变量名访问对应的变量，点语法访问其变量其实就是调用了变量的存取方法。

属性参数

​	1.原子性  atomic、nonatomic

​	2.读写语义 readwrite、readonly、getter、setter

​	3.内存管理语义 assign、weak、__unsafe_unretained，reatin，copy，strong

原子性：

​	atomic、nonatomic 原子性和非原子性

​	atomic会对setter方法加锁，解决资源竞争的问题，但是加锁同时也存在系统资源消耗的代价。

​	nonatomic非原子性，不会对setter方法加锁，可以提高多线程并发访问时的性能。

读写语义

​	readonly、readwrite、getter、setter	

​	readonly只读，修饰的变量只有getter方法，没有setter方法

​	readwrite读写，可读可写，既有getter方法，又有setter方法

​	getter = <gettername> 

​	setter = <settername>

内存管理语义

​	assign 直接简单赋值，不会增加对象的引用计数，用于修饰非OC类型，如NSInteger、C语言类型int、float、double、char等，或者修饰对指针的弱引用

​	weak 修饰弱引用，不增加引用计数，主要用于便面循环引用，与strong/retain对应，weak修饰的对象消失后悔自动将指针置为nil，防止悬挂指针。iOS5.0 之后有的语义

​	unsafe_unretain  和weak一样 自己创建并持有的对象之后确不继续被自己持有，unsafe_unretain 会继续指向对象存在的那个内存，即使是在对象已经销毁之后

​	retain 引用类型，持有对象，声明强引用，指针本来指向的旧的引用对象释放掉后，然后将指针指向新的引用对象，同时将新对象的索引计数加1

​	strong 在ARC中用strong代替retain，

​	copy 建立一个和新对象内容相同且索引计数为1的对象，指针只需向这个对象，然后释放指针之前的旧对象



OC中property 和 instance variable区别

@interface Test: NSObject {

​	NSString *xxx;//实例变量

​	NSInteger bb;//实例变量

}

@property (nonatomic, copy) NSString *name;//属性

属性主要是对实例变量的封装，类对象有一个属性列表来存放类所有的属性

区别：

​	1.实例变量采用硬编码，编译后写死，根据离起始地址的偏移量来访问变量，不可插入新变量，而属性可以在运行时动态添加删除；

​	2.实例变量可以通过@private @public @protected等修饰词来定义变量的作用域，限制变量的访问权限县，而属性不可以。从设计角度来说，属性主要用于和外部类进行访问交互，实例变量主要用于类内部使用；

​	3.属性可以通过三类属性特质分别来帮助内存管理、多线程管理和读写控制，还可以让编译器自动合成存取方法。



什么时候使用weak关键字、weak与assgin的区别

​	1.ARC中避免出现循环引用，会让互相引用的对象中其中一个使用weak弱引用；

​	2.自定义的IBOutlet控件属性一般也用weak

​	assign 与 weak 的区别主要是weak修饰的指针对西乡在对象释放后会自动置为nil，防止悬挂指针，而assign不可以，assign主要用于修饰简单纯量类型，进行简单赋值，weak 只能修饰oc对象，assgin 可以修饰非oc对象



atomic与nonatmoci区别？

​	atomic原子属性修饰的变量setter方法会加锁，防止多线程环境下被多个线程同		时访问造成数据污染，但是会浪费资源，需要额外的资源开销

​	nonatomic非原子性属性修饰的变量setter方法不会被加锁。

​	默认是atomic原子属性

ARC下，不显示制定任何属性关键字时，默认的关键有哪些？

​	1.基本数据类型  atomic、readwrite、assign

​	2.OC普通对象 atomic、readwrite、strong

强引用与弱引用

​	默认指向对象的指针都是strong强引用。当两个或多个对象互相强引用的时候就会出现循环引用，在ARC下 循环引用中的对象将永远得不到销毁而导致内存泄漏，weak属性的弱引用可以打破循环引用从而避免内存泄漏

@synthesize 和 @dynamic 

​	@synthesize 修饰的属性默认会由新系统自动合成setter和getter方法，@synthesize经常用来更改属性的变量名，由系统自动合成默认是_var

​	@dynamic 明确禁止编译器自动合成属性存取方法

​	二者是相互冲突的

@protected、@public、@private

​	@protected 变量对子类可见，对于其他类来说变量是私有的，不可访问

​	@public 公开变量，变量对所有类都是可见的，都可访问

​	@private 变量完全私有化，只对本类可见，子类也不可访问



类中 self.name = @"object" 和 _name = @"object" 区别

​	self.name 会调用setter进行方法赋值，相当于 [self setName:@"object"]

​        _name直接访问实例变量

_block 和 _weak (__block & __weak)



static、extern、const区别
1.const
    const 只修饰自己右边的值
    被const修饰的值是只读的，不可更改
    const int a = 10;// a 是只读变量
    const int *temp;//tem 只读
2.static
    修饰局部变量
        1.延长变量的声明周期，程序结束才会销毁
        2.在同一作用域文件中，只被初始化一次
        3.改变变量的作用域
    修饰全局变量
        1.只要在同一个文件中，变量的声明周期不会改变，也就是指针所指向的地址不会改变
        2.避免重复定义全局变量
3.extern
    声明一个全局变量，不能定义变量
    extern的原理，在当前文件中查找全局变量，如果没有，再去其他文件中查找

组合使用
#define Animation_timer 0.3 // 没有指明常亮类型，如果其余地方有相同名字，会被替换修改，并且不会报错，编译耗时
static const NSTimeInterval kAnimationTimer = 0.3;//不可修改，指明类型，相同名称会报错

extern NSString * const xxxxxx;
NSString *const xxxxxx = @"qqqqqqqqqq";




​       




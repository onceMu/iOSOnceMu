137这个文档最主要的目的是作为ARC的技术规范。

Block是C语言的extension，主要是用于创建匿名函数。用block 指针来交互或者传递对象。block指针就像一个普通的指针。block 可能获得局部变量，block的内存必须动态的生成。

block的初始分配是在 stack//堆栈 中完成的，但是运行时系统提供了一个 block_copy 方法，这个方法要么将当前的block对象拷贝到heap中，同时将引用计数设置为1，然后返回一个新的block指针，要么（如果block指针已经存在于heap中）将block指针的引用计数加1.配对的方法是Block_release,它主要作用是将block 指针的引用计数减1，并且当block指针在堆上的引用计数为0的时候，销毁block指针。

用户可能定义一个 classes，每个classes是个类型，然后指向这个类型的指针是一个对象类型指针，





18612323037	
137505
790826271


pbB@mo3bbEiT2O%PV

手机号13750510086

密码qaz123456

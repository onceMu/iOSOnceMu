高阶函数学习

1.高阶映射

​	映射是在函数的层次上把一个列表变成相同长度的另一个列表，原始列表中的每一个值，在新的列表中都有对应的值。一个高阶函数会返回另外一个函数，而不是一个列表。

2.高阶过滤

​	一个列表通过过滤能返回一个只包含了原列表中符合条件的元素的新列表。如：

​	NSArray *filterArray = [array rx_filterWithBlock:^BOOL (id earch){

​		return ([each integerValue] %2 == 0);

}]; 这个函数可以只返回 %2 == 0的值。

3.高阶折叠

​	Flod 把列表中的所有元素变成一个值。如：

​	NSNumber *sum = [array rx_flodWithBlock^id(id memo, id each){

​		return @([memo integerValue] + [each integeerValue]);

}];这个 函数按顺序执行上述合并规则，memo 参数记录的是上一次合并后的结构。



ReactiveCocoa

<T>流和序列</T>

​	流是值的序列化的抽象，流就像一条水管，值就是流淌在水管中的水，值从管道的一端流入从另一端流出。当值从管道的另一端流出的时候，我们可以读取过去所有的值，甚至是刚刚进入管道的值。流是pull-driven。，

​	RACSequence 可以快速的将数组转化为一个流，RACSequence 是 RACStream的子类。

​	跟数组一样，流中不能包含nil对象，流映射后还是流，RACSequence 返回一个数组array，可以获取到映射后的值。

<p>

NSArray *array = @[@1,@2,@3];

 RACSequence *stream = [array rac_sequence];

NSLog(@"%@",stream);

 [stream map:^id _Nullable(id  _Nullable value) {

​        return @(pow([value integerValue], 2));

 }];

NSLog(@"%@",[stream array]);

输出结果是

1.<RACArraySequence:内存地址>{ name = , array = (**

​    **1,**

​    **2,**

​    **3**

**) }**

2.**(**

​    **1,**

​    **2,**

)   

</p>

正常的映射数组，然后转换成平方的方法。下面可以用合并的方式调用来避免污染变量的作用域。

<p>

NSArray *b = [[[array rac_sequence] map:^id _Nullable(id  _Nullable value) {

​        return @(pow([value integerValue], 2));

​    }]array];

 NSLog(@"%@",b);

输出结果是：

**(**

​    **1,**

​    **4,**

​    **9**

**)**

</p>

上述过程主要的工作是：
1.将数组转化成一个序列类型的流；

2.对流进行映射得到一个新的流；

3.将新的流转换成数组。



序列默认情况西夏延迟加载（懒加载），他们被生成的时候就会提供确切的值，而数组会强制给序列的每一个成员赋值。

RAC过滤方法

<p>

NSLog(@"%@",[[[array rac_sequence]filter:^BOOL(id  _Nullable value) {

​        return [value integerValue] %2 ==0;

  }]array]);

输出结果是：

**(**

​    **2**

**)**

</p>

上述代码将array 转化成一个序列之后对序列进行过滤，然后将过滤出的新的流转换为数组。

RAC将序列流合并成为单个值

<p>

NSLog(@"%@",[[[array rac_sequence] map:^id _Nullable(id  _Nullable value) {

​        return [value stringValue];

​    }]foldLeftWithStart:@"" reduce:^id _Nullable(id  _Nullable accumulator, id  _Nullable value) {

​        return [accumulator stringByAppendingString:value];

​    }]);

输出结果是 123

</p>

上述折叠是左折叠，ReactiveCoCoa有左折叠和右折叠两个概念。左折叠时折叠算法将从头到尾遍历数组，右折叠时折叠算法将从尾到头遍历数组。

​	

<T>信号</T>

​	信号是另外一种类型的流，与序列流相反，信号是push-driven的，新的值能够通过管道发布但不能像pull-driven一样在管道中获取，它们所抽象出来的数据会在未来的某个时间传送过来。

​	pull-driven 与 push-deiven 的区别

​	push-driven：创建信号的时候，信号不会被立即赋值，之后才会被赋值（例如网络请求或者是任意用户输入的结果）

​	pull-driven：在创建信号的同时序列中的值就会被确定下来，我们可以从流中一个个的查询值。

​	信号发送三种类型的值。Next Values代表了下一个发送到管道的值，Error Value代表signal信号无法成功，Completion Values 代表signal信号成功完成。

​	一个事情响应中，一个signal发送了一个Error value或者Completion value之后就不会再发送任何其他的value。错误或者成功将只会发送其中一个，绝不会有两个同时发送的情况。

​	![Class_diagram](/Users/le/Desktop/Class_diagram.png)



<T>订阅</T>

​	当你随时都想知道某一个值的改变时，就需要订阅流。下面是一个常见的UITextFiled的流订阅过程。

​	<p>

​		[self.textField.rac_textSignal subscribeNext:^(NSString * _Nullable x) {

​        NSLog(@"%@",x);

​    }error:^(NSError * _Nullable error) {

​        NSLog(@"%@",error);

​    }completed:^{

​        NSLog(@"完成");

​    }];

​	</p>

当你订阅一个信号时，实际上创建了一个订阅者，订阅者是自动保留的，同时保留订阅的信号。



<T>状态推导</T>

​	RAC()宏，需要两个参数：对象以及整个对象的某个属性的keyPath，比如button的enable属性。然后将表达式右边的值和‘keyPath’做一个单向的绑定，这个值必须是NSObject类型，所以经常要将boolean封装成NSNumber。比如下面的列子：

<p>

//创建一个valid信息，这个信号等于textFiled的本身信号映射出来的，映射的条件是查看输入中是否包含@

​    RACSignal *validSignal = [self.textField.rac_textSignal map:^id _Nullable(NSString * _Nullable value) {

​        return @([value rangeOfString:@"@"].location != NSNotFound);

​    }];

​    //然后将btn的enable属性与 valid 信号绑定

​    RAC(btn,enabled) = validSignal;

​    

​    //将textfiled 的textColor 属性与 valid 信号绑定

​    RAC(self.textField,textColor) = [validSignal map:^id _Nullable(id  _Nullable value) {

​        if ([value boolValue]) {

​            return [UIColor greenColor];

​        }else {

​            return [UIColor redColor];

​        }

​    }];

</p>



<T>指令</T>

​	指令：RACCommand类的代表，创建并订阅动作的信号响应，可以很容易实现一些用户与应用交互时的边界效果。

​	指令的触发通常是UI驱动的，比如说按键的点击等。指令也可以通过信号自动禁用，这种禁用状态呈现在UI上就是禁用与该指令相关联的任何对象。



<T>热信号与冷信号<T>

​	信号是典型的懒鬼。除非有人订阅他们，他们是不会启动并发送的，每增加一个订阅，他们都会重复低多发送一个信号。这种信号成为冷信号。



<T>组播</T>

​	组播是用于多个订阅者共享一个订阅信号的术语。	![multiple_subscriptions](/Users/le/Desktop/multiple_subscriptions.png)

![multicast_connection](/Users/le/Desktop/multicast_connection.png)







<T>RCA开发实战</T>

<p>

\+ (RACSignal *)importPhotos{

​    RACReplaySubject * subject = [RACReplaySubject subject];

​    NSURLRequest * request = [self popularURLRequest];

​    [NSURLConnection sendAsynchronousRequest:request

​                                       queue:[NSOperationQueue mainQueue]

​                           completionHandler:^(NSURLResponse *response, NSData *data, NSError *connectionError){

​                               if (data) {

​                                   id results = [NSJSONSerialization JSONObjectWithData:data options:0 error:nil];

​                                   

​                                   [subject sendNext:[[[results[@"photos"] rac_sequence] map:^id(NSDictionary *photoDictionary){

​                                       FRPPhotoModel * model = [FRPPhotoModel new];

​                                       

​                                       [self configurePhotoModel:model withDictionary:photoDictionary];

​                                       [self downloadThumbnailForPhotoModel:model];

​                                       

​                                       return model;

​                                   }] array]];

​                                   

​                                   [subject sendCompleted];

​                               }

​                               else{

​                                   [subject sendError:connectionError];

​                               }

​                           }];

​    

​    return subject;

​    

}

</p>

上述函数解释：

1.创建一个新的RACReplaySubject，RAC官方文档申明了尽量不使用RACReplaySubject

2.第二创建了一个NSURLRequest来获取 FRPPhotoModel数据

3.发送异步的网络请求，并立即返回RACSubject对象

4.这个RACSubject对象被异步网络请求的回调block捕获，当API接口返回数据时回调block会被调用，然后RACSubkect对象会将结果传送出来，这些值会被我们订阅了RACSubject信号的接收者所接受。



<p>

```
- (void)viewDidLoad{
    [super ViewDidLoad];

    //Configure self
    self.title = @"Popular on 500px";

    //Configure View
    [self.collectionView registerClass:[FRPCell class] forCellWithReuseIdentifier:CellIdentifier];

    //Reactive Stuff
    //第1个RAC注释
    @weakify(self);
    [RACObserver(self, photosArray) subscribeNext:^(id x){
        @strongify(self);
        [self.collectionView reloadData];
    }];

    //Load data
    [self loadPopularPhotos];
}
```

</p>

上述第1个RAC注释中：

​	RACObserver 观察了self，以及self的 属性 photoArray，这个观察会返回一个带属性值的信号，无论这个属性的值怎么变都会及时地通过这个信号反馈出来。

​	subscribeNext: 的block 将捕获其词法范围内的self，造成self和block之间的循环引用。block 被subscribeNext：的返回值，一个RACOberver会自动解除第一个参数的分配，这样self就应该被解除分配，但self被block 强引用，self要被分配的唯一条件是引用计数未0，这样就必须需先解除block的分配，




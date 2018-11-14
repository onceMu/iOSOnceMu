NSInteger是一个类型别名，typedef，在32位系统下是32位的int，在64位系统下是64位的long，int在32位、64位下都是32位

CGFloat也同样，在32位下是32位的float，在64位下是double







键值编码(KVC)比atomic存取器慢的多，

使用[a valueForKey:@"bill"] 调用方式比等效的消息传递[a bill]更慢，并且更不安全，编译器无法确定valueForKey的key字符串是否有效，同时效率也是原来的5%



IMP缓存需要考虑的一种特殊情况是没有接收器，



<https://developer.apple.com/videos/play/wwdc2016/406/>

<https://developer.apple.com/videos/play/wwdc2016/719/>

<https://developer.apple.com/videos/play/wwdc2018/220/>

<https://developer.apple.com/videos/play/wwdc2018/719/>






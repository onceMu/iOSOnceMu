CALayer的shouldRasterize 光栅化

 更新已光栅化的layer，会造成大量的offscreen

不要过度使用，系统限制了缓存大小，2.5 * Screen Size

被光栅化的图片如果超过100ms没有被使用，就会被移除



offscreen rendering为什么会消耗大量资源。

显卡需要另外alloc 一块内存进行渲染，渲染完成之后再绘制到当前屏幕，对于掀开来说，onscreen 和 offscreen 上下文切换是非常昂贵的。

造成Offscreen rendering的原因可能有：

Layer.mask

Layer.masksToBounds = YES

Layer.allowsGroupOpacity = YES or Layer.opacity < 1.0

Layer.shadow

Layeer.shouldResterize = YES

Layer.cornerRadius, Layer.edgeAntialiasingMask layer.allowsEdgeAntialiasing





blending

blending主要是混合像素颜色的计算。

可能造成blending的原因

1.layer(UIView).alpha < 1.0

2.UIImageView 的image 含有alpha 通道



图层如果是不透明的，则系统直接显示该图层的颜色就可以，如果图层是透明的，则需要引入更多的计算，因为需要把下面的图层包括进来，然后进行混合颜色的计算。





core animation 性能检测

1.帧率 fps

2.瓶颈，GPU和CPU 都占有率尽可能低

3.不必要的CPU渲染，尽量不要重写drawRect方法

4.检查过多的offscreen渲染，offscreen会导致GPU需要不断地上下文切换

5.是否有太多的blending，GPU渲染不透明的图层更省资源

6.检查图片的格式是否是常用格式、

7.检查是否有复杂的view图层，尽量不用复杂的图层





HTTPS基础

HTTP明文传输，介于发送端、接收端中间的任意节点都可以知道传输内容是什么。





https://blog.csdn.net/qq_36819141/article/details/75125648



https://halfrost.com/objc_life/



http://blog.leichunfeng.com/blog/2015/06/14/objective-c-method-swizzling-best-practice/



https://github.com/Draveness/analyze/blob/master/contents/objc/%E4%BD%A0%E7%9C%9F%E7%9A%84%E4%BA%86%E8%A7%A3%20load%20%E6%96%B9%E6%B3%95%E4%B9%88%EF%BC%9F.md





http://www.cocoachina.com/ios/20170427/19136.html





http://www.zentut.com/c-tutorial/c-stack-using-pointers/



https://blog.ibireme.com/2015/11/12/smooth_user_interfaces_for_ios/



https://juejin.im/entry/58c75b061b69e6006bea6827



https://juejin.im/entry/57e1f9fc2e958a00547f2461



https://juejin.im/post/5b06578f51882538c150744b



https://casatwy.com/iosying-yong-jia-gou-tan-wang-luo-ceng-she-ji-fang-an.html



http://www.samirchen.com/objective-c-runtime/



https://www.nowcoder.com/discuss/21022?type=0&order=0&pos=92&page=1



https://www.wxz.name/2017/05/17/interview-meituan/



http://www.cocoachina.com/ios/20170511/19252.html



https://draveness.me/cocoapods



https://xiaozhuanlan.com/topic/2601359478



https://www.jianshu.com/p/ace1b422bad4



https://www.jianshu.com/p/8123fc17fe0e



https://github.com/bang590/JSPatch/wiki/JSPatch-%E5%AE%9E%E7%8E%B0%E5%8E%9F%E7%90%86%E8%AF%A6%E8%A7%A3



http://yulingtianxia.com/blog/2014/11/05/objective-c-runtime/



https://www.zybuluo.com/MicroCai/note/64270



http://www.cocoachina.com/ios/20150601/11970.html

http://www.cnblogs.com/kenshincui/p/3931948.html



https://ming1016.github.io/2017/06/20/deeply-ios-performance-optimization/#more



https://renchao0711.github.io/2017/08/29/iOS%E7%BD%91%E7%BB%9C%E4%BC%98%E5%8C%96/

https://www.jianshu.com/p/cd4b445a6a35



http://mrpeak.cn/blog/network-speed/



http://beelearning.cn/2017/11/ASDK/



http://www.cocoachina.com/ios/20180209/22243.html



https://draveness.me/ios-yuan-dai-ma-fen-xi-masonry



http://docs.52im.net/extend/docs/book/tcpip/vol1/14/



https://www.jianshu.com/p/e10e5ca413b7


















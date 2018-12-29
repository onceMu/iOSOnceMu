ViewController 生命周期

1.init(coder)

2.loadView

​	调用一次，只有在viewcontroller被创建的时候才调用。可以重写这个方法，然后自定义view

3.viewDidLoad

​	调用一次，实际上，在这个时候viewcontroller的view 的bounds还没有最后确定下来。

4.viewWillAppear

5.viewDidAppear

6.didReceiveMemoryWarning

7.viewWillDisappear

​	在transition到下一个viewcontroller的时候，当前的viewcontroller从屏幕上移除的时候，这个方法会调用。

8.viewDidDisappear



https://tech.okcupid.com/ios-performance-tutorial-from-okcupid/

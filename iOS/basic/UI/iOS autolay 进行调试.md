iOS autolayout 进行调试

autolayout相关的方法

1.setNeedsLayout:告知页面需要更新，但不会立即更新，执行后会立即调用layoutSubviews

2.layoutIfNeed:告知页面布局立刻更新，如果要立刻生成新的frame要调用此方法，布局动画可以再更新不就后直接使用这个方法让动画生效；

3.layoutSubviews：重写布局

4.setNeedsUpdateConstaints：需要更新约束，不会立刻开始

5.updateConstraintsIfNeeded：立刻更新约束

6.updateConstraints：系统更新约束



断点调试

1.添加add symbolic breakpoint；

2.symbol中添加UIViewAlertForUnsatisfiableConstraints

3.在symbol中添加po [[UIWindow keyWindow] _autolayoutTrace] 或者expr -l objc++ -O -- [[UIWindow keyWindow] _autolayoutTrace]

4.直接po 出内存地址

5.expr 修改颜色等方式，查到相关的视图





layoutSubviews()

对view 和其所有的subview 重新布局（位置，大小）,会给当前的view以及subviews一个位置和大小。这个方法开销很大，因为会在view所有的subviews上调用对应的layoutsubviews方法。

每当需要重新计算view的frames的时候，系统就会调用这个方法。当你需要重新设置frame或者特定设置位置和大小的时候你就需要重写这个方法。但是当view中有视图需要刷新布局的时候不能显示的调用layoutSubviews方法。

当layoutSubviews调用结束的时候，view所在的viewcontroller的viewDidLayoutSubviews将会触发 。由于layoutSubviews方法是在view的layout更新后唯一可靠被调用的，所以你应该将依赖于layout和sizing的逻辑放在viewDidLayoutSubviews方法，而不是放在viewDidLoad 或者 viewDidAppear。



Automatic refresh triggers（自动触发机制）

有很多方法会标记view正在改变layout，因此layoutSubviews方法将会在下一次机会自动调用，即使开发者没有手动做任何操作。

系统会自动触发layoutSubviews的方法：

1.重新给view 赋 大小，resizing

2.添加一个subview

3.用户滚动scrollview（layoutSubviews方法会在scrollview或者其superview 上被调用）

4.用户旋转设备，如果只支持一个方向，则不会触发

5.更新一个视图的约束

上述方法会系统触发layoutSubviews方法，但是也有可以直接触发layoutSubviews

直接触发layoutSubviews的方法：

1.setNeedsLayout（）

​	用最少开销触发layoutSubviews的方式是在view上调用setNeedsLayout，这个方法会向操作系统表明view的layout 需要重新计算。该方法会立即执行和返回，在返回之前并不会更新view的layout，



http://tech.gc.com/demystifying-ios-layout/
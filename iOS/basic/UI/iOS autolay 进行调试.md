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

	用最少开销触发layoutSubviews的方式是在view上调用setNeedsLayout，这个方法会向操作系统表明view的layout 需要重新计算。该方法会立即执行和返回，在返回之前并不会更新view的layout，view将会在下一个update 循环中更新，当系统调用layoutSubViews方法时候，会触发view所有的subviews的layoutSubviews方法
​    
2.layoutIfNeeded()
​       当调用layoutIfNeeded方法的时候，系统如果发现需要更新view的layout，会立	   即执行layoutSubviews方法。如果在setNeedLayout或者其余自动触发系统的方法 之后调用了layoutIfNeeded，view的layoutSubviews方法会调用。如果在调用layotIfNeeded方法之后系统没有标识有方法需要更新view，layoutSubViews方法
不会被调用。如果你在同一个runloop中调用两次layoutIfNeeded方法，并且在这 中间没有更新layout，第二次不会触发layoutSubViews方法。 使用layoutIfNeeded，重新布局和重新绘制所有的subviews会立刻执行，在方法返回之前就会全部执行（只有在执行动画过程中可能列外）。如果你依赖于新的  layout并且不能等到下一个update cycle的时候，这个方法会特别有用。然而，除非是上述所说的情况，你应该调用setNeedsLayout方法，等待这个下一个update  cycle，这样在每一个runloop中，你只需要更新一次view。

​    当在使用动画改变约束的时候，这个方法会特别有用，你应该在动画开始之前的block之前调用layoutIfNeeded方法，来确保所有的layout更新在动画开始之前已经传达，修改约束，然后在动画block中，然后再调用layoutIfNeeded，过度到新的状态。





Display 展示

​	view的展示包括view的属性，但是不涉及view的大小（sizing），位置（positioning）和子view，包含color，texxt，image，以及Core Graphics drawing。Display跟layout 触发update一样，也有两个方法来触发display。

1.draw(_:)

​	OC中的draw（drawRect方法）作用于view的content中，就像layoutSubviews在view的sizing和positioning作用一样。但是，这个并不会触发后续的subview的draw方法。就像la'uyoutSubviews方法一样，永远不要显示的调用draw方法而是应该在runloop循环中在不同点调用触发draw的方法。

2.setNeedsDisplay（）

​	setNeesDisplay（）方法等效于setNeedsLayout方法。这个方法设置了一个内部的flag，view里面有内容需要更新，但是在真正重新绘制view之前就会返回，在下一个update cycle，系统会查找所有被标记过的view，然后调用view的draw方法。如果你只想在下一个update cycle中部分重绘view的content，你可以调用setNeedsDisplay方法，并且传递view在下次update需要的rect。

​	很多时候，更新view的任何UI组件，view都会通过内部自动设置 content updated 标志被标标记为dirty，这样会在下一个update cycle 导致view的content被重新绘制，即使没有显示的调用setNeedsDispalay。然而，如果有属性没有直接绑定到UI组件，但是在每个update都需要view重新绘制，你看定义属性的didSet 属性来观察然后调用setNeeds来触发view的适当更新。



Constraints 约束

在自动布局中，布局和重新绘制view 有三个步骤。

1.updating 约束，系统会在view上计算然设置所有的需要的约束，

2.然后是通过布局，布局引擎计算视图和子视图的frame，然后展示出来

3.The display pass completes the cycle and redraws view's contents if necessary by invoking their draw methods,if they have implemented any.



1.updateConstraints()

​	在使用autolayout中，这个方法能确保动态的改变view的约束。这个方法只能override（重写），永远不要显示的调用。一般来说，你只应该在这个方法中改变需要改变约束的视图的约束。静态约束应该在IB，在视图的初始化方法或者viewDidLoad（）中指定。

​	一般来说，激活或者不激活约束，改变约束的优先级或者约束的常数数值，或者从视图中remove一个子view，都会设置一个内部标记，在下一个update cycle中触发updateConstraints()方法。然而，有些方法可以显示的触发updateConstraints()。

2.`setNeedsUpdateConstraints()`

​	调用setNeedsUpdateConstraints()方法会保证在下一个update cycle中更新约束。这个方法会通过标记一个view的约束已经被更新来触发updateConstraints()方法，这个方法类似于setNeedsDisplay(),setNeedsLayout().

3.`updateConstraintsIfNeeded()`

​	对于使用autolayout的视图，这个方法等效于layoutIfNeeded()。这个方法将会检查 constraint update 标记（通过setNeedsUpdateConstraints()或者invalidateInstrinsicContentSize()方法自动设置），如果系统发现约束需要更新，将会立即触发updateConstraints（）方法，而不是等到run loop结束的时候

4.`invalidateIntrinsicContentSize()`

​	有些使用auto layout的视图，有一个intrinsicContentSize属性，这个属性是视图给其content的自然大小，



layout、display、constraints三者之间的联系

​	layoutSubViews、draw、updateConstraints这些方法都不能直接显示调用，这些方法只有在runloop结束的时候并且发现view被标记过并告知系统view的有些组件需要更新。



|               方法作用               | Layout                                                       |         Display          |                          Constaints                          |
| :----------------------------------: | :----------------------------------------------------------- | :----------------------: | :----------------------------------------------------------: |
|      完成更新(复写，不显示调用)      | Layoutsubviews                                               |           draw           |                      updateConstraints                       |
| 显示标记view在下一个update cycle更新 | setNeedsLayout                                               |     setNeedsDisplay      | setNeedsUpdate    Constraints invalidateIntrinsic ContentSize |
|   如果view 被标记为dirty，立即更新   | layoutIfNeed                                                 |                          |                  updateConstraintsIf Needed                  |
|     哪些操作会导致views updated      | 1.addsubview. 2.ResizingView  3.setFramee            4.scrolls scrollview 5.rotates devic | Changes in view's bounds | Activate/deactivate constraints <br/>Change constraint’s valuer priority 
Remove view from view hierarchy |

http://tech.gc.com/demystifying-ios-layout/ 

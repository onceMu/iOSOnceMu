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
App Programming Guide for iOS

1.The Main Function

​	main function的主要工作是手动控制UIKit framework。UIApplicationMain方法通过创建app的主要对象来处理process（进程），从合适的storeboard文件中加载app的user interface，调用自定义代码来做初始化设置，然后激活app的runloop。需要做的紧紧是提供storeboard 文件和自定义初始化代码。



2.The Struct of an App

	在启动期间，UIApplicationMain会设置几个核心的对象，然后运行app。每个app的核心对象是UIApplication对象，主要作用是在app中促进系统和其它对象的交互。

​	UIAppllcation Object

​		主要管理event loop和其它高层的app行为，同时也报告关键应用转换和一些特殊   事件（推送通知等）给自定义的代理，UIApplication 对象没有子类。

​	App delegate object

​		自定义代码的核心。这个与UIApplication对象配合来处理应用程序初始化、状态转换以及许多高级应用程序事件。

​	Documents 和 Data model 对象

​		主要作用可以看Document-Based App Programming for iOS。

​	View Controller 对象

​	UIWindow object

​	View objects、control objects、layer objects

3.The Main Run Loop

​	App的main run loop关联了用户所有的事件。UIApplication object 在启动的时候设置了main run loop，用于处理事件以及处理view-based interfaces 的更新。main run loop 在app 的main thread 执行。这种行为可以保证可以按照事件的接收顺序串行的处理事件。事件是一个一个触发，然后一个一个分发给main run loop执行。UIApplication 对象是第一个收到事件，并且进一步分发出去。触摸事件通常会被分发给main window处理，window又会把事件分发给touch发生的view。

​	Common type of events for iOS apps

​		Touch、Remote control Shark motion events、Accelerometer Magnetometer Gyroscope、Location、Redraw

​	

​	
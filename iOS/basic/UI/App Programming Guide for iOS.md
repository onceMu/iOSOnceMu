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



​	Execution States for Apps

​	Not running: App未启动或者正在运行但是被系统终止了

​	Inactive: App正在前台运行，但是不接收事件。应用程序可能只是短暂处于这个状态

​	Active：App正在前台运行，并且接收事件。这是App的正常状态

​	Background：App处于后台运行，并且执行代码。

​	Suspended：挂起状态。App处于后台运行，但是不执行代码。系统自动将app置于这个状态，并且在处理之前不会通知App。在挂起状态，app 任然处于内存中，但是不执行任何代码。

​	![high_level_flow_2x](/Users/le/Desktop/high_level_flow_2x.png)

​	



Threads & Concurrency （线程和并发性）

​	系统创建app的主线程，如果需要，可以创建其余的线程没，来perform 另外的任务。

​	在编写线程相关代码的时候需要思考：

​	1.当涉及到views、动画、其余UIKit对象的时候，必须保证是在主线程中执行，但是也有例外，图片相关的操作经常可以在后台线程进行，但是如果有疑问，就假设这些工作是在主线程进行。

​	2.长时间任务（或者可能长时间的任务）则通常是在后台线程运行。涉及到网络请求、文件存储或者大的数据操作都应该使用GCD或者Opreation objects等多线程技术。

​	3.在启动阶段，尽可能的把任务从主线程中移除。在启动阶段、app应该尽可能快的将UI展示出来。唯一的线程任务应该是在主线程中将UI展示出来。所有的tasks都应该异步的执行，当拿到结果后尽快的展示给用户。



Background Execution

​	当用户不适用app的时候，系统会将app移动到background状态。

Executing Finite-Length Tasks

​	每次调用 `beginBackgroundTaskWithName:expirationHandler:` or `beginBackgroundTaskWithExpirationHandler:` 方法的时候会与对应的task生成一个唯一的令牌。当app完成了这个task的时候，必须用对应的token来调用endBackgroundTask: 方法，告知系统task已经完成。在后台线程如果没有调用endBackgroundTask:方法会导致app被终止。如果在task开始的时候提供了一个任务到期的处理方法，系统会调用这个方法给app最后一次机会来完成任务防止App被杀死。

Downloading Content in the Background

​	下载文件的时候，app应该使用NSURLSession对象来进行下载，这样系统可以在app被挂起或者被杀死的时候来控制下载进程。当你为后台进程配置NSURLSession对象的时候，系统会将这个对象放置在单独的进程中并且会在app中返回下载状态。当你的app在下载过程中被杀死的时候，系统会继续在后台下载，当下载完成或者有更多的task需要app来关注的时候会启动app（视情况而定）。

​	为了支持后台下载，必须需适当的配置NSURLSession 对象。具体配置如下：

​	1.通过backgroundSessionConfigurationWithIdentifier: 方法来创建NSURLSessionConfiguration 对象；

​	2.将配置对象的[sessionSendsLaunchEvents](https://developer.apple.com/documentation/foundation/nsurlsessionconfiguration/1617174-sessionsendslaunchevents) 设置为YES；

​	3.如果app在前台开始传输数据，需要将discretionary 属性设置为YES;

​	4.配置configuration对象其余的属性；

​	5.使用configuration对象来创建NSURLSession对象。





What to Do at Launch Time

​	当App在启动的时候（无论是从前台启动还是后台启动），使用app的delegate方法 `application:willFinishLaunchingWithOptions:` and `application:didFinishLaunchingWithOptions:`  来处理如下的事情

​	1.检查lanch options dictionary 对象内容来确认app 为什么被启动，然后适当地进行处理；

​	2.初始化app的最重要的数据对象；

​	3.准备app的window和views 用于展示；

​		1.如果app使用OpenGL ES 来进行绘制，那么不能使用上述方法来准备绘制环境，相对应的，应该讲OpenGL ES 绘制方法写在 applicationDidBecomeActive: 中

​		2.在application:willFinishLaunchingWithOptions: 方法中展示app的window，UIKit 只有在application:willFinishLaunchingWithOptions: 方法返回之后才会将window 可见。

​	在启动阶段应该尽可能的简化工作，启动、初始化、处理事件的时间必须少于5秒中，如果app在5秒钟内没有完成启动任务、系统将会杀死app。因此，任何可能降低启动时间的都应该放在第二线程中。



The Launch Cycle

Launching an app into the foreground![app_launch_fg_2x](/Users/le/Desktop/app_launch_fg_2x.png)



Launching an app into the background

![app_launch_bg_2x](/Users/le/Desktop/app_launch_bg_2x.png)



What to Do When Your App Is Interrupted Temporarily (当应用中断之后应该做什么)

处理中断

![app_interruptions_2x](/Users/le/Desktop/app_interruptions_2x.png)



What to Do When Your App Enters the Foreground

![app_enter_foreground_2x](/Users/le/Desktop/app_enter_foreground_2x.png)
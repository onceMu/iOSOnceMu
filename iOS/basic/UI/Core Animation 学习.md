Core Animation 学习	

CALyaer基础，继承树

​	1.UIView

​		iOS中所有的视图都是从UIView中派生出来的，UIView可以处理触摸事件，可以支持Core Graphics绘图，也可以做变换，或者简单的滑动或渐变的动画。

​	2.CALayer

​		CALayer也是一些被层级关系型树管理的矩形块，同样也可以包含一些内容，管理子图层的位置，同时也有一些方法和熟悉来做动画和变换。CALayer不处理用户交互。

​	3.二者的关系

​		每一个UIView都有一个CALater实例的图层属性。

CALayer属性

​	contents属性	

​	id类型，但是只接收CGImage类型，如果传入UIImage，会显示空白图片，可以用bridge 来桥接UIImage。

​	contentGravity

​	CALayer中与contentModel对应的属性，是contentGravity属性，是一个NSString类型。

​	contentScale

​	浮点型，定义了layer‘s backing image的像素尺寸和UIView大小的比例。

​	maskToBounds

​	UIView 在默认情况下会绘制超过边界的内容和子视图，在CALayer中也是一样的。UIView中使用clipsToBounds来决定是否显示超出边界的视图，在CALayer下用masksToBounds来决定。

​	contentsRect

​	允许在图层边框里显示UIView的一个子域。使用单位坐标，单位坐标指定在0与1 之间，是一个相对值。

​	contentsCenter

​	CGRect对象，定义了一个固定的边框和一个在图层上拉升的区域。



​	自定义绘制

​	-drawRect 方法没有默认的实现，对UIView来说，custom backing image并不是必须的，如果UIView监测到了-drawRect被调用了，UIView就会分配一个CALayer，CALayer的像素尺寸等于视图大小乘以 contensScale。

​	如果没有自定义绘制的任务，就不要在子类中写一个空的-drawRect方法。这样会造成CPU资源和内存的浪费。

​	drawRect 方法在view第一次展示在屏幕上的时候会自动调用。方法会利用Core Graphics去绘制一个backing image，绘制的内容会被缓存下来，直到需要被更新。比如说主动调用setNeedsDisplay方法，或者修改bounds等属性。

​	当图层显示在屏幕上的时候，CALayer并不会自动重绘自己的内容，如果需要重绘，需要开发者手动调用display方法。[CALyaer display]

​	CALayerDelgate 绘制backing image的时候，并没有对超出边界外的内容提供绘制支持。



Layer Geometry 图层几何学

Layout 布局

​	UIView拥有三个最重要的布局属性，frame、bounds、center；

​	CALayer对应的也有三个最重要的属性，frame、bounds、position；

​	frame代表了图层的外部坐标（也就是在父视图上占据的空间）

​	bounds是内部坐标，（{0，0}，通常是图层的左上角）

​	center和position 代表了相对于父视图anchorPoint所在的位置。

​	视图的frame、bounds和center仅仅是存取属性，当你修改视图的frame，实际上是在改变位于视图下方的CALayeer的frame，你不能独立于view的layer来修改viewe的frame。

​	frame并不是一个非常清晰的属性，它是一个虚拟属性，是根据bounds、position、transform计算而来，当其中的任何一个值发生改变，frame都会变化，同样的，改变frame也会影响这些值。

​	anchorPoint 锚点，默认来说，锚点位于图层的中点。layer将会以这个点为中心放置。anchorPoint 没有被UIView接口暴露，与contentsRect和contentsCenter一样，锚点按 单位坐标描述，图层的相对坐标。



​	坐标系

​	layer和view一样，layer在图层树中也是相对于父图层按层级关系放置，一个图层的position依赖于它父图层的bounds。

​	翻转的几何结构

​	在iOS中，一个图层的position位于父视图的左上角，在Mac OS中，通畅位于左下角。Core Animation可以通过geeometryFlipped属性来适配这两种情况。

​	Z坐标系

​	UIView位于一个严格的二维坐标系中，CALayeer位于一个三维空间中。除了position和anchorPoint属性外，CALayer还有另外两个属性，zPosition和anchorPointZ。

​	通常，图层是根据子图层的sublayers出现的顺序来依次绘制的。

Hit Testing

​	CALayer并不关心任何相应链事件，不能直接处理触摸事件或手势。但是可以提供一系列的方法来处理事件：-contaionsPoint 和 -hitTest；

​	-containsPoint，接受一个在本图层坐标系下的CGPoint，如果这个点在图层frame范围内返回YES，这需要把触摸坐标转换到每个图层坐标系下的坐标。

​	-hitTest,同样接收一个CGPoint参数，返回的是图层本身，或者包含这个坐标点的叶子节点图层。



Visual Effects 视图效果

​	圆角 layer cornerRadius

​	CALayer 拥有cornerRadius的属性控制图层角的曲率，浮点数，默认是0（此时是直角），默认情况下，只会影响背景颜色而不影响背景图片或子图层，如果masksToBounds 为YES，图层里面所有东西都会被截取。

​	圆角边框 borderWidth 和 borderColor

​	borderWidth 和 borderColor 共同定义了图层边的绘制样式，这条线（stroke）会沿着图层的bounds绘制，同时也包含图层的角。borderWidth定义边框的粗细，默认是0，borderColor定义边框的颜色，默认是黑色。属于CGColorRef类型，不属于Cocoa的内置对象。

​	阴影 drop shadows

​	给shadowOpacity 一个大于默认值0 的值，阴影就可以显示在任意图层之下，默认是黑色。shadowOffset属性控制这阴影方向和距离，CGSize对象，宽度控制阴影横向的位移，高度控制纵向的位移。默认值是{0,-3}。

​	shadowRadius属性用于控制阴影的模糊度，当值是0的时候，阴影和视图一样有一个非常确定的边界线，当值越来越大的时候，边界线就会越来越模糊和自然。

​	阴影裁剪 shadow clipping

​	不同于layer border属性，layer的阴影继承自内容的外形，而不是根据边界和角半径来确定。

​	shadowPath

​	如果提前知道阴影形状会是什么样子，可以通过提前制定一个shadowPath来提高性能。shadowPath是一个CGPathRef类型，一个指向CGPath的指针。如果是简单的圆或者矩形，用CGPath就可以，但是复杂一点的可以使用CGBezierPath来生成。

​	Layer Masking 图层蒙版

​	通过masksToBounds属性，我们可以沿边界裁剪图形，corneerRadius属性，可以设定一个圆角。mask属性除了静态图之外，还可以通过代码甚至是动画实时生成。

​	Scaling Filters 拉伸过滤

​	

​	Group Opacity

​	CALayer中shouldRasterize 属性，如果被设置为YES，在应用透明度之前，图层及子图层都会被整合成一个整体的图片，这样就解决了透明度混合的问题了。



Transforms 形变

​	仿射变换

​	UIView的transform属性是一个CGAffineTransform类型，用于二维空间做旋转，缩放和平移。

​	数学知识，矩阵乘积。只有当第一个矩阵的列数与第二个矩阵的行数相同时，才能有定义。矩阵A 与矩阵B相乘，可以用如下向量方法来定义

​	A = [a1,1 a1,2 ...

​		a2,1 a2,2...

​		……………..

]

 	B = [b1,1 b1,2 ...

​		b2,2 b2,2

​		………...

]

​	A * B = [ a1,1[b1,1 b2,1 …], a1,2[b1,2 b2,2

​			a2,1[b1,1 b2,1 …],a2,1[b1,2 b2,2...			

]

​	m *n 的矩阵A 与 n * p的矩阵B 相乘之后，会生成m * p 的新矩阵。

​	当对layer做矩阵变换，layer里面的每一个点都相应地被变换，从而形成一个新的四边形形状。CGAffineTransfor中的仿射的意思是无论变化矩阵用什么值，图层中平行的两条线在变换之后任然平行。

​	常用函数：

​	CGAffineTransformMakeRotation(CGFloat angle)//旋转变换

​	CGAffineTransformMakeScale(CGFloat sx, CGFloat sy)//大小变换，x与y的缩放比例

​	CGAffineTransformMakeTranslation(CGFloat tx，CGFloat ty)//



​	混合变换 Combining Transforms

​	Core Graphics 提供了一系列的函数，可以在一个变换的基础上做更深层次的变换，如果做一个既要缩放，又要旋转的变换，就可以使用混合变换。

​	CGAffineTransformRotate(CGAffineTransform t, CGFloat angle)

​	CGAffineTransformScale(CGAffineform t, CGFloat sx, CGFloat sy)

​	CGAffineTransformSlate(CGAffineform t, CGFloat tx,CGFlota ty)



Specialized Layers 专用图层

CAShapeLayer，我们可以不使用图片的情况用CGPath去构造任意形状的阴影。

​	CAShapeLayer是一个通过矢量图形而不是bitmap（位图）来绘制的图层子类。你指定诸如颜色和线宽等属性，用CGPath来定义想要绘制的图形，最后用CAShaperLayer就会自动渲染出来。优点：

​	1.渲染速度快，CAShapeLayer使用了硬件加速，绘制同一图形比Core Graphics快很多；

​	2.高效使用内存，CAShapLayer并不需要像CALayer一样创建一个backing image，所以无论有多大，都不会占用太多的内存；

​	3.不会被图层边界裁剪掉。CAShapeLayer可以在边界之外绘制。

​	4.不会出现像素化。对CAShapeLayer做3D变换时，不会变得像素化。

CATextLayer

​	Core Animations 提供了一个CALayer的子类CATextLayer，它以图层的形式包含了UILabel几乎所有的绘制特性，并且提供了一些新的特性。同时CATextLayer比UILabel渲染要快的多，iOS6之前，UILabel通过WebKit来实现绘制，CATextLayer通过CoreText进行绘制。

​	CATextLayer 的font 属性不是一个UIFont，而是一个CFTypeRef类型，这样可以根据具体需求来决定字体属性应该是用CGFontRef还是CTFontRef（Core Text 类型）。CATextLayer的string 属于id类型，因此可以用NSString，也可以使用NSAttributedString。

Rich Text 富文本

​	

Leading & Kerning 行距和字距

​	由于Core Text 和WebKit 的实现机制不一样，CATextLayer 和UILabel 渲染出的文本行间距和子间距也不是完全相同。



CAGradientLayer 

​	用来生成两种或更多颜色平滑渐变。

​	基础渐变

​	多重渐变

CAReplicatorLayer

​	为了高效生成许多相似的图层。会绘制一个或多个图层的子图层，并在每个复制体上应用不同的变换。

​	Repeating Layers 重复图层



Impkucit Animations 隐式动画

​	Transactions 事务

​	Core Animation 基于一个假设，屏幕上任何的东西都可以（或者可能）做动画。动画不需需要在Core Animation中手动打开，相反需要明确地关闭，否则会一直存在。隐式动画是因为我们并没有指定任何动画类型，我们仅仅改变了一个属性，然后Core Animation来决定如何并且何时去做动画。

​	事务通过CATransaction 类来做管理，CATransaction没有属性或实例方法，并且也不能用+alloc 、-init方法创建，但是可以用+begin和+commit 分别来入栈或出栈。Core Animation在每个run loop周期中自动开始一次新的事务，即使不显式的用begin方法，任何一次run loop循环中属性的改变都会被集中起来，然后做一次0.25秒的动画。（默认是0.25秒，可以修改）。

​	Completion Blocks 动画完成block

​	Layer Actions 图层行为

​	….

Explicit Animations 显式动画

​	属性动画 Property Animations

​	Basic Animations  CABasicAnimations 

​	KeyPath Animations	关键帧动画 CAKeyframeAnimation是另一种UIKit没有暴露出来但功能强大的类。关键帧动画依然作用于单一的一个属性，但是和CABasicAnimation不一样的是，它不限制于设置一个起始和结束的值，而是一连串随意的值来做动画。



第九章 layer time

第十章 easing 缓冲

​	animation velocity  动画速度

​	CADisplayLink  和 NSTimer

​	Run Loop 模式

​	每个添加到run loop的任务都有一个指定了优先级的模式，为了保证用户界面保持平滑，iOS会提供和用户界面相关任务的优先级，而且当UI很活跃的时候会暂停一些别的任务。

​	当UIScrollView 滑动的时候，重绘滚动视图的内容会比别的任务优先级更高，这个时候NSTimer 和网络请求就不会启动。常见的run loop 模式如下：

​	NSDefaultRunLoopMode 标准优先级

​	NSRunLoopCommonModes 高优先级

​	UITrackingRunLoopMode 用于UIScrollView和别的空间的动画



第十一章 性能调优

​	GPU(图形处理器) VS CPU（中央处理器）

​	我们可以认为CPU所做的工作都在软件层面，而GPU在硬件层面。

​	我们可以用软件来做任何事情，但是对图像处理，通常硬件会更快。

​	动画和屏幕上组合的图层实际上被一个单独的进程管理，而不是应用程序。

这就是所谓的渲染服务。iOS5之前SpringBoard、iOS6之后BackBoard。

​	当运行一段动画时，会被四个分离的阶段打破：

​	1.布局，准备视图/图层的层级关系，以及设置图层属性的阶段；

​	2.显示，图层的backing image 被绘制的阶段，可能涉及到 -drawRect，-drawLayer:inContext： 方法的调用路径

​	3.准备，Core Animation 准备发送动画数据到渲染服务的阶段，也是将要执行一些别的事务例如解码动画过程中将要新鲜事的图片的时间点；

​	4.提交，最后的阶段，Core Animation打包所有图层和动画属性，然后通过内部处理通信，发送到渲染服务进行显示。

​	这些是发生在应用程序之内的，动画在屏幕上显示之前任然有更多的工作，一旦打包的图层和动画到达渲染服务进程，会被反序列化来形成另一个渲染树的图层树。使用这个树状结构，渲染服务对动画的每一帧做出如下工作：

​	5.对所有的图层属性计算中间值，设置OpenGL几何形状来执行渲染

​	6.在屏幕上渲染可见的三角形

​	最后两个阶段在动画过程中不停的重复，前5个阶段是在软件层面处理(CPU)，最后一个是被GPU处理。并且真正能控制的，只有前面两个阶段。

​	

​	GPU相关操作

​	GPU用来采集图片和形状，运行变换，应用纹理和混合然后将它们输送到屏幕上。宽泛的说，大多数CALayer 的属性都是通过GPU绘制，比如设置图层背景、边框颜色等。

​	有些情况会降低GPU图层绘制性能

​	1.太多的几何结构，发生在需要太多的三角板来做变换，以应对处理器的栅格化的时候，太多的图层引起CPU的瓶颈，限制了一次展示的图层个数。

​	2.重绘，主要由于重叠的半透明图层引起。GPU的填充比率是有限的（用颜色填充像素的比率），所以需需要避免重绘（每一帧用相同的像素填充多次）发生。

​	3.离屏绘制，这发生在当不能直接在屏幕上绘制，并且必须绘制到离屏图片的上下文中的时候。 离屏绘制发生在基于 CPU 或者是GPU的渲染，或者是为离屏图片分配额外内存，以及切换绘制上下文，都会降低GPU行行行能。对于特定图层效果的使用，圆角、图层遮盖、阴影或者图层光栅化，都会强制Core Animation 提前渲染图层的离屏绘制。并不意味着避免使用这些效果，明白会带来性能负面效果。

​	4.过大的图片，如果绘制超过GPU支持的 2048 * 2048 或者 4096 *4096尺寸的纹理，就必须要用CPU在图层每次显示之前对图片预处理，同样会降低性能。

​	CPU相关操作

​	大多数工作再Core Animation的CPU都发生在动画开始之前，意味着不会影响到帧率，但是会延迟动画开始的时间，界面会看起来比较迟钝。

​	1.布局计算，如果视图过于复杂，当视图呈现或者修改的时候，计算图层帧率会消耗一部分时间，特别是iOS6的自动布局，应该比老版本的自动调整逻辑加强了CPU的工作。

​	2.视图懒加载，iOS只会当视图控制器的视图显示到屏幕上时才会加载它。

​	3.Core Graphic绘制，如果对视图实现了-drawRect方法或者CALayeerDelegate的-drawLayer:inContext：方法，任何绘制都会产生巨大的性能开销，就是一个空的方法都会产生一定的性能开销。为了支持对图层内容的任意绘制，core animation必须创建一个内存中等大小的backing image，绘制结束之后，必须把图片数据通过IPC传到渲染服务器，这样会导致core graphics 绘制变得十分缓慢。

​	4.解压图片，PNG或者JPEG 压缩之后的图片文件比同质量的bitmap小很多。但是在图片绘制到屏幕上之前，必须把图片扩展成完成的未解压的尺寸（通常是 长 * 宽 * 4字节），根据加载图片的方式，第一次对图层内容赋值的时候，直接或者间接使用UIImageView 或者绘制到Core Graphics中，都需要对它解压，当图片较大的时候，占用的时间会很长。

​	当图层被成功打包，发送到渲染服务器之后，CPU任然要做如下工作，为了显示屏幕上的图层，Core Animation必须对渲染树中的每个可见图层通过OpenGL循环转换成纹理三角板，由于GPU并不知道Core Animation图层的任何结构，所以必须由CPU做这些工作。CPU涉及的工作和图层个数成正比，如果应用中有太多图层，就会导致CPU每一帧的渲染都会变慢。



​	I/O相关操作 （input/output）

​	在这部分内容中提到的I/O操作指的是从硬件中存取（例如闪存或者网络接口）。有些动画可能需要从闪存中加载（甚至是从远程URL）。一个典型的例子是两个视图控制器之间的过度效果，这需要从一个nib文件或者从视图控制器中懒加载等方法来过度。

​	I/O 存储比普通的内存访问更慢，所以如果动画设计到I/O，那么问题就会很多。这个时候就需要多线程、缓存、投机加载等方法来解决这个问题。



测量，而不是猜测

真机测试，而不是模拟器

​	模拟器运行在Mac上，电脑的CPU比手机设备上的CPU要快很多，并且Mac上的GPU跟iOS设备完全不一样，模拟器不得不在软件层面（CPU）上模拟设备的GPU，这就意味着GPU相关的操作在模拟器上运行的更慢。

​	性能测试必须用发布模式，而不是调试模式。当用发布环境打包的时候，编译器会引入一系列提高性能的优化，（去掉debug symbols或者移除并重新组织代码）。最好是在支持设备中性能最差的设备上测试。





















​	

​	

​	







点：iOS中最常见的坐标体系，点像是虚拟的像素，也被称为逻辑像素。在标准设备中，一个点就是一个像素，在Retain中，一个点是 2*2 个像素：物理像素坐标并不会用来屏幕布局，
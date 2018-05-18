SDWebImage 源码解读

1.提供UIImageView 的category，支持图片的加载以及缓存管理;

2.异步加载图片

3.异步内存和磁盘图片缓存

4.支持gif

5.支持webp

6.后台图片解压缩处理

7.确保同一个URL地址不会被下载多次

8.确保虚假的URL不会被重复加载

9.确保下载及缓存操作时，主线程不被阻塞



基本知识点

  1.SDWebImageOptions

  2.SDWebImageDownloaderOptions

  3.SDWebImageDownloaderExecutionOrder

  1.SDWebImageOptions 默认是0，然后整个options按照位运算来获取当前的options，图片操作策略

​	SDWebImageRetryFailed = 1 << 0,// 将1 左移0 位，默认情况下，url加载失败之后会进入到黑名单，如果使用整个图片策略，会取消掉放入黑名单中

​	SDWebImageLowPriority = 1 << 1,// 将1 左移1 位，默认情况下，当UI开始交互的时候开始下载图片，例如将下载延迟到scrollview、减速开始

​	SDWebImageCacheMemoryOnly = 1 << 2,// 左2位，这个策略会禁止在disk 上缓存，包含查询和存储

​	SDWebImageProgressiveDownload = 1 << 3, // 允许展示下载过程

​	SDWebImageRefreshCached = 1 << 4, //刷新缓存，即使是缓存中有图片，也会去下载

​	SDWebImageContinueInBackground = 1 << 5,// iOS4 + ，后台下载模式

​	SDWebImageHandleCookies = 1 << 6,// Handles cookies 存储在NSHTTPCookiesStore

​	SDWebImageAllowInvalidSSLCertificates = 1 << 7,//允许不受信任的SSL 下载

​	SDWebImageHighPriority = 1 << 8,// 默认图片是按照线程顺序下载，这个策略会将下载提前到线程之前

​	SDWebImageDelayPlaceholder = 1 << 9,//默认占位图是先展示的，这个策略会将占位图的展示延迟到下载完成

​	SDWebImageQueryDataWhenInMemory = 1 << 13,// 默认情况下，当image在缓存的时候，是没有在disk中查询数据的，这个可以强制允许同时在硬盘和内存缓存中查询数据

​	SDWebImageQueryDiskSync = 1 << 14// 默认情况下，我们同步查询内存缓存，异步查询硬盘缓存，这个策略强制在一个runloop钟同步查询disk缓存

2. SDWebImageDownloaderOptions  图片下载策略

   SDWebImageDownloaderLowPriority = 1 << 0,

   SDWebImageDownloaderProgressiveDownload = 1 << 1,

   SDWebImageDownloaderUseNSURLCache = 1 << 2,// 默认是不使用NSURLCache的，但是这个策略会默认使用NSURLCache

   SDWebImageDownloaderIgnoreCachedResponse = 1 << 3,

   SDWebImageDownloaderContinueInBackground = 1 << 4,

   SDWebImageDownloaderHandleCookies = 1 << 5,

   SDWebImageDownloaderAllowInvalidSSLCertificates = 1 << 6,

   SDWebImageDownloaderHighPriority = 1 << 7,

   SDWebImageDownloaderScaleDownLargeImages = 1 << 8,

3. SDWebImageDownloaderExecutionOrder 下载器执行策略

   SDWebImageDownloaderFIFOExecutionOrder //先进先出

   SDWebImageDownloaderLIFOExecutionOrder//后进先出



入口函数

​	(void)sd_setImageWithURL:(nullable NSURL *)url

​	(void)sd_setImageWithURL:(nullable NSURL *)url placeholderImage:(nullable UIImage *)placeholder

​	(void)sd_setImageWithURL:(nullable NSURL *)url placeholderImage:(nullable UIImage *)placeholder options:(SDWebImageOptions)options

​	(void)sd_setImageWithURL:(nullable NSURL *)url completed:(nullable SDExternalCompletionBlock)completedBlock

​	(void)sd_setImageWithURL:(nullable NSURL *)url placeholderImage:(nullable UIImage *)placeholder completed:(nullable SDExternalCompletionBlock)completedBlock

​	(void)sd_setImageWithURL:(nullable NSURL *)url placeholderImage:(nullable UIImage *)placeholder options:(SDWebImageOptions)options completed:(nullable SDExternalCompletionBlock)completedBlock

SDWebImage 含有6个入口函数，相当于使用者只需要知道这几个函数就可以使用完整的图片下载。

入口函数内部都会调用同一个方法

​	 (void)sd_internalSetImageWithURL:(nullable NSURL *)url

​                  placeholderImage:(nullable UIImage *)placeholder

​                           options:(SDWebImageOptions)options

​                      operationKey:(nullable NSString *)operationKey

​                     setImageBlock:(nullable SDSetImageBlock)setImageBlock

​                          progress:(nullable SDWebImageDownloaderProgressBlock)progressBlock

​                         completed:(nullable SDExternalCompletionBlock)completedBlock

​                           context:(nullable NSDictionary *)context {



}





​	
//
//  OHBaseNetwork.h
//  OneHome
//
//  Created by le on 2017/9/18.
//  Copyright © 2017年 guoqiang. All rights reserved.
//

#import <AFNetworking/AFNetworking.h>


/**
 HTTP请求方法

 - RequestMethodGet: GET
 - RequestMethodPost: POST
 - RequestMethodHead: HEAD
 - RequestMethodPut: PUT
 - RequestMethodDelete: DELETE
 - RequestMethodPatch: PATCH
 */
typedef NS_ENUM(NSInteger , RequestMethod) {
    RequestMethodGet = 0,
    RequestMethodPost,
    RequestMethodHead,
    RequestMethodPut,
    RequestMethodDelete,
    RequestMethodPatch
};


/**
 接口返回的数据类型

 - RequestSerializerTypeHTTP: HTTP
 - RequestSerializerTypeJSON: JSON
 */
typedef NS_ENUM(NSInteger , RequestSerializerType) {
    RequestSerializerTypeHTTP = 0,
    RequestSerializerTypeJSON,
};

/**
 网络请求成功block回调

 @param requestURL 接口地址
 @param responseObject 返回信息
 */
typedef void(^ResponseSuccess)(NSString *requestURL, id responseObject);


/**
 网络请求失败block回调

 @param error 错误信息
 @param responseObject 具体返回信息
 */
typedef void(^ResponseFailed)(NSError *error, id responseObject);


static NSString * const kBaseStatus = @"status";
static NSString * const kBaseStatusReason = @"status_reason";
static NSString * const kBaseStatusCode = @"status_code";
static NSString * const kCommonRequestParameter = @"param";
static NSString * const kBaseRequestParameter = @"systemParam";

//NSDictionary* status = dict[@"status"];
////    self.message = EncodeStringFromDic(status,@"status_reason");
////    self.code = EncodeStringFromDic(status,@"status_code");

@interface OHBaseNetwork : AFHTTPSessionManager

/**
 请求的字典参数
 */
@property(nonatomic, strong) NSMutableDictionary *queryDictionary;

/**
 自定义的网路线程
 */
@property (nonatomic, strong) dispatch_queue_t requestTaskQueue;

/**
 聊天消息轮训线程
 */
@property (nonatomic, strong) dispatch_queue_t messageTaskQueue;



@property (nonatomic, assign) BOOL isNeedAccessToken;

/**
 请求的URL

 @return 当前网络请求的URL方法
 */
- (NSString *)requestURLString;


/**
 Http请求的方法

 @return HTTP操作方法
 */
- (RequestMethod)requestMethod;


/**
 请求的SerializerType

 @return 请求的SerializerType
 */
- (RequestSerializerType)requestSerializerType;

/**
 在HTTP报头添加的自定义参数

 @return HTTP body 自定义参数
 */
- (NSDictionary *)requestHeaderFieldValueDictionary;


/**
 请求的连接超时时间，默认为120秒

 @return 超时时间
 */
- (NSTimeInterval)requestTimeoutInterval;


/**
 查询当前是否有网络请求在执行

 @return YES OR NO
 */
- (BOOL)isExecuting;


/**
 取消网络请求,取消所有的网络请求
 */
- (void)cancel;

/**
 构造AFHTTPRequestSerializer

 @return AFHTTPRequestSerializer
 */
- (AFHTTPRequestSerializer *)bulidCustomSerializer;

/**
 获取缓存数据

 @param success 成功
 @param failure 失败
 */
- (void)getResponseObjectFromCacheWithSuccess:(ResponseSuccess)success
                                      failure:(ResponseFailed)failure;



/**
 请求成功后的处理方法

 @param responseObject 网络返回数据
 @param success 成功
 @param failure 失败
 */
- (void)responseSuccessHandle:(id)responseObject
                      success:(ResponseSuccess)success
                      failure:(ResponseFailed)failure;

/**
 *  URLDecoder
 *
 *  @param str str description
 *
 *  @return return URLDecodedString
 */
-(NSString *)URLDecodedString:(NSString *)str;


/**
 *  GET网络请求(block返回)
 *
 *  @param URLString  接口地址（不包含URL_HOST）
 *  @param parameters 请求参数
 *  @param success        success block返回
 *  @param failure        failure block返回
 */
- (void)requestGETwithUrl:(NSString *)URLString
               parameters:(NSMutableDictionary*)parameters
                  success:(ResponseSuccess)success
                  failure:(ResponseFailed)failure;

/**
 *  POST网络请求(block返回)
 *
 *  @param URLString  接口地址（不包含URL_HOST）
 *  @param parameters 请求参数
 *  @param success        success block返回
 *  @param failure        failure block返回
 */
- (void)requestPOSTwithUrl:(NSString *)URLString
                parameters:(NSMutableDictionary*)parameters
                   success:(ResponseSuccess)success
                   failure:(ResponseFailed)failure;



/**
 聊天相关线程，本来可以在.m中再抽象一层，但是偷懒，就copy了一个新函数

 @param URLString URL地址
 @param parameters 参数
 @param success 成功
 @param failure 失败
 */
- (void)requestPostMessageURL:(NSString *)URLString
                   parameters:(NSMutableDictionary *)parameters
                      success:(ResponseSuccess)success
                       failed:(ResponseFailed)failure;




/**
 上传文件block回调
 
 @param URLString  上传url地址
 @param upLoadData 上传二进制流
 @param parameters 参数
 @param filePath   文件地址
 @param success    成功
 @param failed     失败
 */
- (void)requestUpLoadFileWithURLString:(NSString *)URLString
                            upLoadData:(NSData *)upLoadData
                            parameters:(NSMutableDictionary *)parameters
                              filePath:(NSString *)filePath
                               success:(ResponseSuccess)success
                                failed:(ResponseFailed)failed;

/**
 *  获取NSArray的加密校验串
 *
 *  @param array 根据接口verifyCode的参数顺序初始化的NSArray
 *
 *  @return 返回verifyCode
 */
-(NSString*) getVerifyCodeByArray:(NSArray*)array;

- (void)addHttpHeader;
- (NSMutableDictionary *)parserError:(NSError *)error;


/**
 取消特定的接口请求

 @param apiName apiName
 */
- (void)cancelSepcialTaskWithApiName:(NSString *)apiName;
@end

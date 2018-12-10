//
//  OHBaseNetwork.m
//  OneHome
//
//  Created by le on 2017/9/18.
//  Copyright © 2017年 guoqiang. All rights reserved.
//

#import "OHBaseNetwork.h"
#import "NSDictionary+String.h"
#import "NSString+Additions.h"
#import "Utils.h"


@implementation OHBaseNetwork

- (instancetype)init {
    return [self initWithBaseURL:[NSURL URLWithString:@"back210.onehome.me/ios"]];
}


- (instancetype)initWithBaseURL:(NSURL *)url {
    return [self initWithBaseURL:url sessionConfiguration:nil];
}

- (instancetype)initWithSessionConfiguration:(NSURLSessionConfiguration *)configuration {
    return [self initWithBaseURL:[NSURL URLWithString:@"back210.onehome.me/ios"] sessionConfiguration:configuration];
}

- (instancetype)initWithBaseURL:(NSURL *)url
           sessionConfiguration:(NSURLSessionConfiguration *)configuration {
    
    self = [super initWithBaseURL:(NSURL *)url sessionConfiguration:(NSURLSessionConfiguration *)configuration];
    
    if (self) {
        self.responseSerializer.acceptableContentTypes=[NSSet setWithObjects:@"application/json", @"text/json", @"text/javascript",@"text/html",@"text/plain", nil];
        _queryDictionary = [[NSMutableDictionary alloc]initWithCapacity:1];
        _requestTaskQueue = dispatch_queue_create("oneHomeNetservice.queue", NULL);
        _messageTaskQueue = dispatch_queue_create("oneHomeMessageNetservice.queue", NULL);
        [self setTimeoutInterval];
        _isNeedAccessToken = YES;
        self.securityPolicy.allowInvalidCertificates = YES;
        self.securityPolicy.validatesDomainName = NO;
    }
    return self;
}

- (void)setTimeoutInterval {
    [self.requestSerializer willChangeValueForKey:@"setTimeoutInterval"];
    self.requestSerializer.timeoutInterval = self.requestTimeoutInterval;
    [self.requestSerializer didChangeValueForKey:@"setTimeoutInterval"];
}

#pragma mark  请求自定义相关方法

- (BOOL)isExecuting {
    return self.operationQueue.operationCount >0;
}

- (void)cancel {
    [self.session getTasksWithCompletionHandler:^(NSArray<NSURLSessionDataTask *> * _Nonnull dataTasks, NSArray<NSURLSessionUploadTask *> * _Nonnull uploadTasks, NSArray<NSURLSessionDownloadTask *> * _Nonnull downloadTasks) {
        if (dataTasks.count > 0) {
            for(NSURLSessionDataTask *task in dataTasks) {
                [task cancel];
            }
        }
        if (uploadTasks.count > 0 ) {
            for(NSURLSessionDataTask *task in uploadTasks) {
                [task cancel];
            }
        }
    }];
    [self.operationQueue cancelAllOperations];
    
//    [self.requestTaskQueue c]
}

- (void)cancelSepcialTaskWithApiName:(NSString *)apiName {
//    if ([NSString isBlankString:apiName]) {
//        return;
//    }
//    NSString *urlString = nil;
//    NSMutableString *baseURL = [NSMutableString stringWithFormat:@"%@",self.baseURL.absoluteString];
//    if (![baseURL hasSuffix:@"/"]) {
//        [baseURL appendString:@"/"];
//    }
//    if ([OHApiModel sharedInstance].networkType != NetworkTypeTest) {
//        urlString =  [NSString stringWithFormat:@"https://%@%@", baseURL, apiName];
//    }else {
//        urlString = [NSString stringWithFormat:@"http://%@%@", baseURL, apiName];
//    }
//    NSURL *url = [NSURL URLWithString:urlString];
//    [self.session getTasksWithCompletionHandler:^(NSArray<NSURLSessionDataTask *> * _Nonnull dataTasks, NSArray<NSURLSessionUploadTask *> * _Nonnull uploadTasks, NSArray<NSURLSessionDownloadTask *> * _Nonnull downloadTasks) {
//        if (dataTasks.count > 0) {
//            for(NSURLSessionDataTask *task in dataTasks) {
//                if ([task.currentRequest.URL isEqual:url]) {
//                    [task cancel];
//                    break;
//                }
//            }
//        }
//    }];
}

- (RequestMethod)requestMethod {
    return RequestMethodPost;
}

/* 请求的SerializerType */
- (RequestSerializerType)requestSerializerType {
    return RequestSerializerTypeJSON;
}

/* 请求的连接超时时间，默认为120秒 */
- (NSTimeInterval)requestTimeoutInterval {
    return 60;
}

/* 构造缓存的key */
- (NSString *)buildCacheKey {
    NSMutableString *cacheKey = [[NSMutableString alloc] init];
    [cacheKey appendString:[self requestURLString]];
    if ([self.queryDictionary count] > 0) {
        [cacheKey appendString:[self buildGetRquestURL]];
    }
    return [cacheKey md5];
}

#pragma mark 构造请求url

/**
 *  构造请求url
 *
 *  @return 域名+请求方法名
 */
- (NSString *)requestURLString {
//    NSString *requestMethod = [NSString stringWithFormat:@"%@",[self.queryDictionary objectForKey:REUQEST_METHOD]];
    NSMutableString *urlString = [[NSMutableString alloc] initWithCapacity:1];
//    [urlString appendFormat:@"%@",[self.queryDictionary objectForKey:REUQEST_API_URL]];
//    [urlString appendString:requestMethod];
    return urlString;
}

/**
 *  构造get方式的请求url
 *
 *  @return 将所有请求参数按key=value的方式构造成一个字符串
 */
- (NSString *)buildGetRquestURL {
    NSMutableString *urlString = [[NSMutableString alloc] init];
    for (NSString *key in self.queryDictionary.allKeys) {
        [urlString appendString:[NSString stringWithFormat:@"%@=%@&",key,[self.queryDictionary objectForKey:key]]];
    }
    return urlString;
}

#pragma mark 创建头部参数

// 把所有参数签名的MD5值
- (NSString *)buildSignture {
    NSEnumerator *enumerator = [self.queryDictionary keyEnumerator];
    NSMutableString *signture = [NSMutableString stringWithCapacity:1];
    NSString *theKey;
//    [signture appendString:ACCESS_KEY];
    while (theKey = [enumerator nextObject]) {
        [signture appendString:theKey];
    }
//    [signture appendString:ACCESS_KEY];
    return [signture md5];
}


// 在HTTP报头添加的自定义参数
- (NSDictionary *)requestHeaderFieldValueDictionary {
    //用户cookie
    NSMutableString *session = [NSMutableString stringWithCapacity:1];
   /* if (self.gdm.isLogin) {
        [session appendFormat:@"Token %@",self.gdm.accessToken];
    }
    */
    
    //userAgent
    NSString *appVersion = [[[NSBundle mainBundle]infoDictionary] objectForKey:@"CFBundleShortVersionString"];
    NSMutableString *userAgent = [NSMutableString stringWithCapacity:1];
    [userAgent appendString:@"oneHome"];
    [userAgent appendString:@" "];
    [userAgent appendString:appVersion];
    NSDictionary *dict = [NSDictionary dictionaryWithObjectsAndKeys:
                          //                          [self buildSignture],@"signature",
                          session,@"Authorization",
                          //                          userAgent,@"User-Agent",
                          nil];
    return dict;
}

#pragma mark 自定义请求方法

/* 构造AFHTTPRequestSerializer */
- (AFHTTPRequestSerializer *)bulidCustomSerializer {
    AFHTTPRequestSerializer *serializer = [AFHTTPRequestSerializer serializer];
    [serializer setValue:@"application/x-www-form-urlencoded; charset=UTF-8" forHTTPHeaderField:@"Content-Type"];
    serializer.timeoutInterval = [self requestTimeoutInterval];
    
    // 构造头参数
    NSDictionary *headerParamers = [self requestHeaderFieldValueDictionary];
    for (NSString *key in headerParamers.allKeys) {
        [serializer setValue:[headerParamers objectForKey:key] forHTTPHeaderField:key];
    }
    return serializer;
}

/* 无网络从缓存取数据*/
- (void)getResponseObjectFromCacheWithSuccess:(ResponseSuccess)success
                                      failure:(ResponseFailed)failure {
//    NSString *requestMethod = [self.queryDictionary objectForKeyedSubscript:REUQEST_METHOD];
//    
//    NSString *cacheKey = [self buildCacheKey];
//    
//    id responseObject = [[EGOCache globalCache] objectForKey:cacheKey];
//    if (responseObject && success) {
//        success(nil, responseObject);
//    }else{
//        failure(nil, responseObject);
//    }
//    [self.queryDictionary removeAllObjects];
}


/* 请求成功后的处理方法 */
- (void)responseSuccessHandle:(id)responseObject
                      success:(ResponseSuccess)success
                      failure:(ResponseFailed)failure {
//    NSString *requestMethod = [self.queryDictionary objectForKeyedSubscript:REUQEST_METHOD];
    
    //判断是否添加缓存
//    if (self.isNeedCache) {
//        [[EGOCache globalCache] setObject:responseObject forKey:[self buildCacheKey]];
//    }
    //系统菊花转
    [[UIApplication sharedApplication] setNetworkActivityIndicatorVisible:NO];
    
    if ([responseObject isKindOfClass:[NSDictionary class]] && [(NSDictionary *)responseObject objectForKey:@"status"]) {
        NSString *code = [[(NSDictionary *)responseObject objectForKey:@"status"] objectForKey:@"status_code"];
        if ([code isKindOfClass:[NSNumber class]]) {
            code = code.description;
        }
        //0的时候是请求成功、其余情况是失败情况
        if ([code isEqualToString:@"0"]) {
            if (success) {
                success(nil, responseObject);
                [self.queryDictionary removeAllObjects];
            }
        }else{
            if (failure) {
                if ([code isEqualToString:@"101"]) {
                    //101 时候清楚掉所有的存储逻辑
                   
                }
                
                NSString *errorInfo = [[(NSDictionary *)responseObject objectForKey:@"status"] objectForKey:@"status_reason"];
                if (errorInfo.length > 0) {
                    NSError *error = [NSError errorWithDomain:errorInfo code:[code integerValue] userInfo:nil];
                    failure(error, responseObject);
                }else {
                    failure(nil, responseObject);
                }
                
            }
        }
    }
}


/**
 *  URLDecoder
 *
 *  @param str str
 *
 *  @return return value description
 */
- (NSString *)URLDecodedString:(NSString *)str{
    NSString *decodedString=(__bridge_transfer NSString *)CFURLCreateStringByReplacingPercentEscapesUsingEncoding(NULL, (__bridge CFStringRef)str, CFSTR(""), CFStringConvertNSStringEncodingToEncoding(NSUTF8StringEncoding));
    
    return decodedString;
}


- (void)requestGETwithUrl:(NSString *)URLString
               parameters:(NSMutableDictionary *)parameters
                  success:(ResponseSuccess)success
                  failure:(ResponseFailed)failure{
    
    dispatch_async(self.requestTaskQueue, ^{
        
        NSMutableDictionary *finalParameters = parameters;
        if (finalParameters == nil) {
            finalParameters = [[NSMutableDictionary alloc] init];
        }
        [self addHttpHeader];
        //添加公参
        NSMutableDictionary *parames = [self addCommonParamsTo:finalParameters];
        
        NSString *url = nil;
        NSMutableString *baseURL = [NSMutableString stringWithFormat:@"%@",self.baseURL.absoluteString];
        if (![baseURL hasSuffix:@"/"]) {
            [baseURL appendString:@"/"];
        }

        url =  [NSString stringWithFormat:@"https://%@%@", baseURL, URLString];

        

//        [GetMessageClass suspendMessageTask];
        [self GET:url parameters:parames progress:^(NSProgress * _Nonnull uploadProgress) {
            
            
        }  success:^(NSURLSessionDataTask *task, id responseObject) {
 
            [self responseSuccessHandle:responseObject success:success failure:failure];
            
        } failure:^(NSURLSessionDataTask *task, NSError *error) {
            

            NSMutableDictionary *parames = [self parserError:error];
            if (failure) {
                failure(error,parames);
            }
            
        }];
        
    });
}

- (void)requestPostMessageURL:(NSString *)URLString
                   parameters:(NSMutableDictionary *)parameters
                      success:(ResponseSuccess)success
                       failed:(ResponseFailed)failure {
    dispatch_async(self.messageTaskQueue, ^{
        //        NSAssert([parameters isKindOfClass:[NSMutableDictionary class]] || parameters == nil, @"必须是可变字段或者为空");
        //如果上一级传过来的是个不可变字典
        NSMutableDictionary *finalParameters = parameters;
        
        
        if (finalParameters == nil) {
            finalParameters = [NSMutableDictionary dictionaryWithCapacity:1];
        }
        
        [self addHttpHeader];
        //添加公参
        NSMutableDictionary *parames = [self addCommonParamsTo:finalParameters];
        
        NSString *url = nil;
        NSMutableString *baseURL = [NSMutableString stringWithFormat:@"%@",self.baseURL.absoluteString];
        if (![baseURL hasSuffix:@"/"]) {
            [baseURL appendString:@"/"];
        }
        url =  [NSString stringWithFormat:@"https://%@%@", baseURL, URLString];
        NSString *urls = [NSString stringWithFormat:@"http://%@/%@?%@", @"", URLString, [parames urlEncodedKeyValueString]];
        
        
        [self POST:url parameters:parames progress:^(NSProgress * _Nonnull uploadProgress) {
            
        }  success:^(NSURLSessionDataTask *task, id responseObject) {
            
            [self responseSuccessHandle:responseObject success:success failure:failure];
            
        } failure:^(NSURLSessionDataTask *task, NSError *error) {
            
            //            NSMutableDictionary *parames = [self parserError:error];
            
            NSMutableDictionary *parames = [NSMutableDictionary dictionaryWithCapacity:1];
            NSMutableDictionary *dic = [NSMutableDictionary dictionaryWithCapacity:1];

            if (error.userInfo) {
                if ([error.userInfo objectForKey:@"NSLocalizedDescription"]) {
                    [dic setObject:[error.userInfo objectForKey:@"NSLocalizedDescription"] forKey:@"status_reason"];
                }else {
                    [dic setObject:@"网络请求错误" forKey:@"status_reason"];
                }
            }else {
                [dic setObject:@"网络请求错误" forKey:@"status_reason"];
            }
            [parames setObject:dic forKey:@"status"];
            
            if (failure) {
                failure(error,parames);
            }
            
        }];
        
    });
}

- (void)requestPOSTwithUrl:(NSString *)URLString
                parameters:(NSMutableDictionary *)parameters
                   success:(ResponseSuccess)success
                   failure:(ResponseFailed)failure {
    
    dispatch_async(self.requestTaskQueue, ^{
//        NSAssert([parameters isKindOfClass:[NSMutableDictionary class]] || parameters == nil, @"必须是可变字段或者为空");
        //如果上一级传过来的是个不可变字典
        NSMutableDictionary *finalParameters = parameters;

        
        if (finalParameters == nil) {
            finalParameters = [NSMutableDictionary dictionaryWithCapacity:1];
        }
        
        [self addHttpHeader];
        //添加公参
        NSMutableDictionary *parames = [self addCommonParamsTo:finalParameters];
        
        NSString *url = nil;
        NSMutableString *baseURL = [NSMutableString stringWithFormat:@"%@",self.baseURL.absoluteString];
        if (![baseURL hasSuffix:@"/"]) {
            [baseURL appendString:@"/"];
        }
        url =  [NSString stringWithFormat:@"https://%@%@", baseURL, URLString];
        
        [self POST:url parameters:parames progress:^(NSProgress * _Nonnull uploadProgress) {
            
        }  success:^(NSURLSessionDataTask *task, id responseObject) {
            
            [self responseSuccessHandle:responseObject success:success failure:failure];
            
        } failure:^(NSURLSessionDataTask *task, NSError *error) {
            
            
            NSMutableDictionary *parames = [NSMutableDictionary dictionaryWithCapacity:1];
            NSMutableDictionary *dic = [NSMutableDictionary dictionaryWithCapacity:1];
            if (error.userInfo) {
                if ([error.userInfo objectForKey:@"NSLocalizedDescription"]) {
                    [dic setObject:[error.userInfo objectForKey:@"NSLocalizedDescription"] forKey:@"status_reason"];
                }else {
                   [dic setObject:@"网络请求错误" forKey:@"status_reason"];
                }
            }else {
                [dic setObject:@"网络请求错误" forKey:@"status_reason"];
            }
            [parames setValue:dic forKey:@"status"];
            
            if (failure) {
                failure(error,parames);
            }
            
        }];
        
    });
    
}




- (NSMutableDictionary *)parserError:(NSError *)error {
    NSMutableDictionary *parames = nil;
    if ([error.userInfo objectForKey:AFNetworkingOperationFailingURLResponseDataErrorKey]) {
        id object = [error.userInfo objectForKey:AFNetworkingOperationFailingURLResponseDataErrorKey];
        if ([object isKindOfClass:[NSData class]]) {
            parames = [NSJSONSerialization JSONObjectWithData:object options:NSJSONReadingAllowFragments error:nil];
        }else if ([object isKindOfClass:[NSError class]]) {
            [self parserError:object];
        }else {
            [parames setObject:@"网络请求失败" forKey:@"reason_status"];
        }
    }
    if ([error.userInfo objectForKey:@"NSUnderlyingError"]) {
        id object = [error.userInfo objectForKey:@"NSUnderlyingError"];
        if ([object isKindOfClass:[NSData class]]) {
            parames = [NSJSONSerialization JSONObjectWithData:object options:NSJSONReadingMutableLeaves error:nil];
        }else if ([object isKindOfClass:[NSError class]]) {
            NSError *err = (NSError *)object;
    
            if ([err.userInfo objectForKey:AFNetworkingOperationFailingURLResponseDataErrorKey]) {
                id xxx = [err.userInfo objectForKey:AFNetworkingOperationFailingURLResponseDataErrorKey];
                if ([xxx isKindOfClass:[NSData class]]) {
                    NSString *dataString = [[NSString alloc] initWithData:xxx encoding:NSUTF8StringEncoding];
                    [parames setObject:dataString forKey:@"reason_status"];
                }
            }
        }else {
            [parames setObject:@"网络请求失败" forKey:@"reason_status"];
        }
    }
    return parames;
}


/**
 设置请求参数头
 */
- (void)addHttpHeader {
    NSDictionary *headerParamers = [self requestHeaderFieldValueDictionary];
    for (NSString *key in headerParamers.allKeys) {
        [self.requestSerializer setValue:[headerParamers objectForKey:key] forHTTPHeaderField:key];
    }
}

/**
 *  为网络请求params添加公参
 *
 *  @param params 网络请求params
 */
- (NSMutableDictionary *)addCommonParamsTo:(NSMutableDictionary*)params {
    NSMutableDictionary *dict = [NSMutableDictionary dictionaryWithCapacity:1];

    //某些特定操作会出现tokenSign
    if ([params objectForKey:@"tokenSign"] && [params isKindOfClass:[NSMutableDictionary class]]) {
        [params removeObjectForKey:@"tokenSign"];
    }
    
    NSMutableDictionary *systemParames = [NSMutableDictionary dictionaryWithCapacity:1];
    [systemParames addEntriesFromDictionary:[Utils systemParamForBack]];
    NSTimeInterval timeStamp = [[NSDate date] timeIntervalSince1970] * 1000;
    [systemParames setObject:[NSString stringWithFormat:@"%.0f",timeStamp] forKey:@"timestamps"];
    NSString *md5 = [Utils tokenSign:params systemParames:systemParames];
    [params setObject:md5 forKey:@"tokenSign"];
    
    [dict setObject:[systemParames jsonString] forKeyedSubscript:kBaseRequestParameter];
    [dict setObject:[params jsonString] forKey:kCommonRequestParameter];
    
    
    
    return dict;
}

- (NSString*)getVerifyCodeByArray:(NSArray*)array {
    NSMutableString *buff = [[NSMutableString alloc] initWithCapacity:32];
    
    for (NSString *str in array) {
        [buff appendString:str];
    }
    
    NSString *result = [buff stringByReplacingOccurrencesOfString:@" " withString:@""];;
    
    
    return [result md5];
}


@end

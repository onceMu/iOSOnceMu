//
//  HTTP.h
//  Sort
//
//  Created by le on 2018/11/23.
//  Copyright © 2018 le. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface HTTP : NSObject
- (void)OSIModel;//OSI 模型
- (void)tcpipProtocol;
- (void)threeHandshaking;//三次握手
- (void)ipProtocol;
- (void)dnsProtocol;
- (void)sevenSystem;//七层模型
- (void)httpAndHttps;//http与https关系
- (void)preventHttpHijacking;//防劫持
- (void)httpRSA;//http相关加密

@end

NS_ASSUME_NONNULL_END

//
//  Utils.h
//  AppPrototype
//
//  Created by ChenLiangwei on 15/10/10.
//  Copyright © 2015年 FantasyD. All rights reserved.
//

#import <Foundation/Foundation.h>

FOUNDATION_EXPORT BOOL preferedChineseTranditional();

@interface Utils : NSObject

+ (NSString *)deviceType;
+ (NSDictionary *)systemParam;
+ (NSDictionary *)systemParamForBack;
+ (NSArray *)areaCodes;

+ (NSString *)tokenSign:(NSDictionary *)paramames
          systemParames:(NSDictionary *)systemParames;
+ (BOOL)checkDeviceIsiPad;

+ (NSString *)convertCurrentLangugae:(NSString *)language;

@end

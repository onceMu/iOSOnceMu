//
//  NSDictionary+String.h
//  OneHome
//
//  Created by le on 2017/9/18.
//  Copyright © 2017年 guoqiang. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSDictionary (String)

- (NSString *)jsonString;

-(NSString*) urlEncodedKeyValueString;

-(NSString*) jsonEncodedKeyValueString;

-(NSString*) plistEncodedKeyValueString;

@end

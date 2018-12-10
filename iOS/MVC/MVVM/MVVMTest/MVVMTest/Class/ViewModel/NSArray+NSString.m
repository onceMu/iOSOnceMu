//
//  NSArray+NSString.m
//  OneHome
//
//  Created by le on 2017/12/4.
//  Copyright © 2017年 guoqiang. All rights reserved.
//

#import "NSArray+NSString.h"

@implementation NSArray (NSString)

- (NSString *)jsonString {
    NSString *jsonString = nil;
    NSError *error;
    NSData *jsonData = [NSJSONSerialization dataWithJSONObject:self
                                                       options:kNilOptions
                                                         error:&error];
    if (! jsonData) {
        NSLog(@"Got an error: %@", error);
    } else {
        jsonString = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
    }
    return jsonString;
}

@end

//
//  Son.m
//  Interview
//
//  Created by le on 2018/11/23.
//  Copyright © 2018 le. All rights reserved.
//

#import "Son.h"

@implementation Son

- (instancetype)init {
    if (self = [super init]) {
        NSLog(@"%@", NSStringFromClass([self class]));
        NSLog(@"%@", NSStringFromClass([super class]));
    }
    return self;
}


/*
 调用[self class]的时候，会调用objc_msgSend,
 
 */


@end

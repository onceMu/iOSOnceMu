//
//  PBPerson.m
//  InterViewBlock
//
//  Created by onceMu on 2018/10/27.
//  Copyright © 2018 彭彬. All rights reserved.
//

#import "PBPerson.h"

@implementation PBPerson

- (void)test {
    void (^block)(void) = ^ {
        NSLog(@"…%p >>>>>>>>",_name);
    };
    block();
}

- (instancetype)init {
    self = [super init];
    if (self) {
        _name = @"I love you";
    }
    return self;
}

@end

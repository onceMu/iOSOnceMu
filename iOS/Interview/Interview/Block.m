//
//  Block.m
//  Interview
//
//  Created by le on 2018/12/13.
//  Copyright © 2018 le. All rights reserved.
//

#import "Block.h"

void(^test)(void) = ^{printf("Global Block\n");};

@interface Block ()

@end


@implementation Block

@end

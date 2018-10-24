//
//  main.m
//  InterViewBlock
//
//  Created by onceMu on 2018/10/24.
//  Copyright © 2018 彭彬. All rights reserved.
//

#import <Foundation/Foundation.h>

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        void (^block)(void) = ^{
            NSLog(@"Hello word");
        };
        block();
    }
    return 0;
}

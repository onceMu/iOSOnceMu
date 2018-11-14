//
//  main.m
//  InterViewBlock
//
//  Created by onceMu on 2018/10/24.
//  Copyright © 2018 彭彬. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "PBPerson.h"

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        int age = 10;
        static int b = 20;
        void (^block)(void) = ^{
            NSLog(@"Hello word %d",age);
        };
        NSLog(@"%@",[block class]);

        void (^block1)(void) = ^{
            NSLog(@"xxxxx %d",b);
        };
        NSLog(@"%@",[block1 class]);

        //MRC 下 block 是NSStackBlock、block1是 NSGlobalBlock
        //Global 没有访问auto 对象
        //stack  访问auto 对象
//        age = 20;
//        b = 40;
//        block();
//        PBPerson *person = [[PBPerson alloc]init];
//        [person test];
    }
    return 0;
}

//
//  Block.m
//  Interview
//
//  Created by le on 2018/12/13.
//  Copyright © 2018 le. All rights reserved.
//

#import "Block.h"

//void(^test)(void) = ^{printf("Global Block\n");};

//typedef void(^Test)(NSArray<NSString *> *data);
typedef void(^blk_t)(void);

@interface Block () {
    blk_t blkt;
}

//@property (nonatomic, copy) Test obTest;

@end


@implementation Block

- (instancetype)init {
    self = [super init];
    if (self) {
//        [self testxxx];
//        NSArray *obj = [self blockArray];
//        typedef void (^blkt)(void);
//        blkt blk = (blkt)[obj objectAtIndex:0];
//        blk();
//        blkt = ^{
//            NSLog(@"self = %@",self);
//        };
    }
    return self;
}

//- (void)dealloc {
//    NSLog(@"%s",__func__);
//}

//- (NSArray *)blockArray {
//    int val = 10;
//    return [[NSArray alloc] initWithObjects:[^{NSLog(@"blk0:%d",val);} copy],[^{NSLog(@"blk1:%d",val);} copy], nil];
//}
//
//- (void)test:(BOOL(^)(NSInteger))numerr {
//    BOOL xx = numerr(2);
//    if (xx) {
//        NSLog(@"xxxxx ");
//    }else {
//        NSLog(@"bbbbb ");
//    }
//}
//
//- (void)testxxx {
//    [self test:^BOOL(NSInteger number) {
//        if (number == 3) {
//            return YES;
//        }
//        return NO;
//    }];
//}

- (void)setTitle:(NSString *)title {
    _title = title;
}

@end

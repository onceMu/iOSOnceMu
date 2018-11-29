//
//  ViewController.m
//  Sort
//
//  Created by le on 2018/7/11.
//  Copyright © 2018年 le. All rights reserved.
//

#import "ViewController.h"
#import "LinkList.h"
#import "LinkListNode.swift"
#import "TestViewController.h"
#import "PBPerson.h"
#import <objc/runtime.h>

@interface ViewController ()

@property (nonatomic, copy) NSString *target;

@end

@implementation ViewController


void printString(NSString *a) {
    NSLog(@"string=%@ %p classs: %@",a,a,[a class]);
}


- (void)viewDidLoad {
    [super viewDidLoad];
    
    PBPerson *person = [[PBPerson alloc]initWithFirstName:@"a" lastName:@"b"];

    
    
    self.view.backgroundColor = [UIColor whiteColor];
    
    
    UIButton *btn = [UIButton buttonWithType:UIButtonTypeCustom];
    btn.frame = CGRectMake(100, 100, 100, 30);
    btn.backgroundColor = [UIColor redColor];
    [btn addTarget:self action:@selector(btnClick) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:btn];
    
    
    int x = 10;
//    x ++;
//    先加x的值，然后将x的值再加1
//    11 10
//    ++x 先将x加1，再加值
//    12

    int d = (x++) + (++x) + (x++);
    //10 + 12 + 12
    //
    
//    NSString *text = @"sssssss";
//    text = [text stringByReplacingOccurrencesOfString:@"\\n" withString:@"/n"];
//    NSLog(@"%@",text);
    
    NSString *cs = @"Const";
    printString(cs);
    printString([cs mutableCopy]);
    printString([[cs mutableCopy] copy]);
    
    
    NSMutableArray *xx = [NSMutableArray arrayWithArray:@[@(2),@(4),@(9),@(3),@(9)]];
    NSMutableArray *bb = [NSMutableArray arrayWithArray:@[@(2),@(4),@(9),@(3),@(9)]];
    
    NSInteger count = 0;
    for (NSInteger i = xx.count - 1; i >= 0; i--) {
        count ++;
        if ([xx[i] integerValue] == 9) {
            xx[i] = [NSNumber numberWithInteger:0];
        }else {
            NSInteger z = [xx[i] integerValue];
            z ++ ;
            xx[i] = [NSNumber numberWithInteger:z];
            NSLog(@"我还在执行 %ld",count);
        }
    }
    NSLog(@"哈哈哈哈 %@",xx);
    
    count = 0;
    for (NSInteger i = bb.count - 1; i >= 0; i--) {
        count ++;
        if ([bb[i] integerValue] == 9) {
            bb[i] = [NSNumber numberWithInteger:0];
        }else {
            NSInteger z = [bb[i] integerValue];
            z ++ ;
            bb[i] = [NSNumber numberWithInteger:z];
            NSLog(@"我还想执行 %ld",count);
            break;
        }
    }
    NSLog(@"哈哈哈哈 %@",bb);
    
    
    NSString *a = @"a";
    NSString *b = [[a mutableCopy] copy];
    
    NSLog(@"%p %p %@",a,b,object_getClass(b));
    
    
    
    NSArray *data = @[@(2),@(2),@(1)];
    int xxxx = [self findMutableInArray:data];
    
    
    NSMutableString *mutable = [NSMutableString string];
    NSString *immutable;
    char c = 'a';
    do {
        [mutable appendFormat: @"%c", c++];
        immutable = [mutable copy];
        NSLog(@"0x%016lx %@ %@", immutable, immutable, object_getClass(immutable));
    } while(((uintptr_t)immutable & 1) == 1);
    
    
    
//    dispatch_source_t timer = dispatch_source_create(DISPATCH_SOURCE_TYPE_TIMER, 0, 0, dispatch_get_main_queue());
////    dispatch_source_set_timer(timer, dispatch_time(DISPATCH_TIME_NOW, <#int64_t delta#>), <#uint64_t interval#>, <#uint64_t leeway#>)
//
//    dispatch_queue_t queue = dispatch_queue_create("com.YiYou.test", DISPATCH_QUEUE_CONCURRENT);
//    for (NSInteger i = 0; i< 100000; i++) {
//        dispatch_async(queue, ^{
//            self.target = [NSString stringWithFormat:@"ddds %ld",i];
//        });
//    }
    
    // Do any additional setup after loading the view, typically from a nib.
}

- (void)btnClick {
    TestViewController *vc = [[TestViewController alloc]init];
    [self.navigationController pushViewController:vc animated:YES];
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (int)findMutableInArray:(NSArray *)data {
    int result = 0;
    for (int i = 0; i<data.count; i++) {
        int number = [data[i] intValue];
        result ^= number;
    }
    return result;
}

/*
 运算符
 =  简单赋值运算符
 +=  加且赋值运算符
 -=  减且赋值运算符
 *=  乘且赋值运算符
 /=  除且赋值运算符
 %=  求模且赋值运算符
 <<=  左移且赋值运算符
 >>=  右移且赋值运算符
 &=   按位与且赋值运算符
 ^=   按位异且赋值运算符
 |=   按位或且赋值运算符
 
 
 */


@end

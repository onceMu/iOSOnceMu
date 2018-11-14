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


@interface ViewController ()

@property (nonatomic, copy) NSString *target;

@end

@implementation ViewController


void printString(NSString *a) {
    NSLog(@"string=%@ %p classs: %@",a,a,[a class]);
}


- (void)viewDidLoad {
    [super viewDidLoad];
    
    
    
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


@end

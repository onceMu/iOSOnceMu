//
//  TestViewController.m
//  Sort
//
//  Created by le on 2018/10/11.
//  Copyright © 2018年 le. All rights reserved.
//

#import "TestViewController.h"

@interface TestViewController ()

@property (nonatomic, strong) NSTimer *timer;

@end

@implementation TestViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.view.backgroundColor = [UIColor whiteColor];
    
//    NSArray *data = [NSArray array];
//    [data retain];
//    
//    
//    NSArray *data1 = [data copy];
//    
//    NSMutableArray *data2 = [data mutableCopy];
//    
//    
//    
//    [data release];
//    [data2 release];
//    [data1 release];
    // Do any additional setup after loading the view.
    
    
    dispatch_queue_t mySerialDispatchQueue = dispatch_queue_create("com.example.gcd.MySerialDispatchQueue", NULL);
    dispatch_queue_t globalDispatchQueue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
    dispatch_set_target_queue(mySerialDispatchQueue, globalDispatchQueue);
    
    
    
    dispatch_queue_t queue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
    dispatch_group_t group = dispatch_group_create();
    dispatch_group_async(group, queue, ^{
        NSLog(@"blok0");
    });
    dispatch_group_async(group, queue, ^{
        NSLog(@"blok1");
    });
    dispatch_group_async(group, queue, ^{
        NSLog(@"blok2");
    });
    
    dispatch_group_notify(group, dispatch_get_main_queue(), ^{
        NSLog(@"窒息性完成了");
    });
    dispatch_release(group);
    
    
    dispatch_queue_t xxxQueue = dispatch_queue_create("com.example.gcd.barrier", DISPATCH_QUEUE_CONCURRENT);
    
    dispatch_async(xxxQueue, ^{
        NSLog(@"哈哈哈 1");
    });
    
    dispatch_async(xxxQueue, ^{
        NSLog(@"哈哈哈 2");
    });
    
    dispatch_async(xxxQueue, ^{
        NSLog(@"哈哈哈 3");
    });
    
    dispatch_barrier_async(xxxQueue, ^{
        NSLog(@"我在等一会儿");
    });
    
    
    dispatch_async(xxxQueue, ^{
        NSLog(@"哈哈哈 4");
    });
    
    dispatch_async(xxxQueue, ^{
        NSLog(@"哈哈哈 5");
    });
    
    dispatch_async(xxxQueue, ^{
        NSLog(@"哈哈哈 6");
    });
    dispatch_release(xxxQueue);
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)dealloc {
    NSLog(@"%s",__func__);
    [super dealloc];
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end

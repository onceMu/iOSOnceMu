//
//  ViewController.m
//  Sort
//
//  Created by le on 2018/7/11.
//  Copyright © 2018年 le. All rights reserved.
//

#import "ViewController.h"
#import "LinkList.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    struct Node *head = NULL;
//    for (int i = 60 ; i > 0; i -= 10) {
//        pushLinkList(&head, i);
//    }
    NSArray *sss = @[@1,@2,@3,@4,@5,@6,@7,@8,@9,@1,@2,@3];
    for (NSInteger i = sss.count - 1; i >= 0; i--) {
        int data = [sss[i] intValue];
        pushLinkList(&head, data);
    }
    
    NSLog(@"\n");
    printLinkList(head);
    
//    //旋转
//    rotateLinkList(&head, 2);
//    //翻转链表
//    reverseLinkList(&head);
//    printMiddleLinkList(head);
    NSLog(@"\n");
//    printLinkList(head);
    deleteLastKey(head, 1);
    
    printLinkList(head);
    
    
    // Do any additional setup after loading the view, typically from a nib.
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end

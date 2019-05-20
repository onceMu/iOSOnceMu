//
//  ViewController.m
//  XXXX
//
//  Created by le on 2019/5/8.
//  Copyright © 2019 le. All rights reserved.
//

#import "ViewController.h"

typedef void(^BoringBlock)(void);

@interface ViewController ()
{
    NSString *_string;
    BoringBlock _blockhead;
}
@end

@implementation ViewController

static const struct block_descriptor_NAME {
    unsigned long reserved;
    unsigned long literal_size;
    void (*copy_helper)(void *dst,void *src);
    void (*dispose_helper)(void *src);
};

struct block_literal_NAME {
    void *isa;
    int flags;
    int reserved;
    void (*invoke)(void *literal,...);
    struct block_descriptor_NAME *descriptro;
};

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
//    _string = @"snork";
//    _blockhead = Block_copy(^{
//        NSLog(@"string is %@",self->_string);
//    });
    
}


@end

//
//  MemoryManager.m
//  Sort
//
//  Created by le on 2018/11/28.
//  Copyright © 2018 le. All rights reserved.
//

#import "MemoryManager.h"
#import <objc/runtime.h>

@implementation MemoryManager


/*
 
 内存管理
 
 */
//strong 普通实现
- (void)strongNormalImplementation {
    //调用这种方法的时候
    id __strong obj = [[NSObject alloc]init];
    //实际上编译器工作原理
    /*
    id objx = objc_msgSend(NSObject,@selector(alloc));
    objc_msgSend(objx,@selector(init));
    objc_release(objx);
     */
    
}

- (void)strongSpecialImplementation {
    id __strong obj = [NSMutableArray array];
    /*
     编译器工作
     
     id obj = objc_msgSend(NSMutableArray,@selector(array));
     objc_retainAutoreleasedReturnValue(obj);
     objc_release(obj);
     
     
     + (id)array {
        id obj = objc_msgSend(NSMutableArray,@selector(alloc));
        objc_msgSend(obj,@selector(init));
        return objc_autoreleaseReturnValue(obj);
     }
     
     */
    
}

//weak 实现
- (void)weakImplementation {
    id __strong obj = [[NSObject alloc]init];
    id __weak obj1 = obj;
    
    /*
     编译器工作原理
     id obj1;
     objc_initWeak(&obj1,obj);
     objc_destroyWeak(&obj1);
     */
}

@end

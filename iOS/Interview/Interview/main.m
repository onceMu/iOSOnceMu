//
//  main.m
//  Interview
//
//  Created by le on 2018/10/16.
//  Copyright © 2018年 le. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <malloc/malloc.h>
#import <objc/runtime.h>


@interface Student : NSObject {
    @public
    int _no;
    int _age;
}

@end

@implementation Student

@end

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        // insert code here...
        NSObject *object = [[NSObject alloc]init];
        
        Student *stu = [[Student alloc]init];
        
        //获取object类实例对象成员变量的大小
        NSLog(@"%zd",class_getInstanceSize([Student class]));
        
        
        //获取object指针指向内存的大小
        NSLog(@"%zd",malloc_size((__bridge const void *)stu));
        
        
        
    }
    return 0;
}

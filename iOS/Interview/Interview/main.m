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



int main(int argc, const char * argv[]) {
    @autoreleasepool {
        // insert code here...

    
        
    }
    return 0;
}


//id __attribute__((objc_ownership(strong))) obj = ((NSObject *(*)(id, SEL))(void *)objc_msgSend)((id)((NSObject *(*)(id, SEL))(void *)objc_msgSend)((id)objc_getClass("NSObject"), sel_registerName("alloc")), sel_registerName("init"));



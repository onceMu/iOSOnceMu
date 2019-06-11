//
//  main.m
//  xxxxx
//
//  Created by le on 2019/6/10.
//  Copyright © 2019 le. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <stdlib.h>
#import <unistd.h>
#import <stdio.h>

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        // insert code here...
        NSLog(@"Hello, World!");
        
        printf("hello world (pid:%d)\n",(int)getpid());
        
        int rc = fork();
        
        if (rc < 0) {
            fprintf(stderr, "fork failed \n");
            exit(1);
        }else if (rc == 0) {
            printf("hello , i am child (pid:%d)\n",(int)getpid());
        }else {
            printf("hello ,  i am parent of %d (pid:%d)\n",rc,(int)getpid());
        }
        
        
    }
    return 0;
}

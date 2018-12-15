//
//  main.m
//  InterViewBlock
//
//  Created by onceMu on 2018/10/24.
//  Copyright © 2018 彭彬. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "PBPerson.h"

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        int age = 10;
        static int b = 20;
        void (^block)(void) = ^{
            NSLog(@"Hello word %d",age);
        };
        block();

        //MRC 下 block 是NSStackBlock、block1是 NSGlobalBlock
        //Global 没有访问auto 对象
        //stack  访问auto 对象
//        age = 20;
//        b = 40;
//        block();
//        PBPerson *person = [[PBPerson alloc]init];
//        [person test];
    }
    return 0;
}


// isa 指向
// instance class 的isa 指向的是 class 的isa
// class 的isa 指向的是 meta-class 的isa
// meta-class 的isa 指向的是 root class 的isa
// root class 的 isa 指向nil

/*
struct __block_impl {
    void *isa; // isa 指针
    int Flags;
    int Reserved;
    void *FuncPtr;
};

struct __main_block_impl_0 {
    struct __block_impl impl; //__block_impl 不是指针，结构体
    struct __main_block_desc_0* Desc; //__main_block_desc_0* 指针
    int age;
    __main_block_impl_0(void *fp, struct __main_block_desc_0 *desc, int _age, int flags=0) : age(_age) {
        impl.isa = &_NSConcreteStackBlock;
        impl.Flags = flags;
        impl.FuncPtr = fp;// 函数指针
        Desc = desc;
    }
};
static void __main_block_func_0(struct __main_block_impl_0 *__cself) {
    int age = __cself->age; // bound by copy

    NSLog((NSString *)&__NSConstantStringImpl__var_folders_97_bz_j89nj3lz1tj200mlnb8f80000gn_T_main_29cc47_mi_0,age);
}

static struct __main_block_desc_0 {
    size_t reserved;
    size_t Block_size; //block 大小
} __main_block_desc_0_DATA = { 0, sizeof(struct __main_block_impl_0)};


 void (*block)(void) = ((void (*)())&__main_block_impl_0((void *)__main_block_func_0, &__main_block_desc_0_DATA, age));
 ((void (*)(__block_impl *))((__block_impl *)block)->FuncPtr)((__block_impl *)block);

 void (*block)(void) = &__main_block_impl_0(__main_block_func_0, &__main_block_desc_0_DATA, age));
 ((block)->FuncPtr)(block);

*/

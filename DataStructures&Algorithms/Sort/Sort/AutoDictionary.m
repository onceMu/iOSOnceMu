//
//  AutoDictionary.m
//  Sort
//
//  Created by le on 2018/11/15.
//  Copyright © 2018 le. All rights reserved.
//

#import "AutoDictionary.h"
#import <objc/runtime.h>

@interface AutoDictionary ()

@property (nonatomic, strong) NSMutableDictionary *backingStore;

@end

@implementation AutoDictionary

@dynamic string,number,date,opaqueObject;

- (instancetype)init {
    if (self = [super init]) {
        _backingStore = [NSMutableDictionary dictionary];
    }
    return self;
}

id autoDictionaryGetter(id self,SEL _cmd) {
    AutoDictionary *typeSelf = (AutoDictionary *)self;
    NSMutableDictionary *backingStore = typeSelf.backingStore;
    NSString *key = NSStringFromSelector(_cmd);
    return [backingStore objectForKey:key];
}

void autoDictionarySetter (id self, SEL _cmd, id value) {
    AutoDictionary *typeSelf = (AutoDictionary *)self;
    NSMutableDictionary *backingStore = typeSelf.backingStore;
    NSString *selectorString = NSStringFromSelector(_cmd);
    NSMutableString *key = [selectorString mutableCopy];
    [key deleteCharactersInRange:NSMakeRange(key.length-1, 1)];
    [key deleteCharactersInRange:NSMakeRange(0, 3)];
    NSString *lower = [[key substringToIndex:1] lowercaseString];
    [key replaceCharactersInRange:NSMakeRange(0, 1) withString:lower];
    if (value) {
        [backingStore setObject:value forKey:key];
    }else {
        [backingStore removeObjectForKey:key];
    }
}


+ (BOOL)resolveInstanceMethod:(SEL)sel {
    NSString *selectorString = NSStringFromSelector(sel);
    if ([selectorString hasPrefix:@"set"]) {
        class_addMethod(self, sel, (IMP)autoDictionarySetter, "v@:@");
    }else {
        class_addMethod(self, sel, (IMP)autoDictionaryGetter, "@@:");
    }
    return YES;
}


@end

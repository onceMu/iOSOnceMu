//
//  PBPerson.m
//  Sort
//
//  Created by le on 2018/11/16.
//  Copyright © 2018 le. All rights reserved.
//

#import "PBPerson.h"

@interface PBPerson ()

@property (nonatomic, copy, readwrite) NSString *firstName;
@property (nonatomic, copy, readwrite) NSString *lastName;

@end


@implementation PBPerson

- (instancetype)initWithFirstName:(NSString *)firstName
                         lastName:(NSString *)lastName {
    self = [super init];
    if (self) {
        _firstName = firstName;
        _lastName = lastName;
    }
    return self;
}

@end

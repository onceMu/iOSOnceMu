//
//  PBPerson.h
//  Sort
//
//  Created by le on 2018/11/16.
//  Copyright © 2018 le. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface PBPerson : NSObject

@property (nonatomic, copy, readonly) NSString *firstName;
@property (nonatomic, copy, readonly) NSString *lastName;

- (instancetype)initWithFirstName:(NSString *)firstName
                         lastName:(NSString *)lastName;



@end


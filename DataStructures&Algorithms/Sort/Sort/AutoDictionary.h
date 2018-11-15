//
//  AutoDictionary.h
//  Sort
//
//  Created by le on 2018/11/15.
//  Copyright © 2018 le. All rights reserved.
//

#import <Foundation/Foundation.h>



@interface AutoDictionary : NSObject

@property (nonatomic, copy) NSString *string;
@property (nonatomic, strong) NSNumber *number;
@property (nonatomic, strong) NSDate *date;
@property (nonatomic, strong) id opaqueObject;

@end


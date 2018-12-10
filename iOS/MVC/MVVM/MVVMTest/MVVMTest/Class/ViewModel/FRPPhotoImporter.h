//
//  FRPPhotoImporter.h
//  MVVMTest
//
//  Created by le on 2018/12/10.
//  Copyright © 2018 le. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FRPPhotoModel.h"



@interface FRPPhotoImporter : NSObject

@property (nonatomic, assign) NSInteger pageIndex;

+ (RACSignal *)importPhotos;

- (RACSignal *)fetchCityAndHouse;

@end


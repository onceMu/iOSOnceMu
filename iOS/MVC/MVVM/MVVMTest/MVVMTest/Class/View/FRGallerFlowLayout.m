//
//  FRGallerFlowLayout.m
//  MVVMTest
//
//  Created by le on 2018/12/10.
//  Copyright © 2018 le. All rights reserved.
//

#import "FRGallerFlowLayout.h"

@implementation FRGallerFlowLayout

- (instancetype)init {
    self = [super init];
    if (self) {
        self.itemSize = CGSizeMake(145, 145);
        self.minimumLineSpacing = 10;
        self.minimumInteritemSpacing = 10;
        self.sectionInset = UIEdgeInsetsMake(10, 10, 10, 10);
    }
    return self;
}

@end

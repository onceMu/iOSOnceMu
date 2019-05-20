//
//  RWTSearchResultsViewModel.h
//  RWTFlickrSearch
//
//  Created by le on 2019/3/19.
//  Copyright © 2019 Colin Eberhardt. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RWTViewModelServices.h"
#import "RWTFlickrSearchResults.h"

NS_ASSUME_NONNULL_BEGIN

@interface RWTSearchResultsViewModel : NSObject

- (instancetype)initWithSearchResults:(RWTFlickrSearchResults *)results
                             services:(id<RWTViewModelServices>)services;

@property (nonatomic, copy) NSString *title;
@property (nonatomic, strong) NSArray *searchResults;

@end

NS_ASSUME_NONNULL_END

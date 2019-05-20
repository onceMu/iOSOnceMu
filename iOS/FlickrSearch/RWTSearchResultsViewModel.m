//
//  RWTSearchResultsViewModel.m
//  RWTFlickrSearch
//
//  Created by le on 2019/3/19.
//  Copyright © 2019 Colin Eberhardt. All rights reserved.
//

#import "RWTSearchResultsViewModel.h"

@implementation RWTSearchResultsViewModel

- (instancetype)initWithSearchResults:(RWTFlickrSearchResults *)results
                             services:(id<RWTViewModelServices>)services {
    self = [super init];
    if (self) {
        _title = results.searchString;
        _searchResults = results.photos;
    }
    return self;
}


@end

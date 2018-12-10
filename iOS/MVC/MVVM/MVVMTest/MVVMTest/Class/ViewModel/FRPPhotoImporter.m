//
//  FRPPhotoImporter.m
//  MVVMTest
//
//  Created by le on 2018/12/10.
//  Copyright © 2018 le. All rights reserved.
//

#import "FRPPhotoImporter.h"
#import "AppDelegate.h"
#import "OHBaseNetwork.h"

@interface FRPPhotoImporter ()

@property (nonatomic, strong) OHBaseNetwork *network;

@end


@implementation FRPPhotoImporter

+ (RACSignal *)importPhotos {
    RACReplaySubject *subject = [RACReplaySubject subject];
    OHBaseNetwork *network= [[OHBaseNetwork alloc]init];
    [network requestPOSTwithUrl:@"house/getAppHomePageCityManageList" parameters:[self getParames] success:^(NSString *requestURL, id responseObject) {
        NSLog(@"%@",responseObject);
    } failure:^(NSError *error, id responseObject) {
        NSLog(@"哈哈哈哈哈");
        [subject sendError:error];
    }];
    return subject;
}

- (RACSignal *)fetchCityAndHouse {
    RACReplaySubject *subject = [RACReplaySubject subject];
    
    return subject;
}

+ (void)configurePhotoModel:(FRPPhotoModel *)photomodel withDictionary:(NSDictionary *)dictionary {
    photomodel.photoName = dictionary[@"name"];
    photomodel.identifier = dictionary[@"id"];
    photomodel.photographerName = dictionary[@"user"][@"username"];
    photomodel.rating = dictionary[@"rating"];
    photomodel.thumbnailURL = [self urlForImageSize:3 inArray:dictionary[@"images"]];
    //Extended attributes fetched with subsequent request
    if (dictionary[@"comments_count"]){
        photomodel.fullsizedURL = [self urlForImageSize:4 inArray:dictionary[@"images"]];
    }
}

+ (void)downloadThumbnailForPhotoModel:(FRPPhotoModel *)model {
    NSAssert(model.thumbnailURL, @"不能为空");
    NSURLRequest *request = [NSURLRequest requestWithURL:[NSURL URLWithString:model.thumbnailURL]];
    [NSURLConnection sendAsynchronousRequest:request queue:[NSOperationQueue mainQueue] completionHandler:^(NSURLResponse * _Nullable response, NSData * _Nullable data, NSError * _Nullable connectionError) {
        if (data) {
           model.thumbnailData = data;
        }
    }];
}

+ (NSString *)urlForImageSize:(NSInteger)size inArray:(NSArray *)array {
    return [[[[[array rac_sequence] filter:^BOOL(NSDictionary * value) {
        return [value[@"size"] integerValue] == size;
    }] map:^id (id  value) {
        return value[@"url"];
    }] array]firstObject];
}


+ (NSURLRequest *)popularURLRequest {
    return [[AppDelegate app].apiHelper urlRequestForPhotoFeature:PXAPIHelperPhotoFeaturePopular
                                                   resultsPerPage:100
                                                             page:0
                                                       photoSizes:PXPhotoModelSizeThumbnail
                                                        sortOrder:PXAPIHelperSortOrderRating
                                                           except:PXPhotoModelCategoryNude];
}


+ (NSMutableDictionary *)getParames {
    NSMutableDictionary *param = [NSMutableDictionary dictionaryWithCapacity:1];
    [param setObject:@"1" forKey:@"typeNum"];
    NSMutableDictionary *range = [NSMutableDictionary dictionary];
    [range setValue:@(0) forKey:@"page"];
    [range setValue:@"8" forKey:@"pageSize"];
    [param setValue:range forKey:@"range"];
    return param;
}

- (OHBaseNetwork *)network {
    if (_network == nil) {
        _network = [[OHBaseNetwork alloc]init];
    }
    return _network;
}


@end

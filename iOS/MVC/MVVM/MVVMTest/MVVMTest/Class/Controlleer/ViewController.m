//
//  ViewController.m
//  MVVMTest
//
//  Created by le on 2018/12/7.
//  Copyright © 2018 le. All rights reserved.
//

#import "ViewController.h"
#import <ReactiveObjC/ReactiveObjC.h>
#import "FRPPhotoImporter.h"
#import "FRGallerFlowLayout.h"
#import "FRPCell.h"

static NSString * CellIdentifier = @"Cell";

@interface ViewController () <UICollectionViewDelegate,UICollectionViewDataSource>

@property (nonatomic, strong) UICollectionView *collectionView;
@property (nonatomic, strong) NSMutableArray *dataList;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    
    self.navigationItem.title = @"Popular on 500px";
    
    @weakify(self);
    [RACObserve(self, dataList) subscribeNext:^(id  _Nullable x) {
        @strongify(self);
        [self.collectionView reloadData];
    }];
    [self loadData];
    
    
    
}

- (void)loadData {
    [[FRPPhotoImporter importPhotos] subscribeNext:^(id  _Nullable x) {
        self.dataList = x;
    } error:^(NSError * _Nullable error) {
        NSLog(@"失败了");
    }];
}

#pragma mark --UICollectionViewDelegate && UICollectionViewDataSource
- (NSInteger)numberOfSectionsInCollectionView:(UICollectionView *)collectionView {
    return 1;
}

- (NSInteger)collectionView:(UICollectionView *)collectionView numberOfItemsInSection:(NSInteger)section {
    return self.dataList.count;
}

- (__kindof UICollectionViewCell *)collectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath {
    FRPCell *cell = [collectionView dequeueReusableCellWithReuseIdentifier:CellIdentifier forIndexPath:indexPath];
    if (self.dataList.count > indexPath.item) {
        [cell setModel:self.dataList[indexPath.item]];
    }
    
    return cell;
}


#pragma mark --Lazy Init
- (UICollectionView *)collectionView {
    if (_collectionView == nil) {
        FRGallerFlowLayout *layout = [[FRGallerFlowLayout alloc]init];
        _collectionView = [[UICollectionView alloc]initWithFrame:self.view.bounds collectionViewLayout:layout];
        _collectionView.delegate = self;
        _collectionView.dataSource = self;
        _collectionView.showsHorizontalScrollIndicator = NO;
        _collectionView.backgroundColor = [UIColor whiteColor];
        [_collectionView registerClass:[FRPCell class] forCellWithReuseIdentifier:CellIdentifier];
    }
    return _collectionView;
}


@end

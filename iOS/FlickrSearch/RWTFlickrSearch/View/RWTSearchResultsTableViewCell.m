//
//  Created by Colin Eberhardt on 26/04/2014.
//  Copyright (c) 2014 Colin Eberhardt. All rights reserved.
//

#import "RWTSearchResultsTableViewCell.h"
#import "RWTFlickrPhoto.h"
#import <UIImageView+WebCache.h>
#import <ReactiveCocoa/ReactiveCocoa.h>

@interface RWTSearchResultsTableViewCell ()

@property (weak, nonatomic) IBOutlet UILabel *titleLabel;
@property (weak, nonatomic) IBOutlet UIImageView *imageThumbnailView;
@property (weak, nonatomic) IBOutlet UILabel *favouritesLabel;
@property (weak, nonatomic) IBOutlet UILabel *commentsLabel;
@property (weak, nonatomic) IBOutlet UIImageView *commentsIcon;
@property (weak, nonatomic) IBOutlet UIImageView *favouritesIcon;

@end

@implementation RWTSearchResultsTableViewCell

- (void)awakeFromNib {
    [super awakeFromNib];
    self.imageThumbnailView.contentMode = UIViewContentModeScaleAspectFit;
}

- (void)bindViewModel:(id)viewModel {
    RWTFlickrPhoto *photo = viewModel;
    self.titleLabel.text = photo.title;
    self.imageThumbnailView.contentMode = UIViewContentModeScaleToFill;
    [self.imageThumbnailView sd_setImageWithURL:photo.url];
}

- (void)setParallax:(CGFloat)value {
    self.imageThumbnailView.transform = CGAffineTransformMakeTranslation(0, value);
}


@end

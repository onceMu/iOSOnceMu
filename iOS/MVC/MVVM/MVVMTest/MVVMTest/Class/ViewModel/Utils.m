//
//  Utils.m
//  AppPrototype
//
//  Created by ChenLiangwei on 15/10/10.
//  Copyright © 2015年 FantasyD. All rights reserved.
//

#import "Utils.h"
#import <sys/utsname.h>
#import "NSArray+NSString.h"
#import "NSDictionary+String.h"
#import "NSString+Additions.h"

//#import "OHKeyChainModel.h"

BOOL preferedChineseTranditional() {

    NSString *firstPerferedLanguage = [NSLocale preferredLanguages][0];
    if ([firstPerferedLanguage hasPrefix:@"zh-Hant"]) {
        return YES;
    }
    return [@[@"zh-Hant-CN", @"zh-HK", @"zh-MC", @"zh-TW"] containsObject:firstPerferedLanguage];
}

@implementation Utils

+ (NSDictionary *)systemParam {
    
    NSString* uuid=@"";
    @try {
        uuid = [[[UIDevice currentDevice] identifierForVendor] UUIDString];
        
//        uuid = [OHKeyChainModel deviceIdentifier];
    }
    @catch (NSException *exception) {
        uuid = @"unknown";
    }
    
    NSMutableDictionary *parames = [NSMutableDictionary dictionaryWithCapacity:6];
    [parames setObject:@"IOS" forKey:@"deviceType"];
    [parames setObject:@"3.1" forKey:@"version"];
    [parames setObject:uuid ? uuid : @"unknown" forKey:@"deviceId"];
    [parames setObject:@"tw" forKey:@"area"];
    [parames setObject:@"2.1" forKey:@"apiVersion"];

    NSString *deviceType = [Utils deviceType];
    if (deviceType.length > 0) {
        [parames setObject:deviceType forKey:@"model"];
    }
    
    return parames;

}

+ (NSDictionary *)systemParamForBack {
    
    NSString* uuid=@"";
    @try {
        uuid = [[[UIDevice currentDevice] identifierForVendor] UUIDString];
//        uuid = [OHKeyChainModel deviceIdentifier];
    }
    @catch (NSException *exception) {
        uuid = @"unknown";
    }
    
    NSMutableDictionary *parames = [NSMutableDictionary dictionaryWithCapacity:1];
    [parames setObject:@"ios" forKey:@"deviceType"];
    [parames setObject:@"3.1" forKey:@"version"];
    [parames setObject:@"2.1" forKey:@"apiVersion"];
    
    NSString *deviceType = [Utils deviceType];
    if (deviceType.length > 0) {
        [parames setObject:deviceType forKey:@"model"];
    }
    [parames setObject:uuid forKey:@"uuid"];
    [parames setObject:@"tw" forKey:@"area"];
    
    
    return parames;
}
//    if (![NSString isBlankString:[Utils deviceType]]) {
//        [parames setObject:[Utils deviceType] forKey:@"model"];
//    }


//    return @{@"deviceType": @"ios",
//             @"version": MaxSystemVersion,
//             @"model": [Utils deviceType],
//             @"deviceId":uuid,
//             @"area": preferedChineseTranditional() ? @"tw" : @""
//             };


+ (NSString *)deviceType {
//    struct utsname systemInfo;
//    uname(&systemInfo);
//    NSString *name = [NSString stringWithCString:systemInfo.machine encoding:NSUTF8StringEncoding];
//    
//    /**********
//     iPhone 6S | iPhone 6S Plus | iPhone 6 | iPhone 6 Plus | iPhone 5S | iPhone 5C | iPhone 5 | iPhone 4S
//     iPod Touch
//     iPad Mini | iPad Mini 2| iPad Mini 3 | iPad Mini 4
//     iPad Air | iPad Air 2
//     **********/
//    
//    
//    if ([name isEqualToString:@"iPhone3,1"]) return @"iPhone4";
//    if ([name isEqualToString:@"iPhone3,2"]) return @"iPhone4";
//    if ([name isEqualToString:@"iPhone3,3"]) return @"iPhone4";
//    
//    if ([name isEqualToString:@"iPhone4,1"]) return @"iPhone4S";
//    if ([name isEqualToString:@"iPhone5,1"]) return @"iPhone5";
//    if ([name isEqualToString:@"iPhone5,2"]) return @"iPhone5";
//    if ([name isEqualToString:@"iPhone5,3"]) return @"iPhone5c";
//    if ([name isEqualToString:@"iPhone5,4"]) return @"iPhone5c";
//    if ([name isEqualToString:@"iPhone6,1"]) return @"iPhone5s";
//    if ([name isEqualToString:@"iPhone6,2"]) return @"iPhone5s";
//    if ([name isEqualToString:@"iPhone7,1"]) return @"iPhone6Plus";
//    if ([name isEqualToString:@"iPhone7,2"]) return @"iPhone6";
//    if ([name isEqualToString:@"iPhone8,1"]) return @"iPhone6s";
//    if ([name isEqualToString:@"iPhone8,2"]) return @"iPhone6sPlus";
//    
//    if ([name isEqualToString:@"iPod1,1"])   return @"iPodTouch1G (A1213)";
//    if ([name isEqualToString:@"iPod2,1"])   return @"iPodTouch2G (A1288)";
//    if ([name isEqualToString:@"iPod3,1"])   return @"iPodTouch3G (A1318)";
//    if ([name isEqualToString:@"iPod4,1"])   return @"iPodTouch4G (A1367)";
//    if ([name isEqualToString:@"iPod5,1"])   return @"iPodTouch5G (A1421/A1509)";
//    
//    if ([name isEqualToString:@"iPad2,5"])   return @"iPadMini(A1432)";
//    if ([name isEqualToString:@"iPad2,6"])   return @"iPadMini(A1454)";
//    if ([name isEqualToString:@"iPad2,7"])   return @"iPadMini(A1455)";
//    
//    if ([name isEqualToString:@"iPad3,1"])   return @"iPad3(A1416)";
//    if ([name isEqualToString:@"iPad3,2"])   return @"iPad3(A1403)";
//    if ([name isEqualToString:@"iPad3,3"])   return @"iPad3(A1430)";
//    if ([name isEqualToString:@"iPad3,4"])   return @"iPad4(A1458)";
//    if ([name isEqualToString:@"iPad3,5"])   return @"iPad4(A1459)";
//    if ([name isEqualToString:@"iPad3,6"])   return @"iPad4(A1460)";
//    
//    if ([name isEqualToString:@"iPad4,1"])   return @"iPadAir (A1474)";
//    if ([name isEqualToString:@"iPad4,2"])   return @"iPadAir (A1475)";
//    if ([name isEqualToString:@"iPad4,3"])   return @"iPadAir (A1476)";
//    if ([name isEqualToString:@"iPad4,4"])   return @"iPadMini2 (A1489)";
//    if ([name isEqualToString:@"iPad4,5"])   return @"iPadMini2 (A1490)";
//    if ([name isEqualToString:@"iPad4,6"])   return @"iPadMini2 (A1491)";
//    
//    if ([name isEqualToString:@"iPod7,1"])   return @"iPod7";
//    
//    return @"NOT FOUND";
    // 需要#import "sys/utsname.h"
//#warning 题主呕心沥血总结！！最全面！亲测！全网独此一份！！
    struct utsname systemInfo;
    uname(&systemInfo);
    NSString *deviceString = [NSString stringWithCString:systemInfo.machine encoding:NSUTF8StringEncoding];
    
    if ([deviceString isEqualToString:@"iPhone3,1"])    return @"iPhone 4";
    if ([deviceString isEqualToString:@"iPhone3,2"])    return @"iPhone 4";
    if ([deviceString isEqualToString:@"iPhone3,3"])    return @"iPhone 4";
    if ([deviceString isEqualToString:@"iPhone4,1"])    return @"iPhone 4S";
    if ([deviceString isEqualToString:@"iPhone5,1"])    return @"iPhone 5";
    if ([deviceString isEqualToString:@"iPhone5,2"])    return @"iPhone 5 (GSM+CDMA)";
    if ([deviceString isEqualToString:@"iPhone5,3"])    return @"iPhone 5c (GSM)";
    if ([deviceString isEqualToString:@"iPhone5,4"])    return @"iPhone 5c (GSM+CDMA)";
    if ([deviceString isEqualToString:@"iPhone6,1"])    return @"iPhone 5s (GSM)";
    if ([deviceString isEqualToString:@"iPhone6,2"])    return @"iPhone 5s (GSM+CDMA)";
    if ([deviceString isEqualToString:@"iPhone7,1"])    return @"iPhone 6 Plus";
    if ([deviceString isEqualToString:@"iPhone7,2"])    return @"iPhone 6";
    if ([deviceString isEqualToString:@"iPhone8,1"])    return @"iPhone 6s";
    if ([deviceString isEqualToString:@"iPhone8,2"])    return @"iPhone 6s Plus";
    if ([deviceString isEqualToString:@"iPhone8,4"])    return @"iPhone SE";
    // 日行两款手机型号均为日本独占，可能使用索尼FeliCa支付方案而不是苹果支付
    if ([deviceString isEqualToString:@"iPhone9,1"])    return @"国行、日版、港行iPhone 7";
    if ([deviceString isEqualToString:@"iPhone9,2"])    return @"港行、国行iPhone 7 Plus";
    if ([deviceString isEqualToString:@"iPhone9,3"])    return @"美版、台版iPhone 7";
    if ([deviceString isEqualToString:@"iPhone9,4"])    return @"美版、台版iPhone 7 Plus";
    if ([deviceString isEqualToString:@"iPhone10,1"])   return @"iPhone_8";
    if ([deviceString isEqualToString:@"iPhone10,4"])   return @"iPhone_8";
    if ([deviceString isEqualToString:@"iPhone10,2"])   return @"iPhone_8_Plus";
    if ([deviceString isEqualToString:@"iPhone10,5"])   return @"iPhone_8_Plus";
    if ([deviceString isEqualToString:@"iPhone10,3"])   return @"iPhone_X";
    if ([deviceString isEqualToString:@"iPhone10,6"])   return @"iPhone_X";
    
    if ([deviceString isEqualToString:@"iPod1,1"])      return @"iPod Touch 1G";
    if ([deviceString isEqualToString:@"iPod2,1"])      return @"iPod Touch 2G";
    if ([deviceString isEqualToString:@"iPod3,1"])      return @"iPod Touch 3G";
    if ([deviceString isEqualToString:@"iPod4,1"])      return @"iPod Touch 4G";
    if ([deviceString isEqualToString:@"iPod5,1"])      return @"iPod Touch (5 Gen)";
    
    if ([deviceString isEqualToString:@"iPad1,1"])      return @"iPad";
    if ([deviceString isEqualToString:@"iPad1,2"])      return @"iPad 3G";
    if ([deviceString isEqualToString:@"iPad2,1"])      return @"iPad 2 (WiFi)";
    if ([deviceString isEqualToString:@"iPad2,2"])      return @"iPad 2";
    if ([deviceString isEqualToString:@"iPad2,3"])      return @"iPad 2 (CDMA)";
    if ([deviceString isEqualToString:@"iPad2,4"])      return @"iPad 2";
    if ([deviceString isEqualToString:@"iPad2,5"])      return @"iPad Mini (WiFi)";
    if ([deviceString isEqualToString:@"iPad2,6"])      return @"iPad Mini";
    if ([deviceString isEqualToString:@"iPad2,7"])      return @"iPad Mini (GSM+CDMA)";
    if ([deviceString isEqualToString:@"iPad3,1"])      return @"iPad 3 (WiFi)";
    if ([deviceString isEqualToString:@"iPad3,2"])      return @"iPad 3 (GSM+CDMA)";
    if ([deviceString isEqualToString:@"iPad3,3"])      return @"iPad 3";
    if ([deviceString isEqualToString:@"iPad3,4"])      return @"iPad 4 (WiFi)";
    if ([deviceString isEqualToString:@"iPad3,5"])      return @"iPad 4";
    if ([deviceString isEqualToString:@"iPad3,6"])      return @"iPad 4 (GSM+CDMA)";
    if ([deviceString isEqualToString:@"iPad4,1"])      return @"iPad Air (WiFi)";
    if ([deviceString isEqualToString:@"iPad4,2"])      return @"iPad Air (Cellular)";
    if ([deviceString isEqualToString:@"iPad4,4"])      return @"iPad Mini 2 (WiFi)";
    if ([deviceString isEqualToString:@"iPad4,5"])      return @"iPad Mini 2 (Cellular)";
    if ([deviceString isEqualToString:@"iPad4,6"])      return @"iPad Mini 2";
    if ([deviceString isEqualToString:@"iPad4,7"])      return @"iPad Mini 3";
    if ([deviceString isEqualToString:@"iPad4,8"])      return @"iPad Mini 3";
    if ([deviceString isEqualToString:@"iPad4,9"])      return @"iPad Mini 3";
    if ([deviceString isEqualToString:@"iPad5,1"])      return @"iPad Mini 4 (WiFi)";
    if ([deviceString isEqualToString:@"iPad5,2"])      return @"iPad Mini 4 (LTE)";
    if ([deviceString isEqualToString:@"iPad5,3"])      return @"iPad Air 2";
    if ([deviceString isEqualToString:@"iPad5,4"])      return @"iPad Air 2";
    if ([deviceString isEqualToString:@"iPad6,3"])      return @"iPad Pro 9.7";
    if ([deviceString isEqualToString:@"iPad6,4"])      return @"iPad Pro 9.7";
    if ([deviceString isEqualToString:@"iPad6,7"])      return @"iPad Pro 12.9";
    if ([deviceString isEqualToString:@"iPad6,8"])      return @"iPad Pro 12.9";
    
    if ([deviceString isEqualToString:@"AppleTV2,1"])      return @"Apple TV 2";
    if ([deviceString isEqualToString:@"AppleTV3,1"])      return @"Apple TV 3";
    if ([deviceString isEqualToString:@"AppleTV3,2"])      return @"Apple TV 3";
    if ([deviceString isEqualToString:@"AppleTV5,3"])      return @"Apple TV 4";
    
    if ([deviceString isEqualToString:@"i386"])         return @"Simulator";
    if ([deviceString isEqualToString:@"x86_64"])       return @"Simulator";
    
    return deviceString;
}

+ (NSArray *)areaCodes {
    
    return @[@"+61",@"+44",@"+81",@"+82",@"+886",@"+1",@"+60"];
}

+ (NSString *)tokenSign:(NSDictionary *)paramames
          systemParames:(NSDictionary *)systemParames {
    NSMutableDictionary *dic = [NSMutableDictionary dictionaryWithCapacity:1];
    //合并两个字典
    [dic addEntriesFromDictionary:paramames];
    [dic addEntriesFromDictionary:systemParames];
    
    NSArray *sortArray = [[dic allKeys] sortedArrayUsingSelector:@selector(compare:)];
    NSMutableString *token = [NSMutableString string];
    for (NSInteger i = 0; i<sortArray.count; i++) {
        NSString *key = sortArray[i];
        id value = dic[key];
        [token appendFormat:@"%@=",key];
        if ([value isKindOfClass:[NSArray class]]) {
            NSArray *array = (NSArray *)value;
            [token appendFormat:@"%@&",[array jsonString]];
        }else if ([value isKindOfClass:[NSDictionary class]]) {
            NSDictionary *parm = (NSDictionary *)value;
            [token appendFormat:@"%@&",[parm jsonString]];
        }else {
            [token appendFormat:@"%@&",value];
        }
    }
    //截取掉最后一个& 符号 并且加入随机串
    NSString *finishedSign = [NSString stringWithFormat:@"%@FC83CDBAEFB714B650FA56852AF1CD67",[token substringToIndex:token.length-1]];
    //转换成MD5
    NSString *md5 = [finishedSign md5];
    //最后转换成全部大写
    return [md5 uppercaseString];
}

+ (BOOL)checkDeviceIsiPad {
    NSString *deviceModel = [UIDevice currentDevice].model;
    if ([deviceModel isEqualToString:@"iPhone"]) {
        return NO;
    }
    if ([deviceModel isEqualToString:@"iPod touch"]) {
        return NO;
    }
    if ([deviceModel isEqualToString:@"iPad"]) {
        return YES;
    }
    return NO;
}


+ (NSString *)convertCurrentLangugae:(NSString *)language {
//    ko-kr, ja-jp, en, tw, 缺省 简体中文 zh

    return @"";
}

@end

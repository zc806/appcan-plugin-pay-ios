//
//  EUExPay.h
//  AppCan
//
//  Created by AppCan on 11-10-18.
//  Copyright 2011 AppCan. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "EUExBase.h"
#import "AliPay.h"
#import "AliPayInfo.h"
#define UEX_CPAYSUCCESS			0
#define UEX_CPAYING             1
#define UEX_CPAYFAILED			2
#define UEX_CPAYPLUGINERROR		3

@interface EUExPay : EUExBase {
    AliPayInfo *payInfo;
}
@property(nonatomic,retain)AliPayInfo *payInfo;
@property(nonatomic,copy)NSString *jsStr;
-(void)uexOnPayWithStatus:(int)inStatus des:(NSString*)inDes;
- (void)parseURL:(NSURL *)url application:(UIApplication *)application;
@end

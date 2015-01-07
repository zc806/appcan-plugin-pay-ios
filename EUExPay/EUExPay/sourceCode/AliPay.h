//
//  AlixPay.h
//  AppCan
//
//  Created by AppCan on 11-10-26.
//  Copyright 2011 AppCan. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "AlixPayOrder.h"
#import "AlixPay.h"
#import "EUtility.h"
#import "AliPayInfo.h"
#define UEX_CPAYSUCCESS			0
#define UEX_CPAYING			1
#define UEX_CPAYFAILED			2
#define UEX_CPAYPLUGINERROR		3
@class EUExPay;
@interface AliPay : NSObject {
	EUExPay *euexObj;
}
-(id)initWithEuexObj:(EUExPay *)euexObj_ ;
-(int)openAliPay:(NSMutableDictionary *)argdict payInfo:(AliPayInfo *)payInfo;
@end

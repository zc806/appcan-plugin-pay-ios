//
//  EUExPay.m
//  AppCan
//
//  Created by AppCan on 11-10-18.
//  Copyright 2011 AppCan. All rights reserved.
//

#import "EUExPay.h"


#import "EUExBaseDefine.h"
#import "DataSigner.h"
#import "DataVerifier.h"
@implementation EUExPay
@synthesize payInfo;

AliPay *payObj;

-(id)initWithBrwView:(EBrowserView *) eInBrwView{	
	if (self = [super initWithBrwView:eInBrwView]) {
	}
	return self;
}

-(void)dealloc{
	[payObj release];
	payObj = nil;
    [payInfo release];
	[super dealloc];
}

-(void)pay:(NSMutableArray *)inArguments{
	NSString *inTradNum = [inArguments objectAtIndex:0];
	NSString *inSubject = [inArguments objectAtIndex:1];
	NSString *inBody = [inArguments objectAtIndex:2];
	NSString *inTotalFree = [inArguments objectAtIndex:3];
	NSMutableDictionary *argsDict = [[[NSMutableDictionary alloc]initWithCapacity:UEX_PLATFORM_CALL_ARGS] autorelease];
	[argsDict setValue:inTradNum forKey:@"orderNumber"];
	[argsDict setValue:inSubject forKey:@"goodName"];
	[argsDict setValue:inBody forKey:@"goodDescribution"];
	[argsDict setValue:inTotalFree forKey:@"totalPrice"];
	payObj = [[AliPay alloc] initWithEuexObj:self];
	int  isSuccessPay =[payObj openAliPay:argsDict payInfo:self.payInfo];
	switch (isSuccessPay) {
		case 0:
			break;
		case 1:
			[self uexOnPayWithStatus:UEX_CPAYING des:@"支付中"];
			break;
		case 2:
			[self uexOnPayWithStatus:UEX_CPAYFAILED des:@"支付失败"];
			break;
		case 3:
			[self uexOnPayWithStatus:UEX_CPAYPLUGINERROR des:@"支付插件不完整"];
			break;
		default:
			break;
	}
}

-(void)setPayInfo:(NSMutableArray *)inArguments{
 	NSString *inPartner = [inArguments objectAtIndex:0];
	NSString *inSeller = [inArguments objectAtIndex:1];
	NSString *inRsaPrivateKey = [inArguments objectAtIndex:2];
	NSString *inRsaPublicKey = [inArguments objectAtIndex:3];
	NSString *inNotifyUrl = [inArguments objectAtIndex:4];
	payInfo = [[AliPayInfo alloc] init];
	[payInfo setPartner:inPartner];
	[payInfo setSeller:inSeller];
	[payInfo setRsaPrivate:inRsaPrivateKey];
	[payInfo setRsaPublic:inRsaPublicKey];
	[payInfo setNotifyUrl:inNotifyUrl];
}

-(void)uexOnPayWithStatus:(int)inStatus des:(NSString*)inDes{
	inDes =[inDes stringByReplacingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
	NSString *jsStr = [NSString stringWithFormat:@"if(uexPay.onStatus!=null){uexPay.onStatus(%d,\'%@\')}",inStatus,inDes];
	[meBrwView stringByEvaluatingJavaScriptFromString:jsStr];
}
-(NSString *)getPayPublicRsaKey{
	if (self.payInfo) {
		return payInfo.rsaPublic;
	}
    return nil;
}
- (void)parseURL:(NSURL *)url application:(UIApplication *)application {
    AlixPay *alixpay = [AlixPay shared];
    AlixPayResult *result = [alixpay handleOpenURL:url];
    self.jsStr = nil;
    if (result) {
        if (result.statusCode == 9000) {
            
            NSString *publicKey = [self getPayPublicRsaKey];
            
            if (publicKey==nil) {
                
                self.jsStr = [NSString stringWithFormat:@"if(%@!=null){%@(%d,\'%@\');}",@"uexPay.onStatus",@"uexPay.onStatus",UEX_CPAYSUCCESS,@"订单可能未支付成功,请联系支付宝公司进行确认"];
                
            } else {
                
                id<DataVerifier> verifier = CreateRSADataVerifier([NSString stringWithString:publicKey]);
                
                if ([verifier verifyString:result.resultString withSign:result.signString]) {
                    self.jsStr = [NSString stringWithFormat:@"if(%@!=null){%@(%d,\'%@\');}",@"uexPay.onStatus",@"uexPay.onStatus",UEX_CPAYSUCCESS,result.statusMessage];
                } else {
                    self.jsStr = [NSString stringWithFormat:@"if(%@!=null){%@(%d,\'%@\');}",@"uexPay.onStatus",@"uexPay.onStatus",UEX_CPAYPLUGINERROR,result.statusMessage];
                }
                
            }
            
        } else {
            
            self.jsStr = [NSString stringWithFormat:@"if(%@!=null){%@(%d,\'%@\');}",@"uexPay.onStatus",@"uexPay.onStatus",UEX_CPAYFAILED,result.statusMessage];
            
        }
    }
    
    [self performSelector:@selector(delayCB) withObject:self afterDelay:1.0];
}
-(void)delayCB{
    
    [meBrwView stringByEvaluatingJavaScriptFromString:self.jsStr];
}



@end

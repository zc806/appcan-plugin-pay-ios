//
//  AlixPay.m
//  AppCan
//
//  Created by AppCan on 11-10-26.
//  Copyright 2011 AppCan. All rights reserved.
//

#import "AliPay.h"
#import "DataSigner.h"
#import "EUExPay.h"
#import "AliPayInfo.h"

@implementation AliPay

-(id)initWithEuexObj:(EUExPay *)euexObj_ {
	if (self = [super init]) {
		euexObj = euexObj_;
	}
	return self;
}
-(int)openAliPay:(NSMutableDictionary *)argdict payInfo:(AliPayInfo *)payInfo{
	//get key
	//从用户设置读取支付信息
	NSString *partner;
	NSString *seller;
	NSString *privateKey;
	NSString *urlStr;
	if (payInfo) {
		partner = payInfo.partner;
		seller = payInfo.seller;
		privateKey = payInfo.rsaPrivate;
        urlStr = payInfo.notifyUrl;
        NSLog(@"urlstr = %@",urlStr);
	}else {
        //
    }
	
    if ([partner length]==0||[seller length]==0) {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"提示"
														message:@"缺少partner或者seller。"
													   delegate:self
											  cancelButtonTitle:@"确定"
											  otherButtonTitles:nil];
		[alert show];
		[alert release];
		return UEX_CPAYPLUGINERROR;
	}
	AlixPayOrder *payOrder = [[AlixPayOrder alloc] init];
	payOrder.partner = partner;
	payOrder.seller  = seller;
    NSLog(@"argsdict = %@",[argdict description]);
	 payOrder.tradeNO = [argdict valueForKey:@"orderNumber"];
 	payOrder.productName = [argdict valueForKey:@"goodName"];
 	payOrder.productDescription= [argdict valueForKey:@"goodDescribution"];
	payOrder.amount = [argdict valueForKey:@"totalPrice"];
	if (urlStr&&urlStr.length>0) {
        NSURL *url = [[NSURL alloc]initWithString:[urlStr  stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding]];
        payOrder.notifyURL = urlStr;
        [url release];
	}
	//设置appschame
	NSString *appScheme = nil;
	NSArray *scharray = [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleURLTypes"];
	if ([scharray count]>0) {
		NSDictionary *subDict = [scharray objectAtIndex:0];
		if ([subDict count]>0) {
			NSArray *urlArray = [subDict objectForKey:@"CFBundleURLSchemes"];
			if ([urlArray count]>0) {
				appScheme = [urlArray objectAtIndex:0];
			}
		}
	}
    //将商品信息拼接成字符串
	NSString *orderSpec = [payOrder description];
	//获取私钥并将商户信息签名,外部商户可以根据情况存放私钥和签名,只需要遵循RSA签名规范,并将签名字符串base64编码和UrlEncode
	id<DataSigner> signer = CreateRSADataSigner(privateKey);
	NSString *signedString = [signer signString:orderSpec];
	
	//将签名成功字符串格式化为订单字符串,请严格按照该格式
	NSString *orderString = nil;
	if (signedString != nil) {
		orderString = [NSString stringWithFormat:@"%@&sign=\"%@\"&sign_type=\"%@\"",
                       orderSpec, signedString, @"RSA"];
	}
	//获取安全支付单例并调用安全支付接口
	AlixPay * alixpay = [AlixPay shared];
	int ret = [alixpay pay:orderString applicationScheme:appScheme];
	if (ret == kSPErrorAlipayClientNotInstalled) {
		UIAlertView * alertView = [[UIAlertView alloc] initWithTitle:@"提示" 
															 message:@"您还没有安装支付宝的客户端，请先装" 
															delegate:self 
												   cancelButtonTitle:@"取消" 
												   otherButtonTitles:@"确定",nil];
		[alertView setTag:123];
		[alertView show];
		[alertView release];
		return UEX_CPAYPLUGINERROR;
	}
	else if (ret == kSPErrorSignError) {
		return UEX_CPAYPLUGINERROR;
	}
	return UEX_CPAYING;
}
- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex {
	if (alertView.tag == 123) {
		switch (buttonIndex) {
			case 0:
				[euexObj uexOnPayWithStatus:UEX_CPAYFAILED des:@"用户中途取消"];
				break;
			case 1:
			{
				NSString * URLString = @"http://itunes.apple.com/cn/app/id333206289?mt=8";
				[[UIApplication sharedApplication] openURL:[NSURL URLWithString:URLString]];
			
			break;
			}
			default:
				break;
		}

	}
}
-(void)dealloc{
	[super dealloc];
}
@end

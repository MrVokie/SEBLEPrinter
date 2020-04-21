//
//  SEPrinterManager.h
//  SEBLEPrinter
//
//  Created by Harvey on 16/5/5.
//  Copyright © 2016年 Halley. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>

#import "SEBLEConst.h"
#import "HLPrinter.h"

@class SEPrinterManager;
@protocol SEPrinterManagerDelegate <NSObject>

/** 返回扫描到的蓝牙 设备列表
 *  因为蓝牙模块一次返回一个设备，所以该方法会调用多次
 */
- (void)printerManager:(SEPrinterManager *)manager perpherals:(NSArray<CBPeripheral *> *)perpherals isTimeout:(BOOL)isTimeout;

/** 扫描蓝牙设备失败
 *
 */
- (void)printerManager:(SEPrinterManager *)manager scanError:(SEScanError)error;

/**
 *  连接蓝牙外设完成
 *
 *  @param manager
 *  @param perpheral 蓝牙外设
 *  @param error
 */
- (void)printerManager:(SEPrinterManager *)manager completeConnectPerpheral:(CBPeripheral *)perpheral error:(NSError *)error;

/**
 *  断开连接
 *
 *  @param manager
 *  @param peripheral 设备
 *  @param error      错误信息
 */
- (void)printerManager:(SEPrinterManager *)manager disConnectPeripheral:(CBPeripheral *)peripheral error:(NSError *)error;

@end


@interface SEPrinterManager : NSObject

/**< 蓝牙操作代理 */
@property (assign, nonatomic)   id<SEPrinterManagerDelegate>             delegate;

@property (strong, nonatomic, readonly)   CBPeripheral                *connectedPerpheral;    /**< 当前连接的外设 */

#pragma mark - bluetooth method

+ (instancetype)sharedInstance;

/**
 *  上次连接的蓝牙外设的UUIDString
 *
 *  @return UUIDString,没有时返回nil
 */
+ (NSString *)UUIDStringForLastPeripheral;

/**
 *  蓝牙外设是否已连接
 *
 *  @return YES/NO
 */
- (BOOL)isConnected;

/**
 *  开始扫描蓝牙外设
 *  @param timeout 扫描超时时间,设置为0时表示一直扫描
 */
- (void)startScanPerpheralTimeout:(NSTimeInterval)timeout;

/**
 *  开始扫描蓝牙外设，block方式返回结果
 *  @param timeout 扫描超时时间，设置为0时表示一直扫描
 *  @param success 扫描成功的回调
 *  @param failure 扫描失败的回调
 */
- (void)startScanPerpheralTimeout:(NSTimeInterval)timeout Success:(SEScanPerpheralSuccess)success failure:(SEScanPerpheralFailure)failure;

/**
 *  停止扫描蓝牙外设
 */
- (void)stopScan;

/**
 *  连接蓝牙外设,连接成功后会停止扫描蓝牙外设
 *
 *  @param peripheral 蓝牙外设
 */
- (void)connectPeripheral:(CBPeripheral *)peripheral;

/**
 *  连接蓝牙外设，连接成功后会停止扫描蓝牙外设，block方式返回结果
 *
 *  @param peripheral 要连接的蓝牙外设
 *  @param completion 完成后的回调
 */
- (void)connectPeripheral:(CBPeripheral *)peripheral completion:(SEConnectCompletion)completion;

/**
 *  完整操作，包括连接、扫描服务、扫描特性、扫描描述
 *
 *  @param peripheral 要连接的蓝牙外设
 *  @param completion 完成后的回调
 */
- (void)fullOptionPeripheral:(CBPeripheral *)peripheral completion:(SEFullOptionCompletion)completion;

/**
 *  取消某个蓝牙外设的连接
 *
 *  @param peripheral 蓝牙外设
 */
- (void)cancelPeripheral:(CBPeripheral *)peripheral;

/**
 *  自动连接上次的蓝牙外设
 *
 *  @param timeout
 *  @param completion
 */
- (void)autoConnectLastPeripheralTimeout:(NSTimeInterval)timeout completion:(SEConnectCompletion)completion;

/**
 *  设置断开连接的block
 *
 *  @param disconnectBlock
 */
- (void)setDisconnect:(SEDisconnect)disconnectBlock;

/**
 *  直接打印数据
 *
 *  @param result 结果
 */
- (void)printWithResult:(SEPrintResult)result;

/**
 *  打印自己组装的数据
 *
 *  @param data
 *  @param result 结果
 */
- (void)sendPrintData:(NSData *)data completion:(SEPrintResult)result;

@end

//------------------------------------------------------------------------------------------------------------------------------
//
//  ICADevices.h
//
//  Copyright (c) 2000-2010 Apple Inc. All rights reserved.
//
//  For bug reports, consult the following page onthe World Wide Web:
//  http://developer.apple.com/bugreporter/
//------------------------------------------------------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------------------------------------------------------
#import <ICADevices/ICD_CameraCalls.h>
#import <ICADevices/ICD_ScannerCalls.h>
#import <ICADevices/ICAApplication.h>
#import <CoreGraphics/CGColorSpace.h>

//------------------------------------------------------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

//------------------------------------------------------------------------------------------------------------------------------

extern const CFStringRef kICUTTypeRaw                                                 AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

// ICA Raw File Header
typedef struct ICARawFileHeader
{
    UInt32    imageDataOffset;
    UInt32    version;
    UInt32    imageWidth;
    UInt32    imageHeight;
    UInt32    bytesPerRow;
    UInt32    numberOfComponents;
    UInt32    bitsPerComponent;
    UInt32    bitsPerPixel;
    UInt32    cgColorSpaceModel;
    UInt32    bitmapInfo;
    UInt32    orientation;
    UInt32    dpi;
    char      colorSyncModeStr[64];
} ICARawFileHeader;

//------------------------------------------------------------------------------------------------------------------------------

CGColorSpaceRef ICDCreateColorSpace( UInt32 bitsPerPixel, UInt32 samplesPerPixel, ICAObject icaObject, CFStringRef colorSyncMode, CFDataRef abstractProfile, char* tmpProfilePath );

ICAError        ICDAddImageInfoToNotificationDictionary( CFMutableDictionaryRef dict, UInt32 width, UInt32 height, UInt32 bytesPerRow, UInt32 dataStartRow, UInt32 dataNumberOfRows, UInt32 dataSize, void* dataBuffer );

ICAError        ICDAddBandInfoToNotificationDictionary( CFMutableDictionaryRef dict, UInt32 width, UInt32 height, UInt32 bitsPerPixel, UInt32 bitsPerComponent, UInt32 numComponents, UInt32 endianness, UInt32 pixelDataType, UInt32 bytesPerRow, UInt32 dataStartRow, UInt32 dataNumberOfRows, UInt32 dataSize, void* dataBuffer );
    
ICAError        ICDSendNotification( ICASendNotificationPB* pb );

ICAError        ICDSendNotificationAndWaitForReply( ICASendNotificationPB* pb );

//------------------------------------------------------------------------------------------------------------------------------

extern int          ICLoggingEnabled;
extern int          ICLoggingLevelMask;

extern const int   ICLoggingLevelError;
extern const int   ICLoggingLevelWarning;
extern const int   ICLoggingLevelBasicInfo;
extern const int   ICLoggingLevelVerboseInfo;
extern const int   ICLoggingLevelTimingInfo;

void    __ICLog( const char* format, ... ); // This function MUST be called only if ICLoggingEnabled is true.

#define __ICLOG(logLevel, params)   { if (ICLoggingEnabled && (logLevel & ICLoggingLevelMask)) __ICLog params; }

//------------------------------------------------------------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

//------------------------------------------------------------------------------------------------------------------------------

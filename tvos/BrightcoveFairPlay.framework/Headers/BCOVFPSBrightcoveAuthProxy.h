//
// BCOVFPSBrightcoveAuthProxy.h
// BCOVFairPlay
//
// Copyright (c) 2015 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import "BCOVFPSComponent.h"


/**
 * Class responsible for interacting with fps.brightcove.com.
 */
@interface BCOVFPSBrightcoveAuthProxy : NSObject <BCOVFPSAuthorizationProxy>

/**
 * NSURLSession shared across all network calls to the BCOVFPSBrightcoveAuthProxy.
 * This object is created when the Playback Service is initialized.
 * If you wish to use your own NSURLSession you can set it here.
 * If set to nil, the default NSURLSession will be re-created.
 */
@property (nonatomic, strong, null_resettable) NSURLSession *sharedURLSession;

/**
 *  Creates a BCOVFPSAuthorizationProxy to interacts with fps.brightcove.com.
 *
 *  @param appId The application id registered with fps.brightcove.com. Must not be nil.
 *  @param pubId The publisher id registered with fps.brightcove.com. Must not be nil.
 *
 *  @return An initialized proxy.
 */
- (nullable instancetype)initWithApplicationId:(nonnull NSString *)appId publisherId:(nonnull NSString *)pubId NS_DESIGNATED_INITIALIZER;

/**
 *  Retrieves the Application Certificate for fps.brightcove.com. This should be done 
 *  as soon as possible and should be cached for no longer than 6 hours.
 *
 *  @param completionHandler Executed when the request is completed. If applicationCetificate
 *                           is nil, the error will be populated. The block
 *                           will be executed on the main thread.
 */
- (void)retrieveApplicationCertificate:(nonnull void (^)(NSData * __nullable applicationCetificate, NSError * __nullable error))completionHandler;

@end


@interface BCOVFPSBrightcoveAuthProxy (Unavailable)

- (nullable instancetype)init __attribute__((unavailable("Use `-[BCOVFPSBrightcoveAuthProxy initWithApplicationId:publisherId:]` instead.")));

@end

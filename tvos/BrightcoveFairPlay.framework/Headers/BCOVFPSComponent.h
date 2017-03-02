//
// BCOVFPSComponent.h
// BrightcoveFairPlay
//
// Copyright (c) 2016 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <BrightcovePlayerSDK/BCOVPlayerSDKManager.h>

/**
 * Error domain for FairPlay related errors.
 */
extern NSString * __nonnull const kBCOVFPSErrorDomain;

/**
 *  Error occured requesting content key.
 */
extern const NSInteger kBCOVFPSErrorCodeStreamingContentKeyRequest;

/**
 *  Error occured requesting application certificate.
 */
extern const NSInteger kBCOVFPSErrorCodeApplicationCertificateRequest;


/**
 *  Implement this protocol when interacting with a custom FPS license server.
 */
@protocol BCOVFPSAuthorizationProxy <NSObject>

@optional

/**
 *  Optional method.
 *  Implement this method to handle retrieving the content identifier from the loading request.
 *  This is called for each asset.
 *  No guarantee is made as to the thread that this is called on.
 *  You should return the content identifier corresponding to this loading request.
 *  This is typically extracted from the "skd://..." URL in loadingRequest.request.URL.
 *  The content identifier will be passed to [AVAssetResourceLoadingRequest
 *  streamingContentKeyRequestDataForApp:contentIdentifier:options:error:]
 *  to retrieve the SPC.
 *
 *  If this method is not provided, the default method will be used. The default method
 *  removes "skd://" from loadingRequest.request.URL to generate the content identifier.
 *
 *  @param loadingRequest The skd:// loading request made for the asset.
 */
- (nullable NSData *)contentIdentifierFromLoadingRequest:(nonnull AVAssetResourceLoadingRequest *)loadingRequest;

@required

/**
 *  Implement this method to handle retrieving the content key. This is called for each asset.
 *  No guarantee is made as to the thread that this is called on.
 *
 *  @param loadingRequest    The "skd://..." loading request made for the asset.
 *  @param keyRequest        The key request data returned by [AVAssetResourceLoadingRequest streamingContentKeyRequestDataForApp:contentIdentifier:options:error:].
 *  @param source            The BCOVSource
 *  @param completionHandler The completion handler to return the content key. If returning an error, you must leave the contentkey and response parameters nil.
 */
- (void)encryptedContentKeyForLoadingRequest:(nonnull AVAssetResourceLoadingRequest *)loadingRequest
                           contentKeyRequest:(nonnull NSData *)keyRequest
                                      source:(nonnull BCOVSource *)source
                           completionHandler:(nonnull void (^)(NSURLResponse * __nullable response,
                                                               NSData * __nullable contentKey,
                                                               NSError * __nullable error))completionHandler;

@end


/**
 * Adds methods to BCOVPlayerSDKManager to create FairPlay players and session providers.
 */
@interface BCOVPlayerSDKManager (BCOVFPSAdditions)

/**
 *  Creates and returns a FairPlay enabled playback controller.
 *  If you are using Video Cloud Dynamic Delivery, a Fairplay application certificate will
 *  automatically be retrieved from the BCOVVideo when you play a playlist.
 *  You can still supply an application certificate separately by calling
 * `BCOVBasicPlaybackController addApplicationCertificate:identifier:`.
 *
 *  @param proxy    The BCOVFPSAuthorizationProxy to use for this session provider.
 *                  Must not be nil.
 *
 *  @return A playback controller.
 */
- (nonnull id<BCOVPlaybackController>)createFairPlayPlaybackControllerWithAuthorizationProxy:(nonnull id<BCOVFPSAuthorizationProxy>)proxy;

/**
 *  Creates and returns a FairPlay session provider with the specified parameters.
 *  If you are using Video Cloud Dynamic Delivery, a Fairplay application certificate will
 *  automatically be retrieved from the BCOVVideo when you play a playlist.
 *  You can still supply an application certificate separately by calling
 * `BCOVBasicPlaybackController addApplicationCertificate:identifier:`.
 *
 *  @param proxy    The BCOVFPSAuthorizationProxy to use for this session provider.
 *                  Must not be nil.
 *  @param provider And upstream session provider to link to. If nil, a BCOVBasicSessionProvider
 *                  will be used.
 *
 *  @return A session provider.
 */
- (nonnull id<BCOVPlaybackSessionProvider>)createFairPlaySessionProviderWithAuthorizationProxy:(nonnull id<BCOVFPSAuthorizationProxy>)proxy
                                                                       upstreamSessionProvider:(nullable id<BCOVPlaybackSessionProvider>)provider;

/**
 *  Creates and returns a FairPlay enabled playback controller.
 *
 *  @param appCert  The Fairplay Application Certificate for this session provider.
 *                  If using Brightcove FPS Server, this can retrieved by
 *                  BCOVFPSBrightcoveAuthProxy. Can be nil.
 *  @param proxy    The BCOVFPSAuthorizationProxy to use for this session provider.
 *                  Must not be nil.
 *  @param viewStrategy The view strategy to use.
 *
 *  @return A playback controller.
 */
- (nonnull id<BCOVPlaybackController>)createFairPlayPlaybackControllerWithApplicationCertificate:(nullable NSData *)appCert
                                                                              authorizationProxy:(nonnull id<BCOVFPSAuthorizationProxy>)proxy
                                                                                    viewStrategy:(nullable BCOVPlaybackControllerViewStrategy)viewStrategy;

/**
 *  Creates and returns a FairPlay session provider with the specified parameters.
 *
 *  @param appCert  The FairPlay Application Certificate for this session provider.
 *                  If using Brightcove FPS Server, this can retrieved by
 *                  BCOVFPSBrightcoveAuthProxy. Can be nil.
 *  @param proxy    The BCOVFPSAuthorizationProxy to use for this session provider.
 *                  Must not be nil.
 *  @param provider And upstream session provider to link to. If nil, a BCOVBasicSessionProvider
 *                  will be used.
 *
 *  @return A session provider.
 */
- (nonnull id<BCOVPlaybackSessionProvider>)createFairPlaySessionProviderWithApplicationCertificate:(nullable NSData *)appCert
                                                                                authorizationProxy:(nonnull id<BCOVFPSAuthorizationProxy>)proxy
                                                                           upstreamSessionProvider:(nullable id<BCOVPlaybackSessionProvider>)provider;

@end


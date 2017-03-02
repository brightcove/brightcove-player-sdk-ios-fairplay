# 1.1.3

### Additions and Improvements

With this verison of the Brightcove FairPlay plugin, creation of FairPlay playback controllers and session providers is simplified, as you no longer need to instantiate them with a FairPlay application certificate. You can add application certificates later, and also add multiple application certificates, allowing a single playback controller instance to play FairPlay-encrypted content from multiple accounts.

Also new is support for Video Cloud Dynamic Delivery. When using FairPlay-encrypted content through Dynamic Delivery, you don't need to provide an application certificate at all. The FairPlay plugin will determine and retrieve the correct application certificate to use, and cache it for playing subsequent videos. See README.md for full details.

Note: The method to add a FairPlay application certificate is available in the `BCOVPlaybackController` class in the core Brightcove Native Player SDK framework. Because of this, use of the Brightcove FairPlay plugin requires at least version 5.3.2 of the core framework.

Changes include:

* The `BCOVFPSAuthorizationProxy` protocol has a new optional method, `- (nullable NSData *)contentIdentifierFromLoadingRequest:(nonnull AVAssetResourceLoadingRequest *)loadingRequest`. If you are writing your own authorization proxy, you can implement this method to extract the the video's content identifier from the loading request. If this method is not supplied, the default method will extract the content identifier by removing `"skd://"` from the request URL string.

* The constant `kBCOVFPSErrorCodeApplicationCertificateRequest` was added to assist with diagnosing errors related to requesting application certificates.

* The `BCOVPlayerSDKManager` method `-createFairPlayPlaybackControllerWithAuthorizationProxy:` was added to simplify creation of the FairPlay playback controller. You can add application certificates after creation, or in the case of Dynamic Creation you don't need to add them at all.

* The `BCOVPlayerSDKManager` method `-createFairPlaySessionProviderWithAuthorizationProxy:upstreamSessionProvider:` was added to simplify creation of the FairPlay session provider. You can add application certificates after creation, or in the case of Video Cloud Dynamic Delivery you don't need to add them at all.

* The application certificate passed to the following two `BCOVPlayerSDKManager ` methods can now be nil. (There is a new method in the `BCOVPlaybackController` protocol to add application certificates to the playback controller after it is created: `-  addFairPlayApplicationCertificate:identifier:`.)
  - `-createFairPlayPlaybackControllerWithApplicationCertificate:authorizationProxy:viewStrategy:`
  - `-createFairPlaySessionProviderWithApplicationCertificate:authorizationProxy:upstreamSessionProvider:`



# 1.1.2

### Additions and Improvements
* The podspec now supports version 5.3 of the Brightcove Player SDK for iOS.
* Stability enhancements.

# 1.1.1

### Additions and Improvements
* The minimum supported deployment target is now iOS 8.0.

# 1.1.0

### Additions and Improvements
* Internal improvements.
* You must use the Brightcove Player SDK for iOS version 5.1 or higher.

# 1.0.3

### Additions and Improvements
* Allow overriding the base URL for application certificate requests through the `BCOVFPSBrightcoveAuthProxy`'s `fpsBaseURL` property.
* Allow setting the key request URL for license requests through the `BCOVFPSBrightcoveAuthProxy`'s `keyRequestURL` property.

### Deprecations
* In `BCOVFPSBrightcoveAuthProxy.h`, the method `- (nullable instancetype)initWithApplicationId:(nonnull NSString *)appId publisherId:(nonnull NSString *)pubId` has been deprecated.
 
	Use the method
 	`- (nullable instancetype)initWithPublisherId:(NSString *)pubId applicationId:(nullable NSString *)appId` instead.

	 Note that the arguments are the same, but have been interchanged.

# 1.0.2
### Additions and Improvements
* Improvements to error handling.

# 1.0.1
### Additions and Improvements
* Reformatted the framework's short version string to comply with App Store submission requirements.

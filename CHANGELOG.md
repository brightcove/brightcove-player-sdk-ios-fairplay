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

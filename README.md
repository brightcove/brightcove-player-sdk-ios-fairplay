# FairPlay plugin for Brightcove Player SDK for iOS, version 1.0.0.17

Supported Platforms
===================

iOS 7.0 and above.  
tvOS 9.0 and above.

Installation
============
The FairPlay plugin for the Brightcove Player SDK provides two installation packages for iOS, a static library framework and a dynamic framework. The static library target supports deployment on iOS 7 while the dynamic framework only supports iOS 8 and above.

The FairPlay plugin provides a dynamic framework to support tvOS 9.0 and above.

**While the plugin contains simulator architectures, you can not play FPS protected content in the simulator. This is a FairPlay limitation.**

CocoaPods
--------------

You can use [CocoaPods][cocoapods] to add the Brightcove Player SDK to your project. You can find the latest `Brightcove-Player-SDK-FairPlay` podspec [here][podspecs]. The podspec supports both iOS and tvOS. CocoaPods 0.39 or newer is required.

Specifying the default pod `Brightcove-Player-SDK-FairPlay` will install the static library framework. To install the dynamic framework, declare the pod with the `dynamic` subspec: `Brightcove-Player-SDK-FairPlay/dynamic`

Static Framework example:

    pod 'Brightcove-Player-SDK-FairPlay'
    
Dynamic Framework example:

    pod 'Brightcove-Player-SDK-FairPlay/dynamic'    

Manual
--------------

To add the FairPlay plugin for Brightcove Player SDK to your project manually:

1. Install the latest version of the [Brightcove Player SDK][bcovsdk].
2. Download the latest zipped release of the plugin from our [release page][release].
3. Add the `BrightcoveFairPlay.framework` to your project.
4. On the "Build Settings" tab of your application target, ensure that the "Framework Search Paths" include the path to the framework. This should have been done automatically unless the framework is stored under a different root directory than your project.
5. On the "General" tab of your application target, add the following to the "Link
    Binary With Libraries" section:
    * `BrightcoveFairPlay.framework`  
6. (Dynamic Framework only) On the "General" tab of your application target, add 'BrightcoveFairPlay.framework' to the "Embedded Binary" section.
7. (Dynamic Framework only) On the "Build Phases" tab, add a "Run Script" phase with the command `bash ${BUILT_PRODUCTS_DIR}/${FRAMEWORKS_FOLDER_PATH}/BrightcoveFairPlay.framework/strip-frameworks.sh`. Check "Run script only when installing". This will remove unneeded architectures from the build, which is important for App Store submission. ([rdar://19209161][19209161])
8. (Static Framework only) On the "Build Settings" tab of your application target, add `-ObjC` to the "Other Linker Flags" build setting.

Imports
--------------
The Brightcove Player SDK for iOS can be imported into code a few different ways; `@import BrightcoveFairPlay;`, `#import <BrightcoveFairPlay/BrightcoveFairPlay.h>` or `#import <BrightcoveFairPlay/[specific class].h>`.
    
[cocoapods]: http://cocoapods.org
[podspecs]: https://github.com/CocoaPods/Specs/tree/master/Specs/Brightcove-Player-SDK-FairPlay
[release]: https://github.com/brightcove/brightcove-player-sdk-ios-fairplay/releases
[19209161]: https://openradar.appspot.com/19209161

Quick Start
===========
Brightcove FairPlay is a bridge between Apple FairPlay and the [Brightcove Player SDK for iOS][bcovsdk]. Its use is relatively straightforward.

	    @property (nonatomic, strong) id<BCOVPlaybackController> playbackController;
	
	    -------
	
	[1] BCOVFPSBrightcoveAuthProxy *proxy = [[BCOVFPSBrightcoveAuthProxy alloc] initWithApplicationId:<app-id>
	                                                                                      publisherId:<pub-id>
	    
	[2] [proxy retrieveApplicationCertificate:^(NSData * _Nullable applicationCetificate, NSError * _Nullable error) {
	    
	        if (applicationCetificate)
	        {
	            BCOVPlayerSDKManager *sdkManager = [BCOVPlayerSDKManager sharedManager];
	            
	[3]         id<BCOVPlaybackController> playbackController =
	                        [sdkManager createFairPlayPlaybackControllerWithApplicationCertificate:applicationCetificate
	                                                                            authorizationProxy:proxy
	                                                                                  viewStrategy:nil];
	            playbackController.delegate = self;
	            _playbackController = playbackController;
	            [self.view addSubview:playbackController.view];
	            
	            BCOVPlaybackService *playbackService = [[BCOVPlaybackService alloc] initWithAccountId:<account-id> policyKey:<policy-key>];
	            
	            [playbackService findVideoWithVideoID:<video-id>
	                                       parameters:@{}
	                                       completion:^(BCOVVideo *video, NSDictionary *jsonResponse, NSError *error) {
	                
	                if(video)
	                {
                       [self.playbackController setVideos:@[video]];
	                }
	                
	            }];
	        }
	    
	    }];
    
Let's break this code down into steps, to make it a bit simpler to digest:

1. Create a `BCOVFPSBrightcoveAuthProxy` object using the application id and publisher id used to register your FairPlay credentials with fps.brightcove.com.
2. Using the proxy, retrieve the FairPlay application certificate. In an actual app, you might want to do this as soon as the app starts up, to have it ready when it is time to play content.
3. Brightcove FairPlay adds some category methods to BCOVPlaybackManager. Pass the application certificate and the proxy object to `-[BCOVPlayerSDKManager createFairPlayPlaybackControllerWithApplicationCertificate:authorizationProxy:viewStrategy:]`. If you are using your own FairPlay license server, this is where you would provide you own proxy implementation.

If you have questions or need help, we have a support forum for Brightcove's native Player SDKs at [https://groups.google.com/forum/#!forum/brightcove-native-player-sdks][forum] .

[bcovsdk]: https://github.com/brightcove/brightcove-player-sdk-ios
[forum]: https://groups.google.com/forum/#!forum/brightcove-native-player-sdks

Requesting the Application Certificate
===========
In order to play FairPlay protected content, you must initialize the Brightcove FairPlay plugin with the Application Certificate data associated with the content. The `BCOVFPSBrightcoveAuthProxy` offers a convenience method to retrieve this from fps.brightcove.com.

In order to provide the best experience possible, it is recommended that you retrieve this certificate before the user tries to initiate playback, in order to decrease the amount of time it takes to start playing video. 

Using another FairPlay license Server
===========
The `BCOVFPSBrightcoveAuthProxy` is intended to interface with `fps.brightcove.com`. If you need to use another FairPlay license server, you can implement the `BCOVFPSAuthorizationProxy` protocol to handle the license communication.

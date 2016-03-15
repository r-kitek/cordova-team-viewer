/*
 * Copyright 2013-2014 TeamViewer (www.teamviewer.com).  All rights reserved.
 *
 * Please refer to the end user license agreement (EULA) and license
 * information associated with this source code for terms and
 * conditions that govern your use of this software.
 *
 */

#import <Foundation/Foundation.h>

@protocol TVSessionCreationDelegate;
@class TVSession;

__attribute__((visibility("default")))
extern NSString * const TVSimulatorException; // The function you tried to use, doesn't work on the simulator.

__attribute__((visibility("default")))
extern NSString * const TVMissingBundleException; // The ScreenSharingSDK resource bundle is missing.

/**
 * TVSessionFactory provides methods to create a new TVSession or to get the current running TVSession.
 *
 * @warning The ScreenSharingSDK only supports one session at once. If createTVSessionWithToken:delegate: is called during a session that is already running,
 * the TVSessionCreationDelegate will trigger the error delegate methode (see TVSessionCreationError)
 */
__attribute__((visibility("default")))
@interface TVSessionFactory : NSObject

/**
 * Creates a new TVSession. (Throws NSException with name TVSimulatorException and TVMissingBundleException)
 *
 * @param sdkToken A valid ScreenSharingSDK token.
 * @param delegate The delegate for the session creation. The session creation calls methodes on this delegate
 *	if an error occurs or the session creation was successful. Delegate methodes are called
 *	on the same thread called this method.
 */
+ (void)createTVSessionWithToken:(NSString*)sdkToken delegate:(id<TVSessionCreationDelegate>)delegate;

@end

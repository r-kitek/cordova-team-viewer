/*
 * Copyright 2013-2014 TeamViewer (www.teamviewer.com).  All rights reserved.
 *
 * Please refer to the end user license agreement (EULA) and license
 * information associated with this source code for terms and
 * conditions that govern your use of this software.
 *
 */

#import <Foundation/Foundation.h>

@protocol TVSessionDelegate;
@class TVSessionConfiguration;
/**
 * TVSession provides methodes to start and stop a session. The session delegate object gets notified if an error occured or the session ended. A TVSession can only be created by TVSessionFactory.
 */
__attribute__((visibility("default")))
@interface TVSession : NSObject

/**
 * Starts the TVSession with a TVSessionConfiguration object.
 *
 * @param configuration Session configuration object (see TVSessionConfiguration)
 */
- (void)startWithConfiguration:(TVSessionConfiguration*)configuration;

/**
 * Stops this session. If the session is finished it can't be started again.
 */
- (void)stop;

/**
 * Set the session delegate for this session. The session calls methods on this delegate
 * if an error occurs or the session finished. Delegate methods are called
 * on the same thread that called this method.
 * @param delegate Session delegate
*/
- (void)setSessionDelegate:(id<TVSessionDelegate>)delegate;

@end
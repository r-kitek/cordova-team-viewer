/*
 * Copyright 2013-2014 TeamViewer (www.teamviewer.com).  All rights reserved.
 *
 * Please refer to the end user license agreement (EULA) and license
 * information associated with this source code for terms and
 * conditions that govern your use of this software.
 *
 */

#import <Foundation/Foundation.h>

__attribute__((visibility("default")))
extern NSString *const TVSessionCreationErrorDomain;

/**
 * Errors which could occur during the session creation process.
 */
typedef NS_ENUM(NSInteger, TVSessionCreationError)
{
	/** 
	 * An unexpected internal error occured.
	 */
	TVSessionCreation_InternalError = 0,
    
    /**
     * Connection to the TeamViewer Server failed or Network is disabled.
     */
    TVSessionCreation_NoNetworkConnection = 1,
	
	/** 
	 * The device OS Version is not supported.
	 */
	TVSessionCreation_DeviceOSNotSupported = 2,
	
	/**
	 * There is already a session running or in the process of being created.
	 */
	TVSessionCreation_SessionAlreadyRunning = 3,
	
	/**
	 * The supplied SDK Token was not accepted by the TeamViewer server, because it is
	 * invalid or the check failed due to a network error.
	 */
	TVSessionCreation_TokenInvalid = 4,
	
	/**
	 * The user cancelled the creation of a new session.
	 **/
	TVSessionCreation_UserCancelled = 5,
};

@class TVSession;

/**
 * The TVSessionCreationDelegate protocol defines methodes, that are used to receive
 * feedback from the TVSessionFactory class.
 */
__attribute__((visibility("default")))
@protocol TVSessionCreationDelegate <NSObject>
@required
/**
 * Tells the delegate that a TVSession was created sucessfully.
 *
 * @param session The new created TVSession object.
 */
- (void)sessionCreationSuccess:(TVSession*)session;
@optional
/**
 * Tells the delegate that an error occured during the session creation.
 *
 * @param error Describes the problem that occured during the session creation. See
 * TVSessionCreationError for a list of errors that can occur.
 */
- (void)sessionCreationFailed:(NSError*)error;
@end

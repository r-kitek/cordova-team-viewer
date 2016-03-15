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
extern NSString *const TVSessionErrorDomain;

/**
 * Errors which could occur during a TVSession.
 */
typedef NS_ENUM(NSInteger, TVSessionError)
{
    /**
	 * An unexpected internal error occurred.
	 */
    TVSession_InternalError = 0,
    
    /**
	 * The supplied session code to start the session is already closed.
	 */
    TVSession_SessionCodeClosed = 1,
    
    /**
	 * The supplied session code to start the session is already expired.
	 */
	TVSession_SessionCodeExpired = 2,
    
    /**
	 * The supplied session code to start the session does not exist or is invalid.
	 */
	TVSession_SessionCodeInvalid = 3,
    
    /**
	 * Generation of a new session code failed due to a connection error or an IO error
	 * during configuration processing.
	 */
    TVSession_SessionCodeGenerationFailed = 4,
    
    /**
	 * The configuration linked with the supplied configurationID does not exist.
	 */
    TVSession_ConfigurationIDNonexistent = 5,
    
    /**
     * The configuration linked with the supplied configurationID cannot be used for generating new session codes.
     */
    TVSession_ConfigurationInvalidContent = 6,
};

@class TVSession;

/**
 * TVSessionDelegate protocol declares methods that should be implemented by the delegate of the TVSession object.
 */
__attribute__((visibility("default")))
@protocol TVSessionDelegate <NSObject>
@optional
/**
 * Tells the delegate that an error occurred during the session.
 *
 * @param error Describes the problem that occured during the session.
 *
 * @discussion In the case of an error, the TVSession will be closed.
 *
 * See TVSessionError for a list of errors that can emerge.
 */
- (void)sessionDidFailWithError:(NSError*)error;

/**
 * Tells the delegate that the session did end. It's not possible to restart the TVSession, a new TVSession can only created by TVSessionFactory.
 */
- (void)sessionDidEnd;
@end
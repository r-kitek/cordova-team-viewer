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
extern NSString * const TVIllegalArgumentException; // One of the arguments passed isn't valid. See reason for details.

@class TVSessionConfiguration;

/**
 * TVSessionConfigurationBuilder is used by the TVSessionConfiguration method tvsessionConfigurationWithBlock: to create a new TVSessionConfiguration.
 *
 * A TVSession can be started with an existing session code (property sessionCode) or a configuration id (property configurationId). Don't set both properties in the same configuration.
 * The properties sessionCodeName and sessionCodeDescription can only be used in combination with configurationId.
 */
__attribute__((visibility("default")))
@interface TVSessionConfigurationBuilder : NSObject

/**
 * A session code that was created by TeamViewer or TeamViewer Management Console (e.g. s55-555-555)
 */
@property (nonatomic, retain) NSString* sessionCode;

/**
 * Configuration id created in the TeamViewer Management Console. A new session code will be generated, if the configurationId is valid.
 */
@property (nonatomic, retain) NSString* configurationId;

/**
 * Session code name that will be shown in TeamViewer or TeamViewer Management Console. Can only be used in combination with configurationId.
 */
@property (nonatomic, retain) NSString* serviceCaseName;

/**
 * Service case description for the session code. Can only be used in combination with configurationId.
 */
@property (nonatomic, retain) NSString* serviceCaseDescription;
@end

/**
 * TVSessionConfiguration contains all informations that are necessary to start a TVSession.
 */
__attribute__((visibility("default")))
@interface TVSessionConfiguration : NSObject

/**
 * A session code that was created by TeamViewer or TeamViewer Management Console (e.g. s55-555-555)
 */
@property (nonatomic, readonly, copy) NSString* sessionCode;

/**
 * Configuration Id (Base36) created in the TeamViewer Management Console. A new session code will be generated, if the configurationId is valid.
 */
@property (nonatomic, readonly, copy) NSString* configurationId;

/**
 * Session case name that will be shown in TeamViewer or TeamViewer Management Console. Can only be used in combination with configurationId.
 */
@property (nonatomic, readonly, copy) NSString* serviceCaseName;

/**
 * Service case description for the session code. Can only be used in combination with configurationId.
 */
@property (nonatomic, readonly, copy) NSString* serviceCaseDescription;

typedef void(^TVSessionConfigurationBuilderBlock)(TVSessionConfigurationBuilder *builder);

/**
 * Returns a new TVSessionConfiguration. (Throws NSException with name TVIllegalArgumentException)
 *
 * @param block Configuration Builder block. Will be called durring TVSessionConfiguration creation.
 *
 * @return TVSessionConfiguration object or nil if the supplied informations are invalid (see TVSessionConfigurationBuilder).
 */
+ (instancetype)tvSessionConfigurationWithBlock:(TVSessionConfigurationBuilderBlock)block;

@end

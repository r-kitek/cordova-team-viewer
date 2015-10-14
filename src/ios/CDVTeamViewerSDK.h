//
//  CDVTeamViewerSDK.h
//
//
//  Created by Vladislav Dugnist on 14/10/15.
//
//

#import <Cordova/CDV.h>

@interface CDVTeamViewerSDK : CDVPlugin

- (void)openSessionWithConfigurationId:(CDVInvokedUrlCommand *)command;
- (void)openSessionWithSessionCode:(CDVInvokedUrlCommand *)command;
- (void)closeCurrentSession:(CDVInvokedUrlCommand *)command;

@end

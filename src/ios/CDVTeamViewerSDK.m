//
//  CDVTeamViewerSDK.m
//
//
//  Created by Vladislav Dugnist on 14/10/15.
//
//

#import "CDVTeamViewerSDK.h"
#import <ScreenSharingSDK/ScreenSharingSDK.h>

@interface CDVTeamViewerSDK () <TVSessionCreationDelegate>
@property (nonatomic) TVSession *currentSession;
@property (nonatomic) TVSessionConfiguration *currentSessionConfiguration;
@property (nonatomic) NSString *currentCallbackId;
@end

@implementation CDVTeamViewerSDK

- (void)openSessionWithConfigurationId:(CDVInvokedUrlCommand *)command
{
    if ([command.arguments[0] isEqual:[NSNull null]] || [command.arguments[1] isEqual:[NSNull null]])
    {
        CDVPluginResult *result = [CDVPluginResult resultWithStatus:CDVCommandStatus_IO_EXCEPTION
                                                    messageAsString:@"Missing required parameters: [token, configurationId]"];
        [self.commandDelegate sendPluginResult:result callbackId:command.callbackId];
        return;
    }

    NSString *token = command.arguments[0];
    NSString *configurationId = command.arguments[1];
    NSString *name = command.arguments[2];
    NSString *description = command.arguments[3];

    if ([name isEqual:[NSNull null]]) name = nil;
    if ([description isEqual:[NSNull null]]) description = nil;

    TVSessionConfiguration *sessionConfiguration =
        [TVSessionConfiguration tvSessionConfigurationWithBlock:^(TVSessionConfigurationBuilder *builder) {
            builder.configurationId = configurationId;
            builder.serviceCaseName = name;
            builder.serviceCaseDescription = description;
        }];

    [self openSessionWithConfiguration:sessionConfiguration token:token command:command];
}

- (void)openSessionWithSessionCode:(CDVInvokedUrlCommand *)command
{
    if ([command.arguments[0] isEqual:[NSNull null]] || [command.arguments[1] isEqual:[NSNull null]])
    {
        CDVPluginResult *result = [CDVPluginResult resultWithStatus:CDVCommandStatus_IO_EXCEPTION
                                                    messageAsString:@"Missing required parameter: [token, sessionCode]"];
        [self.commandDelegate sendPluginResult:result callbackId:command.callbackId];
        return;
    }

    NSString *token = command.arguments[0];
    NSString *sessionCode = command.arguments[1];

    TVSessionConfiguration *configuration = [TVSessionConfiguration tvSessionConfigurationWithBlock:^(TVSessionConfigurationBuilder *builder) {
        builder.sessionCode = sessionCode;
    }];

    [self openSessionWithConfiguration:configuration token:token command:command];
}

- (void)closeCurrentSession:(CDVInvokedUrlCommand *)command
{
    CDVPluginResult *result = nil;

    if (self.currentSession) {
        [self.currentSession stop];
        result = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
    } else {
        result = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"Session already closed"];
    }

    self.currentSession = nil;

    [self.commandDelegate sendPluginResult:result callbackId:command.callbackId];
}


- (void)openSessionWithConfiguration:(TVSessionConfiguration *)config
                               token:(NSString *)token
                             command:(CDVInvokedUrlCommand *)command
{
    self.currentCallbackId = command.callbackId;
    self.currentSessionConfiguration = config;
    [TVSessionFactory createTVSessionWithToken:token delegate:self];
}

- (void)sessionCreationSuccess:(TVSession *)session
{
    [session startWithConfiguration:self.currentSessionConfiguration];

    CDVPluginResult *result = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
    [self.commandDelegate sendPluginResult:result callbackId:self.currentCallbackId];
    [self cleanup];
}

- (void)sessionCreationFailed:(NSError *)error
{
    CDVPluginResult *result = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:error.localizedDescription];
    [self.commandDelegate sendPluginResult:result callbackId:self.currentCallbackId];
    [self cleanup];
}

- (void)cleanup
{
    self.currentCallbackId = nil;
    self.currentSessionConfiguration = nil;
}

@end

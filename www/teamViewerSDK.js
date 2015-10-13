module.exports =
{
    openSessionWithConfigurationId: function(token, configurationId, name, description, successCallback, failureCallback)
    {
      cordova.exec(successCallback,
                   failureCallback,
                   "TeamViewerSDK",
                   "openSessionWithConfigurationId",
                   [token, configurationId, name, description]);
    },
    openSessionWithSessionCode: function(token, sessionCode, successCallback, failureCallback)
    {
      cordova.exec(successCallback,
                   failureCallback,
                   "TeamViewerSDK",
                   "openSessionWithSessionId",
                   [token, sessionCode]);
    },
    closeCurrentSession: function()
    {
      cordova.exec(successCallback,
                   failureCallback,
                   "TeamViewerSDK",
                   "closeCurrentSession",
                   null);
    }
};

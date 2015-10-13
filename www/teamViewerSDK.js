module.exports =
{
    openSessionWithConfigurationId: function(token, configurationId, name, description, successCallback, failureCallback)
    {
      cordova.exec(successCallback,
                   failureCallback,
                   "TeamViewerSDK",
                   "alert",
                   [token, configurationId, name, description]);
    },
    openSessionWithSessionId: function(token, sessionId, name, description, successCallback, failureCallback)
    {
      cordova.exec(successCallback,
                   failureCallback,
                   "TeamViewerSDK",
                   "alert",
                   [token, sessionId, name, description]);
    },
    closeCurrentSession: function()
    {
      cordova.exec(successCallback,
                   failureCallback,
                   "TeamViewerSDK",
                   "alert",
                   [token, configurationId, name, description]);
    }
};

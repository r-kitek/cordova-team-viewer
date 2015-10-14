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
                   "openSessionWithSessionCode",
                   [token, sessionCode]);
    },
    closeCurrentSession: function(successcallback, failureCallback)
    {
      cordova.exec(successcallback,
                   failureCallback,
                   "TeamViewerSDK",
                   "closeCurrentSession",
                   null);
    }
};

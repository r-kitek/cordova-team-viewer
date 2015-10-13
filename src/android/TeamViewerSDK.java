package com.cordova.teamViewerSDK;

import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaInterface;
import org.apache.cordova.CordovaPlugin;
import org.apache.cordova.CordovaWebView;
import org.apache.cordova.PluginResult;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

public class TeamViewerSDK extends CordovaPlugin {

  public boolean execute(String action, JSONArray args, CallbackContext callbackContext)
      throws JSONException {
    if (action.equals("openSessionWithConfigurationId")) {
      openSessionWithConfigurationId(args.getString(0), args.getString(1), args.getString(2), args.getString(3), callbackContext);
      return true;
    }
    return false;
  }

  TVSession currentSession = null;

  private synchronized void openSessionWithConfigurationId(final String tvToken,
                                                           final String configurationId,
                                                           final String name,
                                                           final String description,
                                                           final CallbackContext callbackContext)
  {
    final TVSessionConfiguration config =
            new TVSessionConfiguration.Builder(
                    new TVConfigurationID(configurationId))
                    .setServiceCaseName(name)
                    .setServiceCaseDescription(description)
                    .build();

    TVSessionFactory.createTVSession(this, tvToken, new TVSessionCreationCallback() {
      @Override
      public void onTVSessionCreationSuccess(TVSession session) {
        currentSession = session;
        currentSession.start(config);
        callbackContext.sendPluginResult(new PluginResult(PluginResult.Status.OK, 0));
      }

      @Override
      public void onTVSessionCreationFailed(TVCreationError error) {
        callbackContext.sendPluginResult(new PluginResult(PluginResult.Status.ERROR, error.toString()));
      }

    });
  }
}

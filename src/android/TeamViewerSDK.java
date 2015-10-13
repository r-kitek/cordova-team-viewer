package com.cordova.teamViewerSDK;

import org.apache.cordova.CordovaPlugin;

import android.app.Activity;
import android.os.Handler;
import android.os.Looper;

import com.teamviewer.sdk.screensharing.api.TVConfigurationID;
import com.teamviewer.sdk.screensharing.api.TVCreationError;
import com.teamviewer.sdk.screensharing.api.TVSession;
import com.teamviewer.sdk.screensharing.api.TVSessionCode;
import com.teamviewer.sdk.screensharing.api.TVSessionConfiguration;
import com.teamviewer.sdk.screensharing.api.TVSessionCreationCallback;
import com.teamviewer.sdk.screensharing.api.TVSessionFactory;

import org.apache.cordova.CallbackContext;
import org.apache.cordova.PluginResult;
import org.json.JSONArray;
import org.json.JSONException;

public class TeamViewerSDK extends CordovaPlugin {

    public boolean execute(String action, JSONArray args, CallbackContext callbackContext)
            throws JSONException {
        if (action.equals("openSessionWithConfigurationId")) {
            openSessionWithConfigurationId(args.getString(0), args.getString(1), args.getString(2), args.getString(3), callbackContext);
            return true;
        } else if (action.equals("openSessionWithSessionCode")) {
            openSessionWithSessionCode(args.getString(0), args.getString(1), callbackContext);
            return true;
        } else if (action.equals("closeCurrentSession")) {
            closeCurrentSession();
            return true;
        }

        return false;
    }

    TVSession currentSession = null;

    private synchronized void openSessionWithConfigurationId(final String token,
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

        final Activity activity = this.cordova.getActivity();

        startSession(config, token, activity, callbackContext);
    }

    private synchronized void openSessionWithSessionCode(final String token,
                                                       final String sessionCode,
                                                       final CallbackContext callbackContext)
    {
        final TVSessionConfiguration config =
                new TVSessionConfiguration.Builder(new TVSessionCode(sessionCode))
                        .build();

        final Activity activity = this.cordova.getActivity();

        startSession(config, token, activity, callbackContext);
    }

    private synchronized void closeCurrentSession()
    {
        if (currentSession != null) {
            currentSession.stop();
        }
    }

    private void startSession(final TVSessionConfiguration configuration, final String token, final Activity activity, final CallbackContext callbackContext)
    {
        Handler mainHandler = new Handler(Looper.getMainLooper());
        Runnable runnable = new Runnable() {
            @Override
            public void run() {
                TVSessionFactory.createTVSession(activity, token, new TVSessionCreationCallback() {
                    @Override
                    public void onTVSessionCreationSuccess(TVSession session) {
                        currentSession = session;
                        currentSession.start(configuration);
                        callbackContext.sendPluginResult(new PluginResult(PluginResult.Status.OK, 0));
                    }

                    @Override
                    public void onTVSessionCreationFailed(TVCreationError error) {
                        callbackContext.sendPluginResult(new PluginResult(PluginResult.Status.ERROR, error.toString()));
                    }

                });
            }
        };

        mainHandler.post(runnable);
    }
}

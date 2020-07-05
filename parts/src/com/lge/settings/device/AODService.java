package com.lge.settings.device;

import android.app.Service;
import android.hardware.display.AmbientDisplayConfiguration;
import android.os.UserHandle;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.IBinder;
import android.util.Log;

import com.lge.settings.device.utils.Constants;
import com.lge.settings.device.utils.PreferenceHelper;


public class AODService extends Service {
    private static final String TAG = "AODService";
    private static final boolean DEBUG = false;

    @Override
    public void onCreate() {
        if (DEBUG) Log.d(TAG, "Creating service");

        IntentFilter screenStateFilter = new IntentFilter();
        screenStateFilter.addAction(Intent.ACTION_SCREEN_ON);
        screenStateFilter.addAction(Intent.ACTION_SCREEN_OFF);
        screenStateFilter.setPriority(1000);
        registerReceiver(mScreenStateReceiver, screenStateFilter);
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        if (DEBUG) Log.d(TAG, "Starting service");
        return START_STICKY;
    }

    @Override
    public void onDestroy() {
        if (DEBUG) Log.d(TAG, "Destroying service");
        super.onDestroy();
        this.unregisterReceiver(mScreenStateReceiver);
    }

    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    private void onDisplayOn() {
        if (DEBUG) Log.d(TAG, "Display on");

        Utils.writeValue(Constants.AOD_ENABLE_NODE, "0");
        Utils.writeValue(Constants.AOD_BLANK_NODE, "0");
    }

    private void onDisplayOff(Context context) {
        if (DEBUG) Log.d(TAG, "Display off");
        
        AmbientDisplayConfiguration mConfig = new AmbientDisplayConfiguration(context);


        if(PreferenceHelper.getAodBacklightType(context) == 0){
            Utils.writeValue(Constants.AOD_ENABLE_NODE, "2");

            if (mConfig.alwaysOnEnabled(UserHandle.myUserId())) {
                if (DEBUG) Log.d(TAG, "AOD Enabled");
                Utils.writeValue(Constants.AOD_BLANK_NODE, "0");
            }
        }
    }

    private BroadcastReceiver mScreenStateReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            if (intent.getAction().equals(Intent.ACTION_SCREEN_ON)) {
                onDisplayOn();
            } else if (intent.getAction().equals(Intent.ACTION_SCREEN_OFF)) {
                onDisplayOff(context);
            }
        }
    };
}

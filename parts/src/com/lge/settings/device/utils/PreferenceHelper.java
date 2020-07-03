package com.lge.settings.device.utils;

import android.content.Context;
import android.content.SharedPreferences;
import android.support.v7.preference.PreferenceManager;

public class PreferenceHelper {

    /**
     * Get AOD backlight type
     * @param context - ¯\_(ツ)_/¯
     * @return - AOD backlight type
     */
    public static int getAodBacklightType(Context context) {
        SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(context);
        return sharedPreferences.getInt(Constants.PREF_AOD_BACKLIGHT, 0);
    }

    /**
     * Set AOD backlight type
     * @param context - ¯\_(ツ)_/¯
     * @param value - backlight type
     */
    public static void setAodBacklightType(Context context, int value){
        SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(context);
        sharedPreferences.edit().putInt(Constants.PREF_AOD_BACKLIGHT, value).apply();
    }
}
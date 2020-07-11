/*
 * Copyright (C) 2015 The CyanogenMod Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.lge.settings.device;

import android.content.ComponentName;
import android.graphics.Color;
import android.graphics.drawable.ColorDrawable;
import android.os.Bundle;
import android.os.SystemProperties;
import android.provider.Settings;
import android.preference.ListPreference;
import android.preference.Preference;
import android.preference.PreferenceCategory;
import android.preference.EditTextPreference;
import android.preference.SwitchPreference;
import android.preference.TwoStatePreference;
import android.widget.ListView;
import android.widget.Toast;

import com.lge.settings.device.Battery;
import com.lge.settings.device.utils.Constants;
import com.lge.settings.device.utils.NodePreferenceActivity;

public class DeviceSettings extends NodePreferenceActivity {

    private SwitchPreference mFCSwitch;
	private EditTextPreference cyclePreference;
    private EditTextPreference tempPreference;
    private EditTextPreference healthPreference;
    private SwitchPreference mDaylightModeSwitch;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        addPreferencesFromResource(R.xml.device_settings);

        ListView lv = getListView();
        lv.setDivider(new ColorDrawable(Color.TRANSPARENT));
        lv.setDividerHeight(0);

        mFCSwitch = (SwitchPreference) findPreference(Constants.KEY_FAST_CHARGE);
        mFCSwitch.setEnabled(FastChargeSwitch.isSupported());
        mFCSwitch.setChecked(FastChargeSwitch.isCurrentlyEnabled(this));
        mFCSwitch.setOnPreferenceChangeListener(new FastChargeSwitch());

        cyclePreference = (EditTextPreference) findPreference(Constants.KEY_BATTERY_CYCLE);
        tempPreference = (EditTextPreference) findPreference(Constants.KEY_BATTERY_TEMP);
        healthPreference = (EditTextPreference) findPreference(Constants.KEY_BATTERY_HEALTH);

        cyclePreference.setSummary(Battery.getBatteryCycle());
        tempPreference.setSummary(Battery.getBatteryTemp()+"°C");
        healthPreference.setSummary(Battery.getBatteryHealth());

        mDaylightModeSwitch = (SwitchPreference) findPreference(Constants.KEY_DLM_SWITCH);
        mDaylightModeSwitch.setEnabled(DaylightModeSwitch.isSupported());
        mDaylightModeSwitch.setChecked(DaylightModeSwitch.isCurrentlyEnabled(this));
        mDaylightModeSwitch.setOnPreferenceChangeListener(new DaylightModeSwitch());
    }

    @Override
    protected void onResume() {
        super.onResume();

        // If running on a phone, remove padding around the listview
        getListView().setPadding(0, 0, 0, 0);

        // mHapticFeedback.setChecked(
        //         Settings.System.getInt(getContentResolver(), KEY_HAPTIC_FEEDBACK, 1) != 0);
    }
}

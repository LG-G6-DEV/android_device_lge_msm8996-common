/*
* Copyright (C) 2018 The OmniROM Project
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
*/
package com.lge.settings.device;

import android.content.Intent;
import android.content.SharedPreferences;
import android.preference.PreferenceManager;
import android.service.quicksettings.Tile;
import android.service.quicksettings.TileService;
import android.os.SystemProperties;
import android.provider.Settings;
import android.util.Log;

import com.lge.settings.device.utils.Constants;
import com.lge.settings.device.utils.PreferenceHelper;

public class DSTileService extends TileService {

    private String spectrumProfile[];
    private int spectrumProfileID = 0;

    @Override
    public void onDestroy() {
        super.onDestroy();
    }

    @Override
    public void onTileAdded() {
        super.onTileAdded();

        spectrumProfile = getResources().getStringArray(R.array.spectrum_qs_profiles);

        Tile tile = getQsTile();
        tile.setLabel(spectrumProfile[0]);

        if(PreferenceHelper.isSpectrumEnabled(getApplicationContext())) {
            spectrumProfileID = Integer.parseInt(SystemProperties.get(Constants.SPECTRUM_SYSTEM_PROPERTY, "0"));

            tile.setLabel(spectrumProfile[spectrumProfileID]);
            tile.setState(Tile.STATE_ACTIVE);
        } else { tile.setState(Tile.STATE_UNAVAILABLE); }
        tile.updateTile();
    }

    @Override
    public void onTileRemoved() {
        super.onTileRemoved();
    }

    @Override
    public void onStartListening() {
        super.onStartListening();

        SharedPreferences preferences = PreferenceManager.getDefaultSharedPreferences(getApplicationContext());
        preferences.registerOnSharedPreferenceChangeListener(new SharedPreferences.OnSharedPreferenceChangeListener() {
            @Override
            public void onSharedPreferenceChanged(SharedPreferences sharedPreferences, String s) {
                if (s.equals(Constants.PREF_SPECTRUM_ENABLED)){
                    Tile tile = getQsTile();

                    if(PreferenceHelper.isSpectrumEnabled(getApplicationContext())) {
                        spectrumProfile = getResources().getStringArray(R.array.spectrum_qs_profiles);
                        spectrumProfileID = Integer.parseInt(SystemProperties.get(Constants.SPECTRUM_SYSTEM_PROPERTY, "0"));

                        tile.setLabel(spectrumProfile[spectrumProfileID]);
                        tile.setState(Tile.STATE_ACTIVE);
                    } else { tile.setState(Tile.STATE_UNAVAILABLE); }

                    tile.updateTile();
                }
            }
        });
    }

    @Override
    public void onStopListening() {
        super.onStopListening();
    }

    @Override
    public void onClick() {
        super.onClick();

        Tile tile = getQsTile();

        if(PreferenceHelper.isSpectrumEnabled(getApplicationContext())) {
            spectrumProfileID = Integer.parseInt(SystemProperties.get(Constants.SPECTRUM_SYSTEM_PROPERTY, "0"));

            if (spectrumProfileID == (spectrumProfile.length - 1)) { spectrumProfileID = 0; }
            else { spectrumProfileID++; }

            SystemProperties.set(Constants.SPECTRUM_SYSTEM_PROPERTY, Integer.toString(spectrumProfileID));

            tile.setLabel(spectrumProfile[spectrumProfileID]);
            tile.setState(Tile.STATE_ACTIVE);
        } else { tile.setState(Tile.STATE_UNAVAILABLE); }
        tile.updateTile();
    }
}

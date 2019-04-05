const DDCut = require('../../../Backend/ddcut.node');
import { ipcMain, Event } from 'electron';
import Settings from '../../Common/Models/Settings';

class SettingsAPI {
    static Initialize() {

        /*
         *
         * DECLARE_NAPI_METHOD("GetEnableSlider", GetEnableSlider),
         * DECLARE_NAPI_METHOD("GetPauseAfterGCode", GetPauseAfterGCode),
         * DECLARE_NAPI_METHOD("GetMinFeedRate", GetMinFeedRate),
         * DECLARE_NAPI_METHOD("GetMaxFeedRate", GetMaxFeedRate),
         * DECLARE_NAPI_METHOD("GetTimeout", GetTimeout),
         * DECLARE_NAPI_METHOD("GetSettings", GetSettings),
         * DECLARE_NAPI_METHOD("UpdateSettings", UpdateSettings),
         * 
         */
        ipcMain.on("Settings::GetSettings", function (event: Event) {
            let settings = DDCut.GetSettings();
            let pauseAfterGCode = settings["pauseAfterGCode"];
            let timeout = settings["timeout"];
            let enableSlider = settings["enable_slider"];
            let maxFeedRate = settings["maxFeedRate"];
            
            event.returnValue = new Settings(pauseAfterGCode, timeout, enableSlider, maxFeedRate);
        });

        ipcMain.on("Settings::UpdateSettings", function (event: Event, pauseAfterGCode: boolean, timeout: number, enableSlider: boolean, maxFeedRate: number) {
            let settings = new Settings(pauseAfterGCode, timeout, enableSlider, maxFeedRate);            
            DDCut.UpdateSettings(settings);
        });
    };
}

export default SettingsAPI;
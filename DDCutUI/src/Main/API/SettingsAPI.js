"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var DDCut = require('../../../Backend/ddcut.node');
var electron_1 = require("electron");
var Settings_1 = require("../../Common/Models/Settings");
var SettingsAPI = /** @class */ (function () {
    function SettingsAPI() {
    }
    SettingsAPI.Initialize = function () {
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
        electron_1.ipcMain.on("Settings::GetSettings", function (event) {
            var settings = DDCut.GetSettings();
            var pauseAfterGCode = settings["pauseAfterGCode"];
            var timeout = settings["timeout"];
            var enableSlider = settings["enable_slider"];
            var maxFeedRate = settings["maxFeedRate"];
            event.returnValue = new Settings_1.default(pauseAfterGCode, timeout, enableSlider, maxFeedRate);
        });
        electron_1.ipcMain.on("Settings::UpdateSettings", function (event, pauseAfterGCode, timeout, enableSlider, maxFeedRate) {
            var settings = new Settings_1.default(pauseAfterGCode, timeout, enableSlider, maxFeedRate);
            DDCut.UpdateSettings(settings);
        });
    };
    ;
    return SettingsAPI;
}());
exports.default = SettingsAPI;
//# sourceMappingURL=SettingsAPI.js.map
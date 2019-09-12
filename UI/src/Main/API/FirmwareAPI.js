"use strict";
exports.__esModule = true;
var DDCut = require("ddcut");
var electron_1 = require("electron");
var FirmwareUpdate_1 = require("../../Common/Models/FirmwareUpdate");
var FirmwareVersion_1 = require("../../Common/Models/FirmwareVersion");
var FirmwareAPI = /** @class */ (function () {
    function FirmwareAPI() {
    }
    FirmwareAPI.Initialize = function () {
        /*
         *
         * napi_get_named_property(env, args[0], "Version", &versionProperty);
         * napi_get_named_property(env, args[0], "Description", &descriptionProperty);
         * napi_get_named_property(env, args[0], "Files", &filesArray);
         *
         * DECLARE_NAPI_METHOD("UploadFirmware", UploadFirmware),
         * DECLARE_NAPI_METHOD("GetFirmwareUploadStatus", GetFirmwareUploadStatus),
         * DECLARE_NAPI_METHOD("GetFirmwareVersion", GetFirmwareVersion),
         * DECLARE_NAPI_METHOD("GetAvailableFirmwareUpdates", GetAvailableFirmwareUpdates)
         *
         */
        electron_1.ipcMain.on("Firmware::GetAvailableFirmwareUpdates", function (event) {
            DDCut.GetAvailableFirmwareUpdates(function (availableFirmware) {
                var availableUpdates = [];
                console.log(availableFirmware);
                for (var i = 0; i < availableFirmware.length; i++) {
                    var version = availableFirmware[i].version;
                    var description = availableFirmware[i].description;
                    var files = availableFirmware[i].files;
                    var update = new FirmwareUpdate_1["default"](version, description, files);
                    availableUpdates.push(update);
                }
                event.sender.send("Firmware::UpdatesAvailable", availableUpdates);
            });
        });
        electron_1.ipcMain.on("Firmware::GetFirmwareUploadStatus", function (event) {
            event.returnValue = DDCut.GetFirmwareUploadStatus();
        });
        electron_1.ipcMain.on("Firmware::GetFirmwareVersion", function (event) {
            var firmwareVersion = DDCut.GetFirmwareVersion();
            var grblVersion = firmwareVersion["grblVersion"];
            var ddVersion = firmwareVersion["ddVersion"];
            event.returnValue = new FirmwareVersion_1["default"](grblVersion, ddVersion);
        });
        electron_1.ipcMain.on("Firmware::UploadFirmware", function (event, version, description, files) {
            var firmwareUpdate = new FirmwareUpdate_1["default"](version, description, files);
            event.returnValue = DDCut.UploadFirmware(firmwareUpdate);
        });
    };
    ;
    return FirmwareAPI;
}());
exports["default"] = FirmwareAPI;

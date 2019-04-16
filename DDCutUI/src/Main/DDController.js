"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var DDCut = require('../../Backend/ddcut.node');
var SettingsAPI_1 = require("./API/SettingsAPI");
var FirmwareAPI_1 = require("./API/FirmwareAPI");
var FileAPI_1 = require("./API/FileAPI");
var JobsAPI_1 = require("./API/JobsAPI");
var SupportAPI_1 = require("./API/SupportAPI");
var globalAny = global;
var mainWindow = null;
var ggStatus = 0;
function InitializeAPIs() {
    SettingsAPI_1.default.Initialize();
    FirmwareAPI_1.default.Initialize();
    FileAPI_1.default.Initialize();
    JobsAPI_1.default.Initialize();
    SupportAPI_1.default.Initialize();
}
;
function CheckConnectionStatus() {
    if (mainWindow != null) {
        var newStatus = DDCut.GetGhostGunnerStatus();
        if (newStatus != ggStatus) {
            ggStatus = newStatus;
            mainWindow.webContents.send("DD_UpdateGGStatus", newStatus);
        }
    }
}
var connectionStatusIntervalId = null;
var DDController = /** @class */ (function () {
    function DDController() {
    }
    DDController.Initialize = function () {
        DDCut.Initialize(function () {
            InitializeAPIs();
            connectionStatusIntervalId = setInterval(CheckConnectionStatus, 50);
            globalAny.initialized = true;
        });
    };
    ;
    DDController.SetWindow = function (window) {
        mainWindow = window;
    };
    DDController.Shutdown = function () {
        clearInterval(connectionStatusIntervalId);
        DDCut.Shutdown();
    };
    ;
    return DDController;
}());
exports.default = DDController;
//# sourceMappingURL=DDController.js.map
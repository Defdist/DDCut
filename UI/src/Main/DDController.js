"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const ddcut_1 = require("ddcut");
const electron_1 = require("electron");
const SettingsAPI_1 = require("./API/SettingsAPI");
const FirmwareAPI_1 = require("./API/FirmwareAPI");
const FileAPI_1 = require("./API/FileAPI");
const GhostGunnerAPI_1 = require("./API/GhostGunnerAPI");
const JobsAPI_1 = require("./API/JobsAPI");
const LogsAPI_1 = require("./API/LogsAPI");
const SupportAPI_1 = require("./API/SupportAPI");
const WalkthroughAPI_1 = require("./API/WalkthroughAPI");
const globalAny = global;
var mainWindow = null;
var ggStatus = 0;
var currentContainer = "Dashboard";
function InitializeAPIs() {
    SettingsAPI_1.default.Initialize();
    FirmwareAPI_1.default.Initialize();
    FileAPI_1.default.Initialize();
    GhostGunnerAPI_1.default.Initialize();
    JobsAPI_1.default.Initialize();
    LogsAPI_1.default.Initialize();
    SupportAPI_1.default.Initialize();
    WalkthroughAPI_1.default.Initialize();
    electron_1.ipcMain.on("DD_SetCurrentPage", function (event, container) {
        currentContainer = container;
    });
    electron_1.ipcMain.on("DD_GetCurrentPage", function (event) {
        event.returnValue = currentContainer;
    });
}
;
function CheckConnectionStatus() {
    if (mainWindow != null) {
        let newStatus = ddcut_1.GetGhostGunnerStatus();
        if (newStatus != ggStatus) {
            ggStatus = newStatus;
            mainWindow.webContents.send("DD_UpdateGGStatus", newStatus);
        }
    }
}
var connectionStatusIntervalId = null;
class DDController {
    static Initialize() {
        ddcut_1.Initialize(function () {
            InitializeAPIs();
            connectionStatusIntervalId = setInterval(CheckConnectionStatus, 50);
            globalAny.initialized = true;
        });
    }
    ;
    static SetWindow(window) {
        mainWindow = window;
    }
    static Shutdown() {
        clearInterval(connectionStatusIntervalId);
        ddcut_1.Shutdown();
    }
    ;
    static SetMillingStatus(milling) {
        if (mainWindow != null) {
            mainWindow.webContents.send("Milling::Status", milling);
        }
    }
}
exports.default = DDController;
//# sourceMappingURL=DDController.js.map

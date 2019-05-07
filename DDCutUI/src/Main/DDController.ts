const DDCut = require('../../Backend/ddcut.node');
import { ipcMain, BrowserWindow } from 'electron';
import SettingsAPI from './API/SettingsAPI';
import FirmwareAPI from './API/FirmwareAPI';
import FileAPI from './API/FileAPI';
import GhostGunnerAPI from './API/GhostGunnerAPI';
import JobsAPI from './API/JobsAPI';
import LogsAPI from './API/LogsAPI';
import SupportAPI from './API/SupportAPI';

const globalAny: any = global;
var mainWindow = null;

var ggStatus = 0;

function InitializeAPIs() {
    SettingsAPI.Initialize();
    FirmwareAPI.Initialize();
    FileAPI.Initialize();
    GhostGunnerAPI.Initialize();
    JobsAPI.Initialize();
    LogsAPI.Initialize();
    SupportAPI.Initialize();
};


function CheckConnectionStatus() {
    if (mainWindow != null) {
        let newStatus : number = DDCut.GetGhostGunnerStatus();
        if (newStatus != ggStatus) {
            ggStatus = newStatus;
            mainWindow.webContents.send("DD_UpdateGGStatus", newStatus);
        }
    }
}

var connectionStatusIntervalId = null;

class DDController {
    static Initialize() {
        DDCut.Initialize(function () {
            InitializeAPIs();
            connectionStatusIntervalId = setInterval(CheckConnectionStatus, 50);
            globalAny.initialized = true;
        });
    };

    static SetWindow(window: BrowserWindow) {
        mainWindow = window;
    }

    static Shutdown() {
        clearInterval(connectionStatusIntervalId);
        DDCut.Shutdown();
    };

	static SetMillingStatus(milling: boolean) {
		if (mainWindow != null) {
            mainWindow.webContents.send("Milling::Status", milling);
		}
	}
}

export default DDController;
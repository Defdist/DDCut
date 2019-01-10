const ddcut = require('../../node/ddcut.node');
const electron = require('electron');
const ipc = electron.ipcRenderer;
const BrowserWindow = electron.remote.BrowserWindow;
const path = require('path');
const url = require('url');

var settingsWindow = null;

//////////////////////////////////////////////////////
// FIRMWARE
//////////////////////////////////////////////////////
var firmwareVersionIntervalId = 0;

function SendFirmwareVersion() {
    console.log("SendFirmwareVersion");
    if (settingsWindow == null) {
        clearInterval(firmwareVersionIntervalId);
    }
    else if (connected == 2) {
        const firmwareVersion = ddcut.GetFirmwareVersion();
        settingsWindow.webContents.send("FIRMWARE_VERSION", firmwareVersion["ddVersion"], firmwareVersion["grblVersion"]);
        clearInterval(firmwareVersionIntervalId);
    }
}

function CheckForFirmwareUpdates(event, callback) {
    if (settingsWindow != null && connected == 2) {
        console.log("CheckForFirmwareUpdates");
        ddcut.GetAvailableFirmwareUpdates(function (availableFirmware) {
            console.log("ShowFirmwareSelectionWindow");
            let firmwareWindow = new BrowserWindow({
                width: 400, height: 250, frame: false, resizable: false,
                parent: settingsWindow, modal: false, icon: path.join(__dirname, '../img/logo-white.png')
            });
            firmwareWindow.setMenu(null);
            firmwareWindow.on('closed', () => {
                $("#Modal").addClass('hidden');
            });

            firmwareWindow.loadURL(
                url.format({
                        pathname: path.join(__dirname, '../firmware_selection.html'),
                        protocol: 'file:',
                        slashes: true
                })
            );

            $("#Modal").removeClass('hidden');

            firmwareWindow.webContents.on('did-finish-load', () => {
                firmwareWindow.webContents.send("FIRMWARE", availableFirmware, "FIRMWARE_SELECTED");
            });
        });
    }
}

//////////////////////////////////////////////////////
// FIRMWARE UPLOAD
//////////////////////////////////////////////////////
var uploadFirmwareStatusIntervalId = 0;
var uploadFirmwareWindow = null;

function UpdateFirmwareUploadStatus() {
    if (uploadFirmwareWindow == null) {
        clearInterval(uploadFirmwareStatusIntervalId);
    } else {
        const status = ddcut.GetFirmwareUploadStatus();
        if (status < 0) {
            // TODO:
        } else if (status == 100) {
            clearInterval(uploadFirmwareStatusIntervalId);
        }

        uploadFirmwareWindow.webContents.send("FIRMWARE_UPLOAD_STATUS", status);
    }
}

function UploadFirmware(event, firmware) {
    if (ddcut.UploadFirmware(firmware)) {
        console.log("Uploading Firmware");
        uploadFirmwareWindow = new BrowserWindow({
            width: 682, height: 496, frame: false, resizable: false,
            parent: settingsWindow, modal: false, icon: path.join(__dirname, '../img/logo-white.png')
        });
        uploadFirmwareWindow.setMenu(null);
        uploadFirmwareWindow.on('closed', () => {
            uploadFirmwareWindow = null;
            $("#Modal").addClass('hidden');
        });

        uploadFirmwareWindow.loadURL(
            url.format({
                pathname: path.join(__dirname, '../firmware_uploader.html'),
                protocol: 'file:',
                slashes: true
            })
        );

        $("#Modal").removeClass('hidden');

        uploadFirmwareWindow.webContents.on('did-finish-load', () => {
            uploadFirmwareStatusIntervalId = setInterval(UpdateFirmwareUploadStatus, 50);
        });
    } else {
        // TODO: Alert the user of a failure
    }
}

//////////////////////////////////////////////////////
// SETTINGS
//////////////////////////////////////////////////////
function SaveSettings(event, settings) {
    console.log("Saving Settings:");
    console.log(settings);
    ddcut.UpdateSettings(settings);
}

function ShowSettingsWindow(event) {
    settingsWindow = new BrowserWindow({
        width: 523, height: 518, frame: false, resizable: false,
        parent: electron.remote.getCurrentWindow(), modal: false, icon: path.join(__dirname, '../img/logo-white.png')
    });
    settingsWindow.setMenu(null);
    settingsWindow.on('closed', () => {
        settingsWindow = null;
        $("#Modal").addClass('hidden');
    });

    settingsWindow.loadURL(
        url.format({
                pathname: path.join(__dirname, '../settings.html'),
                protocol: 'file:',
                slashes: true
        })
    );

    $("#Modal").removeClass('hidden');

    const settings = ddcut.GetSettings();
    settingsWindow.webContents.on('did-finish-load', () => {
        settingsWindow.webContents.send("CURRENT_SETTINGS", settings);
        firmwareVersionIntervalId = setInterval(SendFirmwareVersion, 200);
    });
}

//////////////////////////////////////////////////////
// EVENT LISTENERS
//////////////////////////////////////////////////////
function AddEventListeners() {
    ipc.removeAllListeners("SAVE_SETTINGS");
    ipc.on("SAVE_SETTINGS", SaveSettings);

    ipc.removeAllListeners("CHECK_FIRMWARE_UPDATES");
    ipc.on("CHECK_FIRMWARE_UPDATES", CheckForFirmwareUpdates);

    ipc.removeAllListeners('FIRMWARE_SELECTED');
    ipc.on('FIRMWARE_SELECTED', UploadFirmware);

    const settingsButton = document.getElementById('settings');

    settingsButton.addEventListener('click', ShowSettingsWindow);
}

//////////////////////////////////////////////////////
// EXPORTS
//////////////////////////////////////////////////////
module.exports = {
    AddEventListeners
};
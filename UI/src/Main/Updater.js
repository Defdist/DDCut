const { dialog } = require('electron');
const { autoUpdater } = require('electron-updater');
const logger = require("electron-log");

autoUpdater.on('error', (error) => {
    //dialog.showErrorBox('Error: ', error == null ? "unknown" : (error.stack || error).toString())
})

autoUpdater.on('update-available', (updateInfo) => {
    let message = "Version: " + updateInfo.releaseName;

    dialog.showMessageBox({
        type: 'info',
        title: 'Update Available',
        message: 'A new version of DDCut is available. Would you like to update now?\n\n' + message,
        buttons: ['Yes', 'No']
    }, (buttonIndex) => {
        if (buttonIndex === 0) {
            autoUpdater.downloadUpdate();
        }
    });
})

autoUpdater.on('update-not-available', () => {

})

autoUpdater.on('update-downloaded', () => {
    autoUpdater.quitAndInstall();
});

function checkForUpdates () {
    logger.transports.file.level = "debug";
    autoUpdater.logger = logger;
    autoUpdater.autoDownload = false;
    autoUpdater.checkForUpdates();
}

export default {checkForUpdates};
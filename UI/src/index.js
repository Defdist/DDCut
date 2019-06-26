import {app, BrowserWindow} from 'electron';
import DDController from './Main/DDController';
import Updater from './Main/Updater.js';
import env from 'env';
const unhandled = require('electron-unhandled');

// Keep a global reference of the window object, if you don't, the window will
// be closed automatically when the JavaScript object is garbage collected.
let mainWindow;

unhandled({
    logger: console.log,
    showDialog: false
});

const createWindow = async () => {
    // Create the browser window.
    mainWindow = new BrowserWindow({
        width: 1205,
        height: 705,
        frame: false,
        webPreferences: {
            nodeIntegration: true
        }
    });

    DDController.Initialize();

    mainWindow.webContents.once('dom-ready', () => {
        console.log("Finished loading");
        DDController.SetWindow(mainWindow);
        
        Updater.checkForUpdates();
    });

    // and load the index.html of the app.
    mainWindow.loadURL(`file://${__dirname}/index.html`);

    // Open the DevTools.
    if (env.name == 'development') {
        mainWindow.webContents.openDevTools({mode:'undocked'});
    }

    // Emitted when the window is closed.
    mainWindow.on('closed', () => {
        console.log("closed");

        // Dereference the window object, usually you would store windows
        // in an array if your app supports multi windows, this is the time
        // when you should delete the corresponding element.
        mainWindow = null;
    });
};


const gotTheLock = app.requestSingleInstanceLock();
if (!gotTheLock) {
    app.quit();
} else {
    app.on('second-instance', (event, commandLine, workingDirectory) => {
        // Someone tried to run a second instance, we should focus our window.
        if (mainWindow) {
            if (mainWindow.isMinimized()) {
                mainWindow.restore();
                mainWindow.focus();
            }
        }
    });
    
    // This method will be called when Electron has finished
    // initialization and is ready to create browser windows.
    // Some APIs can only be used after this event occurs.
    app.on('ready', createWindow);
}

// Quit when all windows are closed.
app.on('window-all-closed', () => {
    console.log("window-all-closed");
    // On OS X it is common for applications and their menu bar
    // to stay active until the user quits explicitly with Cmd + Q
    if (process.platform !== 'darwin') {
        setTimeout(() => {
            DDController.SetWindow(null);
            DDController.Shutdown();

            console.log("app.quit");
            app.quit();
        }, 0);
    }
});

app.on('before-quit', (e) => {
    console.log("before-quit");
});

app.on('will-quit', (e) => {
    console.log("will-quit");
});

app.on('quit', (e) => {
    console.log("quit");
    app.removeAllListeners();
});

app.on('activate', () => {
    // On OS X it's common to re-create a window in the app when the
    // dock icon is clicked and there are no other windows open.
    if (mainWindow === null) {
        createWindow();
    }
});

// In this file you can include the rest of your app's specific main process
// code. You can also put them in separate files and import them here.

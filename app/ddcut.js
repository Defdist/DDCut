const { app, BrowserWindow, Menu } = require('electron')
const electron = require('electron');

const path = require('path')
const url = require('url')

global.DEBUG = false;

// Keep a global reference of the window object, if you don't, the window will
// be closed automatically when the JavaScript object is garbage collected.
let win

function createWindow () {
	// Create the browser window.
	win = new BrowserWindow(
		{
			width: 1205, 
			height: 705, 
			frame: false, 
			resizable: false,
			icon: path.join(__dirname, 'ui/img/logo-white.png')
		}
	);
	
	global.window_id = win.id;
	
	//win.setMenu(null);
	//ddMenu();

	// and load the dashboard.html of the app.
	win.loadURL(
		url.format
		(
			{
				pathname: path.join(__dirname, 'ui/index.html'),
				protocol: 'file:',
				slashes: true
			}
		)
	)

	// Open the DevTools.
    if (global.DEBUG) {
        win.webContents.openDevTools();
    }

	// Emitted when the window is closed.
	win.on(
		'closed', 
		() => 
		{
			//require('./node/ddcut.node').EmergencyStop();
		  // Dereference the window object, usually you would store windows
		  // in an array if your app supports multi windows, this is the time
		  // when you should delete the corresponding element.
		  win = null
		}
	)
}

// This method will be called when Electron has finished
// initialization and is ready to create browser windows.
// Some APIs can only be used after this event occurs.
app.on('ready', createWindow)

// Quit when all windows are closed.
app.on(
	'window-all-closed', 
	() => 
	{
		// On macOS it is common for applications and their menu bar
		// to stay active until the user quits explicitly with Cmd + Q
		//if (process.platform !== 'darwin') {
			app.quit()
		//}
	}
)

app.on(
	'activate', 
	() => 
	{
		// On macOS it's common to re-create a window in the app when the
		// dock icon is clicked and there are no other windows open.
		if (win === null) {
		  createWindow()
		}
	}
)

process.on('uncaughtException', function (err) {
  console.log(err);
})

// In this file you can include the rest of your app's specific main process
// code. You can also put them in separate files and require them here.
let execPath = path.dirname(process.execPath);

// listen to an open-file-dialog command and sending back selected information
const ipc = require('electron').ipcMain
const dialog = require('electron').dialog
ipc.on('open-file-dialog', 
	function (event, returnEventName)
	{
  		dialog.showOpenDialog(
		{
            defaultPath: path.join(execPath, 'Cutting Code'),
            properties: ['openFile', 'treatPackageAsDirectory'],
			filters: [{name: "DD Files", extensions: ["dd"]}]
  		}, 
		function (files) 
		{
    		if (files)
            {
                ddcut.SetDDFile(files[0]);
                if (ddcut.GetJobs().length == 0) {
                    // TODO: Alert user that .dd file is invalid. Call Validate??
                    ddcut.SetDDFile("");
                }
				//event.returnValue = files;
				event.sender.send(returnEventName, files)
			}
  		})
	}
)

ipc.on("CUSTOMER_SUPPORT_REQUEST", (event, email, description, includeLogs) => {
    ipc.once("CUSTOMER_SUPPORT_RESULT", (event2, error) => {
        event.sender.send("CUSTOMER_SUPPORT_ERROR", error);
    });

    win.webContents.send("CUSTOMER_SUPPORT", email, description, includeLogs);
});
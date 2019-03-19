const electron = require('electron');

var updateVersion = null;
var returnEventName = null;

document.getElementById("CancelButton").addEventListener("click",
	function()
	{
		electron.remote.getCurrentWindow().close();
	}
);

document.getElementById("InstallButton").addEventListener("click",
	function()
	{
        electron.ipcRenderer.sendTo(electron.remote.getGlobal('window_id'), returnEventName, updateVersion);
		electron.remote.getCurrentWindow().close();
	}
);

electron.ipcRenderer.on('UPDATE', 
	function(event, availableUpdate, eventName)
	{
        updateVersion = availableUpdate.LATEST_VERSION;
        returnEventName = eventName;

        document.getElementById("VersionLabel").innerText += updateVersion;
        document.getElementById("ReleaseNotes").value = availableUpdate.RELEASE_NOTES;
	}
);
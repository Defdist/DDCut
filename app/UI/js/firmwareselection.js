const electron = require('electron');

var availableUpdates = null;
var returnEventName = null;

document.getElementById("CancelButton").addEventListener("click",
	function()
	{
		electron.remote.getCurrentWindow().close();
	}
);

document.getElementById("SelectButton").addEventListener("click",
	function()
	{
        var firmwareList = document.getElementById("FirmwareList");
        if (firmwareList.selectedIndex >= 0) 
		{
            electron.ipcRenderer.sendTo(electron.remote.getGlobal('window_id'), returnEventName, availableUpdates[firmwareList.selectedIndex]);
			electron.remote.getCurrentWindow().close();
		}
	}
);

electron.ipcRenderer.on('FIRMWARE', 
	function(event, availableFirmware, eventName)
	{
		returnEventName = eventName;
        availableUpdates = availableFirmware;
		
        var firmwareList = document.getElementById("FirmwareList");
        for (var i = 0; i < availableFirmware.length; i++)
		{
			var opt = document.createElement('option');
            opt.value = i;
            opt.text = availableFirmware[i].Description;
			firmwareList.add(opt);
		}
	}
);
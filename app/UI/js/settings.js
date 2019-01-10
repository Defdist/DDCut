const electron = require('electron');
const ipc = electron.ipcRenderer;

//////////////////////////////////////////////////////
// DISPLAY
//////////////////////////////////////////////////////
function DisplaySettings(settings)
{	
	$("#EnableFeedrate").prop("checked", settings.enable_slider);
	
	$("#Pause").prop("checked", settings.pauseAfterGCode);
	$("#Timeout").val(settings.timeout);

	if (settings.maxFeedRate == 300)
	{
		$("#feedrate30_300").prop("checked", true);
	}
	else
	{
		$("#feedrate30_100").prop("checked", true);
	}
}
	
function EnableDisableFeedRateRadioButtons()
{
	console.log("EnableDisableFeedRateRadioButtons");
	$("#feedrate30_100").attr('disabled', !$("#EnableFeedrate").prop("checked"));
	$("#feedrate30_300").attr('disabled', !$("#EnableFeedrate").prop("checked"));
}

document.getElementById("EnableFeedrate").addEventListener("click", EnableDisableFeedRateRadioButtons);

ipc.removeAllListeners("CURRENT_SETTINGS");
ipc.on('CURRENT_SETTINGS', 
	function(event, settings)
	{
		DisplaySettings(settings);
		
		EnableDisableFeedRateRadioButtons();
	}
);

//////////////////////////////////////////////////////
// CANCEL
//////////////////////////////////////////////////////
document.getElementById("CancelButton").addEventListener("click",
	function()
	{
		electron.remote.getCurrentWindow().close();
	}
);

//////////////////////////////////////////////////////
// SAVE
//////////////////////////////////////////////////////
document.getElementById("SaveButton").addEventListener("click",
	function()
	{
		var radios = document.getElementsByName('feedrate');
		var maxFeedRate = 100;
		
		for (var i = 0, length = radios.length; i < length; i++)
		{
			if (radios[i].checked)
			{
				maxFeedRate = parseInt(radios[i].getAttribute('maxFeedRate'));
				break;
			}
		}
		
		var settings = {};
		settings.enable_slider = document.getElementById('EnableFeedrate').checked;
		settings.pauseAfterGCode = document.getElementById('Pause').checked;
		settings.timeout = parseInt(document.getElementById('Timeout').value);
		settings.maxFeedRate = maxFeedRate;
		
		electron.ipcRenderer.sendTo(electron.remote.getGlobal('window_id'), "SAVE_SETTINGS", settings);
		electron.remote.getCurrentWindow().close();
	}
);

//////////////////////////////////////////////////////
// FIRMWARE
//////////////////////////////////////////////////////
document.getElementById("UpdateFirmware").addEventListener("click",
    function () {
        ipc.sendTo(electron.remote.getGlobal('window_id'), "CHECK_FIRMWARE_UPDATES");
    }
);

ipc.removeAllListeners("FIRMWARE_VERSION");
ipc.on('FIRMWARE_VERSION',
    function (event, ddVersion, grblVersion) {
        $("#FirmwareVersion").removeClass("RedText");
        $("#FirmwareVersion").addClass("WhiteText");
        $("#FirmwareVersion").html("DD: " + ddVersion + " -  GRBL: " + grblVersion);
        $("#UpdateFirmware").addClass("Clickable");
    }
);
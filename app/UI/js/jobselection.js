
const electron = require('electron');

var loadedJobs = null;
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
		var jobsList = document.getElementById("JobsList");
		if (jobsList.selectedIndex >= 0) 
		{
			electron.ipcRenderer.sendTo(electron.remote.getGlobal('window_id'), returnEventName, jobsList.selectedIndex);
			electron.remote.getCurrentWindow().close();
		}
	}
);
	
document.getElementById("JobsList").addEventListener("change", 
	function () 
	{
		var selectedIndex = document.getElementById("JobsList").selectedIndex;
		var jobTextElement = document.getElementById("JobText");
		jobTextElement.value = loadedJobs[selectedIndex].prompt;
		
		document.getElementById("SelectButton").className = "clickable"
	}
);

electron.ipcRenderer.on('JOBS', 
	function(event, jobs, eventName)
	{
		returnEventName = eventName;
		loadedJobs = jobs;
		
		var jobsList = document.getElementById("JobsList");
		for (var i = 0; i < jobs.length; i++)
		{
			var opt = document.createElement('option');
			opt.value = i;
			opt.text = jobs[i].title;
			jobsList.add(opt);
		}
	}
);
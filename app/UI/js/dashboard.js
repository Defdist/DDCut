// This file is required by the index.html file and will
// be executed in the renderer process for that window.
// All of the Node.js APIs are available in this process.

const dashboard_settings = require('./dashboard_settings.js');
const ddcut = require('../../node/ddcut.node');
const electron = require('electron');
const ipc = electron.ipcRenderer;
const BrowserWindow = electron.remote.BrowserWindow;
const path = require('path');
const url = require('url');

//////////////////////////////////////////////////////
// JOB SELECTION
//////////////////////////////////////////////////////
function ShowJobSelectionWindow()
{
	let jobWindow = new BrowserWindow({width: 600, height: 380, frame: false, resizable: false, 
			parent: electron.remote.getCurrentWindow(), modal: false, icon: path.join(__dirname, '../img/logo-white.png')});
	jobWindow.setMenu(null);
	jobWindow.on('closed', () => {
		$("#Modal").addClass('hidden');
	});

	jobWindow.loadURL(
		url.format
		(
			{
				pathname: path.join(__dirname, '../job_selection.html'),
				protocol: 'file:',
				slashes: true
			}
		)
	);
	
	$("#Modal").removeClass('hidden');
	
	const jobs = ddcut.GetJobs();
	jobWindow.webContents.on('did-finish-load', () => { 
		jobWindow.webContents.send("JOBS", jobs, "SELECTED_JOB_DASHBOARD");
	});
}

ipc.removeAllListeners('SELECTED_JOB_DASHBOARD');
ipc.on('SELECTED_JOB_DASHBOARD', 
	function (event, jobIndex)
	{
		ddcut.SetSelectedJob(jobIndex);
		ShowSection("Milling");
	}
);

//////////////////////////////////////////////////////
// RUN BUTTON
//////////////////////////////////////////////////////
function EnableDisableRunButton()
{
	if (currentSection == "Dashboard")
	{
		if (connected == 2 && ddcut.GetDDFile().length > 0)
		{
			$('#run').addClass("Clickable");
		}
		else
		{
			$('#run').removeClass("Clickable");
		}
	}
}

var enableDisableRunIntervalId = setInterval(EnableDisableRunButton, 100);

function AddRunEventListener()
{
	const runButton = document.getElementById('run');

	runButton.addEventListener('click', 
		function (event) 
		{
			if ($('#run').hasClass("Clickable"))
			{
				ShowJobSelectionWindow();
			}
		}
	);
}

//////////////////////////////////////////////////////
// DD FILE
//////////////////////////////////////////////////////
function AddDDFileEventListener()
{
	const openButton = document.getElementById('open');

	openButton.addEventListener('click', 
		function (event) 
		{
			ipc.send('open-file-dialog', 'SELECTED_FILE_DASHBOARD');
		}
    );
}

ipc.removeAllListeners('SELECTED_FILE_DASHBOARD');
ipc.on('SELECTED_FILE_DASHBOARD',
    function (event, path) {
        ddcut.SetDDFile(path[0]);
        if (ddcut.GetJobs().length == 0) {
            // TODO: Alert user that .dd file is invalid. Call Validate??
            ddcut.SetDDFile("");
        }
    }
);

//////////////////////////////////////////////////////
// STORE BUTTON
//////////////////////////////////////////////////////
function AddStoreEventListener()
{
	const storeButton = document.getElementById('store');

	storeButton.addEventListener('click', 
		function (event) 
		{
			electron.shell.openExternal("https://ghostgunner.net/collections/featured-products");
		}
	);
}

//////////////////////////////////////////////////////
// DASHBOARD
//////////////////////////////////////////////////////
function InitializeDashboard()
{
	if (ddcutInitialized && !sectionInitialized && currentSection == "Dashboard")
    {
        console.log("Initializing Dashboard");

        sectionInitialized = true;
        AddRunEventListener();
        AddDDFileEventListener();
        AddStoreEventListener();
        dashboard_settings.AddEventListeners();
        
        if (ddcut.ShouldShowWalkthrough("Dashboard"))
        {
            ddcut.SetShowWalkthrough("Dashboard", false);
            ShowDashboardWalkthrough();
        }
	}
}

var dashboardIntervalId = setInterval(InitializeDashboard, 100);
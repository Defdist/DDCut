const ddcut = require('../../node/ddcut.node');
const electron = require('electron');
const ipc = electron.ipcRenderer;
const BrowserWindow = electron.remote.BrowserWindow;
const path = require('path');
const url = require('url');

const pauseAfterGCode = ddcut.GetPauseAfterGCode();
const settings = ddcut.GetSettings();
const showSlider = settings.enable_slider;
const maxFeedRate = settings.maxFeedRate;

const DEBUG = electron.remote.getGlobal('DEBUG');

var finished = false;
var hasGCodes = false;
var currentStep = 0;

function PopulateSteps()
{
	var stepsList = document.getElementById("stepsList");
	var steps = ddcut.GetAllSteps();
	for (var i = 0; i < steps.length; i++)
	{
		var step = steps[i];


		var opt = document.createElement('option');
		opt.value = i;
		opt.text = step["Title"];
		stepsList.add(opt);
	}
}

// GCode files can be 100s of lines long. While retrieving the text from the ddcut plugin is relatively fast, displaying the text can be very time consuming.
// Since the browser is single-threaded, we must call setTimeout after changing the text to "Loading..." to allow the UI to redraw.
function ShowGCodes(gCodes)
{
	$("#GCode").html("<p style='font-size:16px; text-align: center;'><b>Loading...</b></p>");
	setTimeout(function() { $("#GCode").html(gCodes); }, 0);
}

function ShowImage()
{
	if ($("#ImageButton").hasClass("ToggledOff"))
	{
		$("#ImageButton").addClass("ToggledOn");
		$("#ImageButton").removeClass("ToggledOff");

		$("#RawButton").addClass("ToggledOff");
		$("#RawButton").removeClass("ToggledOn");

		$("#GCode").addClass("hidden");
		$("#Image").removeClass("hidden");
	}
}

function ShowRaw()
{
		if (!hasGCodes)
		{
			return;
		}

		if ($("#RawButton").hasClass("ToggledOff"))
		{
			$("#RawButton").addClass("ToggledOn");
			$("#RawButton").removeClass("ToggledOff");

			$("#ImageButton").addClass("ToggledOff");
			$("#ImageButton").removeClass("ToggledOn");

			$("#Image").addClass("hidden");
			$("#GCode").removeClass("hidden");

			const gCodes = $("#GCode").html();
			ShowGCodes(gCodes);
		}
}

function ShowStep(index)
{
	currentStep = index;
	var stepInfo = ddcut.GetStep(index);

	$("#Title").text(stepInfo["Title"].toUpperCase());
	$("#Description").text(stepInfo["Prompt"]);

	const gCodes = stepInfo["GCode"];
	if (gCodes)
	{
		hasGCodes = true;
		ShowGCodes(gCodes);
		$("#Warning").removeClass("hidden");
	}
	else
	{
		hasGCodes = false;
		$("#Warning").addClass("hidden");
		ShowImage();
	}

	document.getElementById("Image").src = 'data:image/jpeg;base64,' + stepInfo["Image"];

	$("#Next").removeClass("hidden");

	$("#StepCount").html("Step " + (index + 1) + "/" + document.getElementById("stepsList").length);

	$("#MillingStatus").addClass("hidden");
	$("#PreMilling").removeClass("hidden");
}

function AddStepSelectionListener()
{
	$('#stepsList').change(function(){
		if (DEBUG)
		{
			var index = parseInt($(this).val());
			ShowStep(index);
		}
		else if (finished)
		{
			$('#stepsList').val(-1);
		}
		else
		{
			$('#stepsList').val(currentStep);
		}
	});
}

function ShowNextStep()
{
	var index = parseInt($("#stepsList").val());
	if (index == document.getElementById("stepsList").length - 1)
	{
		$("#MiddleSection").addClass("hidden");
		$("#RightSection").addClass("hidden");
		$("#OperationComplete").removeClass("hidden");
		finished = true;
	}
	else
	{
		$("#stepsList").val(index + 1);
		ShowStep(index + 1);
	}
}

var millingStatusIntervalId = 0;
function CheckMillingStatus()
{
	var stepIndex = parseInt($("#stepsList").val());
	const percentage = ddcut.GetMillingStatus(stepIndex);
	$("#OperationPercentage").html(percentage + "%");
    document.getElementById("ProgressBarGreen").style.width = percentage + '%';

	if (percentage == 100)
	{
		clearInterval(millingStatusIntervalId);

		if (pauseAfterGCode)
		{
            // TODO: Handle this
            ShowNextStep();
		}
		else
		{
			ShowNextStep();
		}
	}
}

//////////////////////////////////////////////////////
// BUTTON LISTENERS
//////////////////////////////////////////////////////
function AddButtonListeners()
{
	//
	// Back to Main
	//
	document.getElementById("BackToMain").addEventListener("click",
		function(event)
		{
			// TODO: ddcut.AbortJob();
			ShowSection("Dashboard");
		}
	);

	//
	// Next
	//
	$("#Next").click(function() {
		if (hasGCodes)
		{
			$("#Modal").removeClass("hidden");
			$("#StartMillingDialog").removeClass("hidden");
		}
		else
		{
			ShowNextStep();
		}
	});

	//
	// Start Milling "Cancel"
	//
	document.getElementById("StartMillingCancelButton").addEventListener("click",
		function(event)
		{
			$("#StartMillingDialog").addClass("hidden");
			$("#Modal").addClass("hidden");
			$("#MillingStatus").addClass("hidden");
			$("#PreMilling").removeClass("hidden");
		}
	);

	//
	// Start Milling "Start"
	//
	document.getElementById("StartMillingStartButton").addEventListener("click",
		function(event)
		{
			$("#StartMillingDialog").addClass("hidden");
			$("#Modal").addClass("hidden");
			var stepIndex = parseInt($("#stepsList").val());
			$("#MillingStatus").removeClass("hidden");
			$("#PreMilling").addClass("hidden");
			$("#OperationPercentage").html("0%");
            document.getElementById("ProgressBarGreen").style.width = 1 + '%';
			ddcut.StartMilling(stepIndex);
			millingStatusIntervalId = setInterval(CheckMillingStatus, 100);
		}
	);

	//
	// FeedRate Override
	//
	if (showSlider)
	{
		$("#FeedRateOverride").removeClass("hidden");
		var slider = document.getElementById("FeedRateOverride");
		slider.setAttribute("max", maxFeedRate);
		slider.value = ddcut.GetFeedRate();
		console.log("Current feedrate: " + slider.value);

		slider.addEventListener("mouseup",
			function(event)
			{
				console.log("Updating feedrate to: " + this.value);
				ddcut.SetFeedRate(this.value);
			}
		);
	}

	//
	// Image Toggle
	//
	document.getElementById("ImageButton").addEventListener("click", ShowImage);


	//
	// Raw Toggle
	//
	document.getElementById("RawButton").addEventListener("click", ShowRaw);

	//
	// Stop
	//
	$("#Stop").click(function() {
		console.log("Stopping...");
		ddcut.EmergencyStop();
	});

	$("#StopText").click(function() {
		console.log("Stopping...");
		ddcut.EmergencyStop();
	});


	//
	// Operation Complete
	//
	$("#Restart").click(function() {
		ShowSection("Milling");
	});

	$("#Open").click(function() {
		ipc.send('open-file-dialog', 'SELECTED_FILE_MILLING');
	});

	var jobSelected = false;

	function ShowJobWindow()
	{
		let jobWindow = new BrowserWindow({width: 600, height: 380, frame: false, resizable: false,
			parent: electron.remote.getCurrentWindow(), modal: false, icon: path.join(__dirname, '../img/logo-white.png')});
		jobWindow.setMenu(null);
		jobWindow.on('closed', () => {
			setTimeout(function() {
				if (jobSelected)
				{
					ShowSection("Milling");
				}
				else
				{
					ShowSection("Dashboard");
				}
			},
			100);
			//$("#Modal").addClass('hidden');
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

		//$("#Modal").removeClass('hidden');

		const jobs = ddcut.GetJobs();
		jobWindow.webContents.on('did-finish-load', () => {
			jobWindow.webContents.send("JOBS", jobs, "SELECTED_JOB_MILLING");
		});
	}

	ipc.removeAllListeners('SELECTED_JOB_MILLING');
	ipc.on('SELECTED_JOB_MILLING',
		function (event, jobIndex)
		{
			ddcut.SetSelectedJob(jobIndex);
			jobSelected = true;
			//ShowSection("Milling");
		}
	);

	ipc.removeAllListeners('SELECTED_FILE_MILLING');
	ipc.on('SELECTED_FILE_MILLING',
		function (event, path)
		{
			//const currentDDFile = ddcut.GetDDFile();
			if (ddcut.IsValidDDFile(path))
			{
				ddcut.SetDDFile(path);

				ShowJobWindow();
			}
			else
			{
				// TODO: Alert user that .dd file is invalid.
			}
		}
	);

	$("#Back").click(function() {
		// TODO: ddcut.AbortJob();
		ShowSection("Dashboard");
	});
}

//////////////////////////////////////////////////////
// INITIALIZE
//////////////////////////////////////////////////////
function InitializeMilling()
{
	if (!sectionInitialized && currentSection == "Milling")
	{
        console.log("Initializing Milling");
        sectionInitialized = true;

        PopulateSteps();

        // Set first step as selected
        $("#stepsList").val(0);
        ShowStep(0);

        AddStepSelectionListener();
        AddButtonListeners();

        if (ddcut.ShouldShowWalkthrough("Milling")) {
            ddcut.SetShowWalkthrough("Milling", false);
            ShowMillingWalkthrough();
        }
	}
}

var millingIntervalId = setInterval(InitializeMilling, 1000);

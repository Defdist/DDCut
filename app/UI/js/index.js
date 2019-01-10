const ddcut = require('../../node/ddcut.node');

const electron = require('electron');
const path = require('path');
const url = require('url');
const shell = electron.shell;
const BrowserWindow = electron.remote.BrowserWindow;
const ipc = electron.ipcRenderer;

//////////////////////////////////////////////////////
// DAEMON INITIALIZATION
//////////////////////////////////////////////////////
ddcut.Initialize(function () {
    ddcutInitialized = true;
});

//////////////////////////////////////////////////////
// CONNECTION STATUS
//////////////////////////////////////////////////////
function UpdateConnectionStatus(newStatus)
{
	connected = newStatus;
	if (connected == 2)
	{
		document.getElementById("GGStatusIcon").src = "./img/green_oval.png";
		document.getElementById("GGStatusText").innerText = "Connected";
		document.getElementById("GGStatusText").style.color = "#069076";
	}
	else if (connected == 1)
	{
		document.getElementById("GGStatusIcon").src = "./img/yellow_oval.png";
		document.getElementById("GGStatusText").innerText = "Connecting...";
		document.getElementById("GGStatusText").style.color = "#fff200";
	}
	else
	{
		document.getElementById("GGStatusIcon").src = "./img/red_oval.png";
		document.getElementById("GGStatusText").innerText = connected == 0 ? "Not Connected" : "Failed to connect";
		document.getElementById("GGStatusText").style.color = "#ec1c24";
	}
}

function CheckConnectionStatus() 
{
	var newStatus = ddcut.GetGhostGunnerStatus();
	if (newStatus != connected)
	{
		UpdateConnectionStatus(newStatus);
	}
}

UpdateConnectionStatus(0);
var connectionStatusIntervalId = setInterval(CheckConnectionStatus, 50);

//////////////////////////////////////////////////////
// SOFTWARE UPDATES
//////////////////////////////////////////////////////
function ShowSoftwareUpdateWindow() {
    // Create the browser window.
    var softwareUpdateWindow = new BrowserWindow({
        width: 625, height: 500, frame: false, resizable: false, parent: electron.remote.getCurrentWindow(), modal: false,
        icon: path.join(__dirname, '../img/logo-white.png')
    })

    softwareUpdateWindow.setMenu(null);
    softwareUpdateWindow.on('closed', () => {
        $("#Modal").addClass('hidden');
        //softwareUpdateWindow = null;
    });

    softwareUpdateWindow.loadURL(
        url.format({
            pathname: path.join(__dirname, '../software_update.html'),
            protocol: 'file:',
            slashes: true
        })
    );

    $("#Modal").removeClass('hidden');
}

//////////////////////////////////////////////////////
// SUPPORT CENTER
//////////////////////////////////////////////////////
var customerSupportWindow = null;

function SendCustomerSupportRequest(event, email, description, includeLogs)
{
    ddcut.SendCustomerSupportRequest(email, description, includeLogs, function (error) {
        if (customerSupportWindow != null) {
            if (error == null) {
                customerSupportWindow.close();
            } else {
                event.sender.send("CUSTOMER_SUPPORT_RESULT", error);
            }
        }
    });
}

function ShowCustomerSupportWindow() {
    // Create the browser window.
    customerSupportWindow = new BrowserWindow({
        width: 625, height: 500, frame: false, resizable: false, parent: electron.remote.getCurrentWindow(), modal: false,
        icon: path.join(__dirname, '../img/logo-white.png')
    })

    customerSupportWindow.setMenu(null);
    customerSupportWindow.on('closed', () => {
        $("#Modal").addClass('hidden');
        customerSupportWindow = null;
    });

    customerSupportWindow.loadURL(
        url.format({
            pathname: path.join(__dirname, '../customer_support.html'),
            protocol: 'file:',
            slashes: true
        })
    );

    $("#Modal").removeClass('hidden');
}

function AddSupportCenterEventListener()
{
	var collapsible = document.getElementsByClassName("collapsible");

	for (var i = 0; i < collapsible.length; i++)
	{
		if (collapsible[i].id != "CustomerSupportHeader")
		{			
			collapsible[i].addEventListener("click", 
				function() 
				{
					this.classList.toggle("active");
					var content = this.nextElementSibling;
					if (content.style.maxHeight)
					{
						content.style.maxHeight = null;
					} 
					else 
					{
						content.style.maxHeight = content.scrollHeight + "px";
					} 
				}
			);
		}
    }

    document.getElementById("DashboardWalkthrough").addEventListener('click',
        function () {
            if (currentSection == "Dashboard") {
                $('#SupportCenterDialog').addClass("hidden");
                ShowDashboardWalkthrough();
            }
        }
    );

    document.getElementById("MillingWalkthrough").addEventListener('click',
        function () {
            if (currentSection == "Milling") {
                $('#SupportCenterDialog').addClass("hidden");
                ShowMillingWalkthrough();
            }
        }
    );

    document.getElementById("ViewManual").addEventListener('click',
        function () {
            shell.openExternal(__dirname + '/../doc/GG2Manual.pdf');
        }
    );

    document.getElementById("VisitSupport").addEventListener('click',
        function () {
            shell.openExternal("https://ghostgunner.net/");
        }
    );
	
	var closeButton = document.getElementById("SupportCenterClose");
	closeButton.addEventListener('click', 
		function (event) 
		{
			$('#SupportCenterDialog').addClass("hidden");
		}
	);
	
	electron.ipcRenderer.on("CUSTOMER_SUPPORT", SendCustomerSupportRequest);
	
	document.getElementById("CustomerSupportHeader").addEventListener("click", ShowCustomerSupportWindow);
	
	const supportButton = document.getElementById('Support');

	supportButton.addEventListener('click', 
		function (event) 
		{
			$('#SupportCenterDialog').removeClass("hidden");
		}
	);
}

AddSupportCenterEventListener();

//////////////////////////////////////////////////////
// MAIN MENU
//////////////////////////////////////////////////////
function AddMenuListeners()
{
	document.getElementById("MenuOpen").addEventListener('click',
		function() {
			if (!$("#MenuOpen").hasClass("inactive"))
			{
				ipc.send('open-file-dialog', 'SELECTED_FILE_DASHBOARD');
			}
		}	
	);
	
	document.getElementById("MenuUpdates").addEventListener('click',
        function () {
            if (!$("#MenuUpdates").hasClass("inactive")) {
                const BrowserWindow = electron.remote.BrowserWindow;
                const path = require('path');
                const url = require('url');
                let win = new BrowserWindow({
                    width: 220, height: 105, frame: true, resizable: false,
                    parent: electron.remote.getCurrentWindow(), modal: true, icon: path.join(__dirname, '../img/logo-white.png')
                });
                win.setMenu(null);
                const pageContent = ("<p><center>IN PROGRESS!<br/><br/>COMING SOON!</center></p>");

                win.loadURL('data:text/html;charset=UTF-8,' + encodeURIComponent(pageContent), {
                    baseURLForDataURL: `file://${__dirname}/app/`
                });
            }
		}	
	);
	
	document.getElementById("MenuExit").addEventListener('click',
		function() {
			electron.remote.getCurrentWindow().close();
		}	
    );

    document.getElementById("MenuViewManual").addEventListener('click',
        function () {
            shell.openExternal(__dirname + '/../doc/GG2Manual.pdf');
        }
    );

    document.getElementById("MenuCustomerSupport").addEventListener('click', ShowCustomerSupportWindow);

    document.getElementById("MenuVisitSupport").addEventListener('click',
        function () {
            shell.openExternal("https://ghostgunner.net/");
        }
    );
}

AddMenuListeners();

document.getElementById("GhostGunnerNet").addEventListener('click',
	function() {
		shell.openExternal("https://ghostgunner.net/");
	}	
);

window.onbeforeunload = function (e)
{
	console.log("Shutting down..");
	ddcut.Shutdown();
}
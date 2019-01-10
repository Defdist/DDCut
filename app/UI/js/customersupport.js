const electron = require('electron');

document.getElementById("CancelButton").addEventListener("click",
	function()
	{
		electron.remote.getCurrentWindow().close();
	}
);

document.getElementById("SendReportButton").addEventListener("click",
	function()
    {
        electron.ipcRenderer.once("CUSTOMER_SUPPORT_ERROR", function (event, error) {
            document.getElementById("Error").innerHTML = "";

            //if (error.hasOwnProperty("name")) {
            //    document.getElementById("Error").innerText += "NAME: " + error.name + "<br/>";
            //}

            if (error.hasOwnProperty("email")) {
                document.getElementById("Error").innerHTML += "EMAIL: " + error.email + "<br/>";
            }

            if (error.hasOwnProperty("description")) {
                document.getElementById("Error").innerHTML += "DESCRIPTION: " + error.description;
            }

            document.getElementById("Error").classList.remove("hidden");
        });

		var email = document.getElementById("Email").value;
		var description = document.getElementById("Description").value;
		var includeLogs = document.getElementById("IncludeLogs").checked;

        electron.ipcRenderer.send("CUSTOMER_SUPPORT_REQUEST", email, description, includeLogs);
	}
);
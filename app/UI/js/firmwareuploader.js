const electron = require('electron');

document.getElementById("CloseButton").addEventListener("click",
    function () {
        electron.remote.getCurrentWindow().close();
    }
);

electron.ipcRenderer.on('FIRMWARE_UPLOAD_STATUS',
    function (event, percentage) {
        if (percentage >= 0) {
            document.getElementById("StatusText").innerHTML = percentage + "%";
            document.getElementById("StatusBar").style.width = (2.50 * percentage) + "px";

            if (percentage == 100) {
                document.getElementById("CloseButton").classList.remove("hidden");
            }
        } else {
            document.getElementById("StatusText").innerHTML = "ERROR";
            document.getElementById("CloseButton").classList.remove("hidden");
        }
    }
);
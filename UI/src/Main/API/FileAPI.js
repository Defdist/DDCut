"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const ddcut_1 = require("ddcut");
const electron_1 = require("electron");
const path = require('path');
const fs = require('fs');
class FileAPI {
    static Initialize() {
        let execPath = path.dirname(process.execPath);
        electron_1.ipcMain.on('File::OpenFileDialog', function (event) {
            electron_1.dialog.showOpenDialog({
                defaultPath: path.join(execPath, 'Cutting Code'),
                properties: ['openFile', 'treatPackageAsDirectory'],
                filters: [{ name: "Milling Files", extensions: ["ab", "dd"] }]
            }, function (files) {
                if (files) {
                    ddcut_1.SetDDFile(files[0]);
                    if (ddcut_1.SetDDFile(files[0]) == true) {
                        event.sender.send("ShowJobSelection", ddcut_1.GetJobs());
                    }
                    else {
                        event.sender.send("InvalidDDFile", files[0]);
                    }
                }
            });
        });
        electron_1.ipcMain.on("File::ReadFile", function (event, fileName) {
            console.log("Reading file: " + fileName);
            fs.readFile(fileName, 'utf-8', function (err, data) {
                event.sender.send('File::FileOpened', data);
            });
        });
    }
    ;
}
exports.default = FileAPI;
//# sourceMappingURL=FileAPI.js.map

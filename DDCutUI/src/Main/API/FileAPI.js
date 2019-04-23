"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var DDCut = require('../../../Backend/ddcut.node');
var electron_1 = require("electron");
var path = require('path');
var fs = require('fs');
var FileAPI = /** @class */ (function () {
    function FileAPI() {
    }
    FileAPI.Initialize = function () {
        var execPath = path.dirname(process.execPath);
        electron_1.ipcMain.on('File::OpenFileDialog', function (event) {
            electron_1.dialog.showOpenDialog({
                defaultPath: path.join(execPath, 'Cutting Code'),
                properties: ['openFile', 'treatPackageAsDirectory'],
                filters: [{ name: "DD Files", extensions: ["dd"] }]
            }, function (files) {
                if (files) {
                    DDCut.SetDDFile(files[0]);
                    if (DDCut.SetDDFile(files[0]) == true) {
                        event.sender.send("ShowJobSelection", DDCut.GetJobs());
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
    };
    ;
    return FileAPI;
}());
exports.default = FileAPI;
//# sourceMappingURL=FileAPI.js.map
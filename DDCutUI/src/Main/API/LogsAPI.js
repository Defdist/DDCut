"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var DDCut = require('../../../Backend/ddcut.node');
var electron_1 = require("electron");
var FileAPI = /** @class */ (function () {
    function FileAPI() {
    }
    FileAPI.Initialize = function () {
        electron_1.ipcMain.on('Logs::GetLogFile', function (event) {
            event.returnValue = DDCut.GetLogPath();
        });
    };
    ;
    return FileAPI;
}());
exports.default = FileAPI;
//# sourceMappingURL=LogsAPI.js.map
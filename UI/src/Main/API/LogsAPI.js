"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const ddcut_1 = require("ddcut");
const electron_1 = require("electron");
class FileAPI {
    static Initialize() {
        electron_1.ipcMain.on('Logs::GetLogFile', function (event) {
            event.returnValue = ddcut_1.GetLogPath();
        });
    }
    ;
}
exports.default = FileAPI;
//# sourceMappingURL=LogsAPI.js.map

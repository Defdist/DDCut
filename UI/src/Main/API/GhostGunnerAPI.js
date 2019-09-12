"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const ddcut_1 = require("ddcut");
const electron_1 = require("electron");
class FileAPI {
    static Initialize() {
        electron_1.ipcMain.on('Ghost::GetAvailableGhosts', function (event) {
            var availableGhostGunners = ddcut_1.GetAvailableGhostGunners();
            event.returnValue = availableGhostGunners;
        });
        electron_1.ipcMain.on('Ghost::ChooseGhost', function (event, path, serialNumber) {
            ddcut_1.SelectGhostGunner(path, serialNumber);
        });
    }
    ;
}
exports.default = FileAPI;
//# sourceMappingURL=GhostGunnerAPI.js.map

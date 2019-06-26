"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const ddcut_1 = require("ddcut");
const electron_1 = require("electron");
class WalkthroughAPI {
    static Initialize() {
        electron_1.ipcMain.on('Walkthrough::ShouldDisplay', function (event, walkthroughType) {
            event.returnValue = ddcut_1.ShouldShowWalkthrough(walkthroughType);
        });
        electron_1.ipcMain.on('Walkthrough::SetShowWalkthrough', function (event, walkthroughType, value) {
            event.returnValue = ddcut_1.SetShowWalkthrough(walkthroughType, value);
        });
    }
    ;
}
exports.default = WalkthroughAPI;
//# sourceMappingURL=WalkthroughAPI.js.map

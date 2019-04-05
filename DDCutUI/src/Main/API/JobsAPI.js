"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var DDCut = require('../../../Backend/ddcut.node');
var electron_1 = require("electron");
var JobsAPI = /** @class */ (function () {
    function JobsAPI() {
    }
    JobsAPI.Initialize = function () {
        electron_1.ipcMain.on('Jobs::SelectJob', function (event, jobIndex) {
            if (DDCut.SetSelectedJob(jobIndex) == true) {
                event.sender.send('Jobs::JobSelected');
            }
            else {
                event.sender.send('Jobs::JobSelectionFailed');
            }
        });
        electron_1.ipcMain.on('Jobs::GetSteps', function (event) {
            event.returnValue = DDCut.GetAllSteps();
        });
        electron_1.ipcMain.on('Jobs::GetStep', function (event, stepIndex) {
            event.returnValue = DDCut.GetStep(stepIndex);
        });
        electron_1.ipcMain.on('Jobs::StartMilling', function (event, stepIndex) {
            DDCut.StartMilling(stepIndex);
        });
        electron_1.ipcMain.on('Jobs::GetProgress', function (event, stepIndex) {
            event.returnValue = DDCut.GetMillingStatus(stepIndex);
        });
        electron_1.ipcMain.on('Jobs::EmergencyStop', function (event, stepIndex) {
            event.returnValue = DDCut.EmergencyStop();
        });
    };
    ;
    return JobsAPI;
}());
exports.default = JobsAPI;
//# sourceMappingURL=JobsAPI.js.map
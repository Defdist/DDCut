"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const ddcut_1 = require("ddcut");
const electron_1 = require("electron");
const DDController_1 = require("../DDController");
class JobsAPI {
    static Initialize() {
        electron_1.ipcMain.on('Jobs::SelectJob', function (event, jobIndex) {
            if (ddcut_1.SetSelectedJob(jobIndex) == true) {
                event.sender.send('Jobs::JobSelected');
            }
            else {
                event.sender.send('Jobs::JobSelectionFailed');
            }
        });
        electron_1.ipcMain.on('Jobs::GetSteps', function (event) {
            event.returnValue = ddcut_1.GetAllSteps();
        });
        electron_1.ipcMain.on('Jobs::GetStep', function (event, stepIndex) {
            event.returnValue = ddcut_1.GetStep(stepIndex);
        });
        electron_1.ipcMain.on('Jobs::StartMilling', function (event, stepIndex) {
            JobsAPI.milling = true;
            DDController_1.default.SetMillingStatus(true);
            ddcut_1.StartMilling(stepIndex);
        });
        electron_1.ipcMain.on('Jobs::GetProgress', function (event, stepIndex) {
            event.sender.send('Jobs::ReadWrites', ddcut_1.GetReadWrites());
            let status = ddcut_1.GetMillingStatus(stepIndex);
            if (status.percentage == 100 || status.percentage < 0) {
                DDController_1.default.SetMillingStatus(false);
                JobsAPI.milling = false;
            }
            event.returnValue = status;
        });
        electron_1.ipcMain.on('Jobs::EmergencyStop', function (event, stepIndex) {
            event.returnValue = ddcut_1.EmergencyStop();
            DDController_1.default.SetMillingStatus(false);
        });
    }
    ;
}
exports.default = JobsAPI;
//# sourceMappingURL=JobsAPI.js.map

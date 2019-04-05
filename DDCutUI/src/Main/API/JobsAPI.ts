const DDCut = require('../../../Backend/ddcut.node');
import { ipcMain, Event, dialog } from 'electron';

class JobsAPI {
    static Initialize() {
        ipcMain.on('Jobs::SelectJob', function (event: Event, jobIndex: number) {
            if (DDCut.SetSelectedJob(jobIndex) == true) {
                event.sender.send('Jobs::JobSelected');
            } else {
                event.sender.send('Jobs::JobSelectionFailed');
            }
        });

        ipcMain.on('Jobs::GetSteps', function (event: Event) {
            event.returnValue = DDCut.GetAllSteps();
        });

        ipcMain.on('Jobs::GetStep', function (event: Event, stepIndex: number) {
            event.returnValue = DDCut.GetStep(stepIndex);
        });

        ipcMain.on('Jobs::StartMilling', function (event: Event, stepIndex: number) {
            DDCut.StartMilling(stepIndex);
        });

        ipcMain.on('Jobs::GetProgress', function (event: Event, stepIndex: number) {
            event.returnValue = DDCut.GetMillingStatus(stepIndex);
        });

        ipcMain.on('Jobs::EmergencyStop', function (event: Event, stepIndex: number) {
            event.returnValue = DDCut.EmergencyStop();
        });
    };
}

export default JobsAPI;
const DDCut = require('../../../Backend/ddcut.node');
import { ipcMain, Event, dialog } from 'electron';
import DDController from '../DDController';

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
			JobsAPI.milling = true;
			DDController.SetMillingStatus(true);
            DDCut.StartMilling(stepIndex);
        });

        ipcMain.on('Jobs::GetProgress', function (event: Event, stepIndex: number) {
            event.sender.send('Jobs::ReadWrites', DDCut.GetReadWrites());
			let status: number = DDCut.GetMillingStatus(stepIndex);
			if (status == 100 || status < 0) {
				DDController.SetMillingStatus(false);
				JobsAPI.milling = false;
			}

            event.returnValue = status;
        });

        ipcMain.on('Jobs::EmergencyStop', function (event: Event, stepIndex: number) {
            event.returnValue = DDCut.EmergencyStop();
			DDController.SetMillingStatus(false);
        });
    };
}

export default JobsAPI;
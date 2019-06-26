import DDCut from 'ddcut';
import { ipcMain, Event } from 'electron';

class FileAPI {
    static Initialize() {
        ipcMain.on('Logs::GetLogFile', function (event: Event) {
            event.returnValue = DDCut.GetLogPath();
        });
    };
}

export default FileAPI;

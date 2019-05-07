const DDCut = require('../../../Backend/ddcut.node');
import { ipcMain, Event } from 'electron';

class FileAPI {
    static Initialize() {
        ipcMain.on('Logs::GetLogFile', function (event: Event) {
            event.returnValue = DDCut.GetLogPath();
        });
    };
}

export default FileAPI;
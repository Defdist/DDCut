const DDCut = require('../../../Backend/ddcut.node');
import { ipcMain, Event } from 'electron';

class FileAPI {
    static Initialize() {
        ipcMain.on('Logs::GetLogFile', function (event: Event) {
            console.log("GetLogFile");
            var logPath = DDCut.GetLogPath();
            console.log(logPath);
            event.returnValue = "P:\Git\Github\DDCutMaster\DDCutUI\logs\ddcut.log;
        });
    };
}

export default FileAPI;
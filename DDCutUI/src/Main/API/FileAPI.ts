const DDCut = require('../../../Backend/ddcut.node');
import { ipcMain, Event, dialog } from 'electron';
const path = require('path');

class FileAPI {
    static Initialize() {
        let execPath = path.dirname(process.execPath);
        ipcMain.on('File::OpenFileDialog', function (event: Event) {
            dialog.showOpenDialog(
                {
                    defaultPath: path.join(execPath, 'Cutting Code'),
                    properties: ['openFile', 'treatPackageAsDirectory'],
                    filters: [{ name: "DD Files", extensions: ["dd"] }]
                },
                function (files) {
                    if (files) {
                        DDCut.SetDDFile(files[0]);
                        if (DDCut.SetDDFile(files[0]) == true) {
                            event.sender.send("ShowJobSelection", DDCut.GetJobs());
                        } else {
                            event.sender.send("InvalidDDFile", files[0]);
                        }
                    }
                }
            )
        });
    };
}

export default FileAPI;
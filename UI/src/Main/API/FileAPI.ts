import DDCut from 'ddcut';
import { ipcMain, Event, dialog } from 'electron';
const path = require('path');
const fs = require('fs');

class FileAPI {
    static Initialize() {
        let execPath = path.dirname(process.execPath);
        ipcMain.on('File::OpenFileDialog', function (event: Event) {
            dialog.showOpenDialog(
                {
                    defaultPath: path.join(execPath, 'Cutting Code'),
                    properties: ['openFile', 'treatPackageAsDirectory'],
                    filters: [{ name: "Milling Files", extensions: ["ab", "dd"] }]
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

        ipcMain.on("File::ReadFile", function (event: Event, fileName: string) {
            console.log("Reading file: " + fileName);
            fs.readFile(fileName, 'utf-8', function (err, data) {
                event.sender.send('File::FileOpened', data);
            });
        });
    };
}

export default FileAPI;

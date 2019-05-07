const DDCut = require('../../../Backend/ddcut.node');
import { ipcMain, Event } from 'electron';

class FileAPI {
    static Initialize() {
        ipcMain.on('Ghost::GetAvailableGhosts', function (event: Event) {
            var availableGhostGunners = DDCut.GetAvailableGhostGunners();
            event.returnValue = availableGhostGunners;
        });

        ipcMain.on('Ghost::ChooseGhost', function (event: Event, path: string, serialNumber: string) {
            DDCut.SelectGhostGunner(path, serialNumber);
        });
    };
}

export default FileAPI;
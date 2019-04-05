const DDCut = require('../../../Backend/ddcut.node');
import { ipcMain, Event } from 'electron';
import FirmwareUpdate from '../../Common/Models/FirmwareUpdate';
import FirmwareVersion from '../../Common/Models/FirmwareVersion';

class FirmwareAPI {
    static Initialize() {

        /*
         *
         * napi_get_named_property(env, args[0], "Version", &versionProperty);
	     * napi_get_named_property(env, args[0], "Description", &descriptionProperty);
	     * napi_get_named_property(env, args[0], "Files", &filesArray);
         * 
         * DECLARE_NAPI_METHOD("UploadFirmware", UploadFirmware),
		 * DECLARE_NAPI_METHOD("GetFirmwareUploadStatus", GetFirmwareUploadStatus),
		 * DECLARE_NAPI_METHOD("GetFirmwareVersion", GetFirmwareVersion),
		 * DECLARE_NAPI_METHOD("GetAvailableFirmwareUpdates", GetAvailableFirmwareUpdates)
         * 
         */
        ipcMain.on("Firmware::GetAvailableFirmwareUpdates", function (event: Event) {
            let availableUpdates = DDCut.GetAvailableFirmwareUpdates();
            let version = availableUpdates["Version"];
            let description = availableUpdates["Description"];
            let files = availableUpdates["Files"];
            event.returnValue = new FirmwareUpdate(version, description, files);
        });

        ipcMain.on("Firmware::GetFirmwareUploadStatus", function (event: Event) {
            event.returnValue = DDCut.GetFirmwareUploadStatus();
        });

        ipcMain.on("Firmware::GetFirmwareVersion", function (event: Event) {
            let firmwareVersion = DDCut.GetFirmwareVersion();
            let grblVersion = firmwareVersion["grblVersion"];
            let ddVersion = firmwareVersion["ddVersion"];
            event.returnValue = new FirmwareVersion(grblVersion, ddVersion);
        });

        ipcMain.on("Firmware::UploadFirmware", function (version: string, description: string, files: string[]) {
            let firmwareUpdate = new FirmwareUpdate(version, description, files);
            DDCut.UploadFirmware(firmwareUpdate);
        });
    };
}

export default FirmwareAPI;
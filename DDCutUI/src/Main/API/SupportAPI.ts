const DDCut = require('../../../Backend/ddcut.node');
import { ipcMain, Event } from 'electron';

class SupportAPI {
    static Initialize() {
        ipcMain.on('Support::SendRequest', function (event: Event, email: string, description: string, includeLogs: boolean) {
            console.log("Email: " + email);
            console.log("Description: " + description);
            console.log("IncludeLogs: " + includeLogs);
            DDCut.SendCustomerSupportRequest(email, description, includeLogs, (error: any) => {
                console.log(error);
                event.returnValue = error;
            });
        });
    };
}

export default SupportAPI;
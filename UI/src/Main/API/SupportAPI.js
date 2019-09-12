"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const ddcut_1 = require("ddcut");
const electron_1 = require("electron");
class SupportAPI {
    static Initialize() {
        electron_1.ipcMain.on('Support::SendRequest', function (event, email, description, includeLogs) {
            console.log("Email: " + email);
            console.log("Description: " + description);
            console.log("IncludeLogs: " + includeLogs);
            ddcut_1.SendCustomerSupportRequest(email, description, includeLogs, (error) => {
                console.log(error);
                event.returnValue = error;
            });
        });
    }
    ;
}
exports.default = SupportAPI;
//# sourceMappingURL=SupportAPI.js.map

"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var DDCut = require('../../../Backend/ddcut.node');
var electron_1 = require("electron");
var SupportAPI = /** @class */ (function () {
    function SupportAPI() {
    }
    SupportAPI.Initialize = function () {
        electron_1.ipcMain.on('Support::SendRequest', function (event, email, description, includeLogs) {
            console.log("Email: " + email);
            console.log("Description: " + description);
            console.log("IncludeLogs: " + includeLogs);
            DDCut.SendCustomerSupportRequest(email, description, includeLogs, function (error) {
                console.log(error);
                event.returnValue = error;
            });
        });
    };
    ;
    return SupportAPI;
}());
exports.default = SupportAPI;
//# sourceMappingURL=SupportAPI.js.map
"use strict";
exports.__esModule = true;
var FirmwareUpdate = /** @class */ (function () {
    function FirmwareUpdate(version, description, files) {
        this.version = version;
        this.description = description;
        this.files = files;
    }
    Object.defineProperty(FirmwareUpdate.prototype, "getVersion", {
        get: function () {
            return this.version;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(FirmwareUpdate.prototype, "getDescription", {
        get: function () {
            return this.description;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(FirmwareUpdate.prototype, "getFiles", {
        get: function () {
            return this.files;
        },
        enumerable: true,
        configurable: true
    });
    return FirmwareUpdate;
}());
exports["default"] = FirmwareUpdate;

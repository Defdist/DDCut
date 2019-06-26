"use strict";
exports.__esModule = true;
var FirmwareVersion = /** @class */ (function () {
    function FirmwareVersion(grblVersion, ddVersion) {
        this.grblVersion = grblVersion;
        this.ddVersion = ddVersion;
    }
    Object.defineProperty(FirmwareVersion.prototype, "getGRBLVersion", {
        get: function () {
            return this.grblVersion;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(FirmwareVersion.prototype, "getDDVersion", {
        get: function () {
            return this.ddVersion;
        },
        enumerable: true,
        configurable: true
    });
    return FirmwareVersion;
}());
exports["default"] = FirmwareVersion;

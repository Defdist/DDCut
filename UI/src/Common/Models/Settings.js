"use strict";
exports.__esModule = true;
var Settings = /** @class */ (function () {
    function Settings(pauseAfterGCode, timeout, enableSlider, maxFeedRate) {
        this.pauseAfterGCode = pauseAfterGCode;
        this.timeout = timeout;
        this.enable_slider = enableSlider;
        this.maxFeedRate = maxFeedRate;
    }
    Object.defineProperty(Settings.prototype, "getPauseAfterGCode", {
        get: function () {
            return this.pauseAfterGCode;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(Settings.prototype, "getTimeout", {
        get: function () {
            return this.timeout;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(Settings.prototype, "getEnableSlider", {
        get: function () {
            return this.enable_slider;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(Settings.prototype, "getMaxFeedRate", {
        get: function () {
            return this.maxFeedRate;
        },
        enumerable: true,
        configurable: true
    });
    return Settings;
}());
exports["default"] = Settings;

declare class Settings {
    private pauseAfterGCode;
    private timeout;
    private enable_slider;
    private maxFeedRate;
    constructor(pauseAfterGCode: boolean, timeout: number, enableSlider: boolean, maxFeedRate: number);
    readonly getPauseAfterGCode: boolean;
    readonly getTimeout: number;
    readonly getEnableSlider: boolean;
    readonly getMaxFeedRate: number;
}
export default Settings;

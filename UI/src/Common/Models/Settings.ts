
class Settings {
    private pauseAfterGCode: boolean;
    private timeout: number;
    private enable_slider: boolean;
    private maxFeedRate: number;

    constructor(pauseAfterGCode: boolean, timeout: number, enableSlider: boolean, maxFeedRate: number) {
        this.pauseAfterGCode = pauseAfterGCode;
        this.timeout = timeout;
        this.enable_slider = enableSlider;
        this.maxFeedRate = maxFeedRate;
    }

    get getPauseAfterGCode(): boolean {
        return this.pauseAfterGCode;
    }

    get getTimeout(): number {
        return this.timeout;
    }

    get getEnableSlider(): boolean {
        return this.enable_slider;
    }

    get getMaxFeedRate(): number {
        return this.maxFeedRate;
    }
}

export default Settings;
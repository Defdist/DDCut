
class FirmwareVersion {
    private grblVersion: string;
    private ddVersion: string;

    constructor(grblVersion: string, ddVersion: string) {
        this.grblVersion = grblVersion;
        this.ddVersion = ddVersion;
    }

    get getGRBLVersion(): string {
        return this.grblVersion;
    }

    get getDDVersion(): string {
        return this.ddVersion;
    }
}

export default FirmwareVersion;
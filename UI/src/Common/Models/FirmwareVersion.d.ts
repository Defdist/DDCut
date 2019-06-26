declare class FirmwareVersion {
    private grblVersion;
    private ddVersion;
    constructor(grblVersion: string, ddVersion: string);
    readonly getGRBLVersion: string;
    readonly getDDVersion: string;
}
export default FirmwareVersion;

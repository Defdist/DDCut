declare class FirmwareUpdate {
    private version;
    private description;
    private files;
    constructor(version: string, description: string, files: string[]);
    readonly getVersion: string;
    readonly getDescription: string;
    readonly getFiles: string[];
}
export default FirmwareUpdate;

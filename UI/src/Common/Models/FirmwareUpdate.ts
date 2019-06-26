
class FirmwareUpdate {
    private version: string;
    private description: string;
    private files: string[];

    constructor(version: string, description: string, files: string[]) {
        this.version = version;
        this.description = description;
        this.files = files;
    }

    get getVersion(): string {
        return this.version;
    }

    get getDescription(): string {
        return this.description;
    }

    get getFiles(): string[] {
        return this.files;
    }
}

export default FirmwareUpdate;
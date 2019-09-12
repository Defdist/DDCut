import { BrowserWindow } from 'electron';
declare class DDController {
    static Initialize(): void;
    static SetWindow(window: BrowserWindow): void;
    static Shutdown(): void;
    static SetMillingStatus(milling: boolean): void;
}
export default DDController;

import DDCut from 'ddcut';
import { ipcMain, Event } from 'electron';

class WalkthroughAPI {
    static Initialize() {
        ipcMain.on('Walkthrough::ShouldDisplay', function (event: Event, walkthroughType: string) {
            event.returnValue = DDCut.ShouldShowWalkthrough(walkthroughType);
        });

        ipcMain.on('Walkthrough::SetShowWalkthrough', function (event: Event, walkthroughType: string, value: boolean) {
            event.returnValue = DDCut.SetShowWalkthrough(walkthroughType, value);
        });
    };
}

export default WalkthroughAPI;

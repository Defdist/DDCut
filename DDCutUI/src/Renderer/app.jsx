import * as React from 'react';
import { MuiThemeProvider, createMuiTheme } from '@material-ui/core/styles';
import { ipcRenderer } from 'electron';
import Routes from './Routes';
import { Titlebar, Color } from 'custom-electron-titlebar';
import BottomToolbar from './components/BottomToolbar';

const theme = createMuiTheme({
    palette: {
        secondary: {
            main: "#069076",
        },
        primary: {
            main: '#ffffff',
            dark: '#888888',
            dark: '#333333',
        },
        text: {
            primary: "#ffffff",
            secondary: "#cccccc",
            disabled: "#444444"
        },
        background: {
            paper: "#000000"
        },
    },
    typography: {
        useNextVariants: true,
        // Use the system font instead of the default Roboto font.
        fontFamily: [
            '"Lato"',
            'sans-serif'
        ].join(',')
    },
    props: {
        MuiButtonBase: {
            disableRipple: true
        },
        MuiDialog: {
            TransitionProps: {
                enter: false,
                exit: false,
                timeout: 0
            }
        }
    },
    overrides: {
        MuiFormControl: {
            root: {
                backgroundColor: '#555555',
            },
        },
        MuiDialog: {
            paper: {
                border: '#FFFFFF 1px solid' 
            }
        }
    }
});

export default class App extends React.Component {
    constructor() {
        super();
        this.state = {
            ghostGunnerStatus: 0,
			millingInProgress: false
        };
    }

    componentWillMount() {
        if (!this.props.data) {
            new Titlebar({
                backgroundColor: Color.fromHex('#333333'),
                icon: './static/img/DD_icon.ico',
                menu: null,
                titleHorizontalAlignment: "left"
            });
        }
    }

    render() {
        function updateStatus(event, newStatus) {
            if (newStatus != this.state.ghostGunnerStatus) {
                this.setState({
                    ghostGunnerStatus: newStatus
                });
            }
        }

        function updateMillingStatus(event, newStatus) {
            if (newStatus != this.state.millingInProgress) {
                this.setState({
                    millingInProgress: newStatus
                });
            }
        }

        ipcRenderer.removeAllListeners("DD_UpdateGGStatus");
        ipcRenderer.on("DD_UpdateGGStatus", updateStatus.bind(this));

        ipcRenderer.removeAllListeners("Milling::Status");
        ipcRenderer.on("Milling::Status", updateMillingStatus.bind(this));

        document.getElementsByClassName('window-appicon')[0].style.width = "20px";
        document.getElementsByClassName('window-appicon')[0].style.height = "20px";
        document.getElementsByClassName('window-appicon')[0].style.backgroundSize = "20px 20px";
        document.getElementsByClassName('window-appicon')[0].style.marginLeft = "5px";

        return (
            <React.Fragment>
                <MuiThemeProvider theme={theme}>
                    <Routes status={this.state.ghostGunnerStatus} />
                    <BottomToolbar status={this.state.ghostGunnerStatus} milling={this.state.millingInProgress} />
                </MuiThemeProvider>
            </React.Fragment>
        );
    }
}
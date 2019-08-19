import * as React from 'react';
import { MuiThemeProvider, createMuiTheme } from '@material-ui/core/styles';
import { ipcRenderer } from 'electron';
import Routes from './Routes';
import { Titlebar, Color } from 'custom-electron-titlebar';
import BottomToolbar from './components/BottomToolbar';
import { version } from '../../package.json';
import app from 'app';


const theme = createMuiTheme({
    palette: {
        secondary: {
            main: app.colors.secondary,
        },
        primary: {
            main: '#ffffff',
            dark: '#888888',
            dark: '#333333',
        },
        text: {
            primary: app.colors.textPrimary,
            secondary: app.colors.textSecondary,
            disabled: "#444444"
        },
        background: {
            paper: "#000000"
        },
    },
    typography: {
        useNextVariants: true,
        // Use the system font instead of the default Roboto font.
        fontFamily: app.fonts.join(','),
        root: {
            fontWeight: app.font.weight
        },
        body1: {
            fontSize: 14,
            fontWeight: app.font.weight
        },
        h6: {
            fontWeight: app.font.weight
        }
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
                backgroundColor: app.colors.form,
            },
        },
        MuiDialog: {
            paper: {
                border: app.modal.border,
                color: app.modal.color,
                backgroundImage: `url(${app.modal.background})`
            }
        },
        MuiFab: {
            root: {
                fontFamily: app.fonts.join(','),
                fontWeight: app.font.weight
            }
        },
        MuiOutlinedInput: {
            input: {
                padding: '5px 10px'
            }
        },
        MuiCssBaseline: {
            '@global': {
                '*::webkit-scrollbar': {
                    width: '10px',
                    backgroundColor: app.colors.scrollbar
                },
                '@font-weight': app.font.weight
            },
        },
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
            if (app.name == 'ABCut') {
                document.title = 'ABCut';
            } else {
                document.title = app.name + ' v' + version;
            }

            let titlebar = new Titlebar({
                backgroundColor: Color.fromHex('#333333'),
                icon: app.titlebar.icon,
                menu: null,
                titleHorizontalAlignment: "left"
            });
        }
    }

	componentDidMount() {
		if (ipcRenderer.sendSync("Walkthrough::ShouldDisplay", "Dashboard")) {
			window.ShowDashboardWalkthrough(app.machine_name);
			ipcRenderer.send("Walkthrough::SetShowWalkthrough", "Dashboard", false);
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

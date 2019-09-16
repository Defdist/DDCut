import React from 'react';
import PropTypes from 'prop-types';
import withStyles from '@material-ui/core/styles/withStyles';
import path from "path";
import { ipcRenderer } from 'electron';
import {
    Dialog, Typography, Button, Grid, DialogTitle,
    DialogContent, DialogActions, Select, LinearProgress
} from '@material-ui/core';

const styles = theme => ({
    cancel: {
        marginTop: -theme.spacing.unit,
        marginBottom: theme.spacing.unit
    },
    select: {
        marginTop: -theme.spacing.unit,
        marginBottom: theme.spacing.unit
    },
    firmwareList: {
        width: "100%"
    },
    firmwareText: {
        width: "calc(100% - 6px)"
    },
});

class FirmwareUpdater extends React.Component {
    constructor() {
        super();
        this.state = {
            showUpdates: false,
            showUpdater: false,
            updatesLoaded: false,
            selectedIndex: -1,
            availableFirmware: [],
            uploadStatus: -1
        };

        this.uploadFirmwareStatusIntervalId = null;
        this.onAvailableFirmware = this.onAvailableFirmware.bind(this);
        this.updateFirmwareUploadStatus = this.updateFirmwareUploadStatus.bind(this);
        this.closeUpdater = this.closeUpdater.bind(this);
    }

    closeUpdater() {
        this.setState({
            showUpdater: false,
            updatesLoaded: false,
            showUpdates: false,
            selectedIndex: -1,
            uploadStatus: -1
        });

        //const { refreshFirmwareVersion } = this.props;
        //refreshFirmwareVersion();
    }

    updateFirmwareUploadStatus() {
        if (!this.state.showUpdater) {
            clearInterval(this.uploadFirmwareStatusIntervalId);
        } else {
            const status = ipcRenderer.sendSync("Firmware::GetFirmwareUploadStatus");
            if (status != this.state.uploadStatus) {
                if (status < 0) {
                    // TODO:
                    clearInterval(this.uploadFirmwareStatusIntervalId);
                    this.setState({ uploadStatus: status });
                } else {
                
                    //document.getElementById("StatusText").innerHTML = status + "%";
                    //document.getElementById("StatusBar").style.width = (2.50 * status) + "px";

                    if (status == 100) {
                        clearInterval(this.uploadFirmwareStatusIntervalId);
                        this.setState({ uploadStatus: status });
                    } else {
                        this.setState({ uploadStatus: status });
                    }
                }
            }
        }
    }

    onAvailableFirmware(event, availableUpdates) {
        this.setState({ availableFirmware: availableUpdates });
    }

    render() {
        const { classes, refreshFirmwareVersion } = this.props;    
    
        if (this.state.showUpdates) {
            if (!this.state.updatesLoaded) {
                ipcRenderer.removeAllListeners("Firmware::UpdatesAvailable");
                ipcRenderer.on("Firmware::UpdatesAvailable", this.onAvailableFirmware);

                ipcRenderer.send("Firmware::GetAvailableFirmwareUpdates");

                this.setState({ updatesLoaded: true });
            }
        }

        function handleSelect(event) {
            if (this.state.selectedIndex >= 0) {
                const firmwareUpdate = this.state.availableFirmware[this.state.selectedIndex];
                const success = ipcRenderer.sendSync("Firmware::UploadFirmware", firmwareUpdate.version, firmwareUpdate.description, firmwareUpdate.files);
                if (success) {
                    console.log("SUCCESS");
                    this.uploadFirmwareStatusIntervalId = setInterval(this.updateFirmwareUploadStatus, 50);
                    this.setState({ showUpdater: true });
                    return;
                }
            }

            this.closeUpdater();
        }

        function handleSelectFirmware(event) {
            this.setState({ selectedIndex: event.target.selectedIndex });
        }

        function getButtons(instance) {
            if (!instance.state.showUpdater) {
                return (
                    <Grid container spacing={8} justify="center">
                        <Grid item xs={3}>
                            <Button
                                variant="contained"
                                className={classes.cancel}
                                onClick={instance.closeUpdater}
                                fullWidth
                            >
                                CANCEL
                            </Button>
                        </Grid>
                        <Grid item xs={3}>
                            <Button
                                variant="contained"
                                className={classes.select}
                                color="secondary"
                                onClick={handleSelect.bind(instance)}
                                fullWidth
                            >
                                SELECT
                            </Button>
                        </Grid>
                    </Grid>
                );
            } else if (instance.state.uploadStatus == -1 || instance.state.uploadStatus == 100) {
                return (
                    <Grid container spacing={8} justify="center">
                        <Grid item xs={3}>
                            <Button
                                variant="contained"
                                className={classes.select}
                                color="secondary"
                                onClick={instance.closeUpdater}
                                fullWidth
                            >
                                Close
                            </Button>
                        </Grid>
                    </Grid>
                );
            } else {
                return <br />;
            }
        }

        function getProgress(instance) {
            if (instance.state.showUpdater) {
                return (
                    <React.Fragment>
                        <Grid container spacing={1}>
                            <Grid item xs={3}>
                                <img src={path.join(__dirname, './static/img/computer.png')} width="128" height="72" style={{ marginTop: '15px' }}/>
                            </Grid>
                            <Grid item xs={6}>
                                <br/>
                                <LinearProgress variant="determinate" color="secondary" style={{ height: '30px', marginTop: '5px' }} value={instance.state.uploadStatus} />
                            </Grid>
                            <Grid item xs={3}>
                                <img src={path.join(__dirname, './static/img/mill.png')} width="90" height="90" />
                            </Grid>
                        </Grid>
                    </React.Fragment>
                );
            }

            return "";
        }

        function getSelection(instance) {
            if (!instance.state.showUpdater) {
                return (
                    <React.Fragment>
                        <Typography>Select firmware version to download.</Typography>
                        <select size="5" onChange={handleSelectFirmware.bind(instance)} className={classes.firmwareList}>
                            {
                                instance.state.availableFirmware.map((firmware, index) => {
                                    return (<option key={index}>{firmware.description}</option>);
                                })
                            }
                        </select>
                        <br />
                    </React.Fragment>
                );
            }

            return "";
        }

        return (
            <React.Fragment>
                <Button
                    onClick={() => { this.setState({ showUpdates: true }); }}
                    variant="contained"
                    color="secondary"
                    size="small"
                    fullWidth
                >
                    Update Firmware
                </Button>

                <Dialog
                    open={this.state.showUpdates}
                    aria-labelledby="form-dialog-title"
                    maxWidth="sm"
                    PaperProps={{ style: { overflow: 'hidden' } }}
                    fullWidth
                >
                    <DialogTitle>
                        <center>
                            { this.state.showUpdater ? "Uploading Firmware" : "Firmware Selection" }
                        </center>    
                    </DialogTitle>
                    <DialogContent>
                        { getProgress(this) }
                        { getSelection(this) }
                    </DialogContent>
                    <DialogActions>
                        { getButtons(this) }
                    </DialogActions>
                </Dialog>
            </React.Fragment>
        );
    }
}

FirmwareUpdater.propTypes = {
    classes: PropTypes.object.isRequired,
    refreshFirmwareVersion: PropTypes.func
};

export default withStyles(styles)(FirmwareUpdater);
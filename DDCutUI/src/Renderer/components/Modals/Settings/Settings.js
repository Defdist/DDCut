import React from "react";
import PropTypes from "prop-types";
import {
    Button, Dialog, DialogContent, Typography,
    DialogTitle, Fab, Radio, RadioGroup, FormControl, FormLabel,
    FormControlLabel, Checkbox, TextField
} from "@material-ui/core";
import path from "path";
import { withStyles } from "@material-ui/core/styles";
import { ipcRenderer } from "electron";

const styles = theme => ({
    settingsButton: {
        paddingTop: 0,
        paddingBottom: 0,
        paddingLeft: theme.spacing.unit,
        paddingRight: theme.spacing.unit,
        backgroundColor: "transparent"
    },
    settingsCog: {
        width: '25px',
        height: '25px',
        marginRight: theme.spacing.unit,
        padding: 0,
        marginTop: 0
    },
    settingsText: {
        width: '62px',
        height: '28px',
        objectFit: 'contain',
        padding: 0,
        margin: 0
    },
    timeoutText: {
        width: 100,
        height: 30,
        marginLeft: theme.spacing.unit * 2,
        marginRight: theme.spacing.unit * 2,
        marginTop: theme.spacing.unit
    },
    cancel: {
        marginRight: theme.spacing.unit
    },
    save: {
        marginLeft: theme.spacing.unit
    },
    radio: {
        marginLeft: theme.spacing.unit,
        marginTop: 0,
        marginBottom: 0
    },
    radioGroup: {
        width: "100%",
        backgroundColor: "black",
        borderStyle: "solid",
        borderColor: "white",
        borderWidth: "2px",
        borderRadius: "2px"
    },
    feedRatePercentage: {
        marginLeft: theme.spacing.unit,
        padding: theme.spacing.unit,
        backgroundColor: "black"
    }
});

function Settings(props) {
    const { classes, disabled } = props;
    const [open, setOpen] = React.useState(false);
    const [pause, setPause] = React.useState(false);
    const [timeout, setTimeout] = React.useState(0);
    const [enableSlider, setEnableSlider] = React.useState(false);
    const [maxFeedRate, setMaxFeedRate] = React.useState(0);
    const [ddVersion, setDDVersion] = React.useState("");
    const [grblVersion, setGrblVersion] = React.useState("");

    function handleClickOpen() {
		if (!disabled) {
			setOpen(true);
			var settings = ipcRenderer.sendSync("Settings::GetSettings");
			setPause(settings.pauseAfterGCode);
			setTimeout(settings.timeout);
			setEnableSlider(settings.enable_slider);
			setMaxFeedRate(settings.maxFeedRate);

			var firmware = ipcRenderer.sendSync("Firmware::GetFirmwareVersion");
			setDDVersion(firmware.ddVersion);
			setGrblVersion(firmware.grblVersion);
		}
    }

    function handleClose() {
        setOpen(false);
    }

    function handleSave() {
        ipcRenderer.send("Settings::UpdateSettings", pause, timeout, enableSlider, maxFeedRate);
        setOpen(false);
    }

    function getVersionDisplay() {
        if (ddVersion == "") {
            return "Not Connected";
        }

        return "DD: " + ddVersion + " GRBL: " + grblVersion;
    }

    return (
        <React.Fragment>
            <Fab
                variant="extended"
                aria-label="Settings"
				disabled={disabled}
                onClick={handleClickOpen}
                className={classes.settingsButton}
                size="small"
				id="settings"
            >
                <img src={path.join(__dirname, '../../../static/img/settings-cog.png')} className={classes.settingsCog} /> 
                <img src={path.join(__dirname, '../../../static/img/settings.png')} className={classes.settingsText}/> 
            </Fab>
            
            <Dialog
                open={open}
                onClose={handleClose}
                aria-labelledby="form-dialog-title"
                maxWidth="sm"
                PaperProps={{
                    className: classes.paper
                }}
            >
                <DialogTitle id="form-dialog-title"><center>Settings</center></DialogTitle>
                <DialogContent>
                    {/* Pause After GCode */}
                    <FormControlLabel
                        control={
                            <Checkbox checked={pause} onChange={e => setPause(e.currentTarget.checked)} />
                        }
                        label="Pause after GCode"
                    /><br/>

                    {/* Default Timeout */}
                    <FormControlLabel
                        control={
                            <TextField
                                margin="normal"
                                variant="outlined"
                                className={classes.timeoutText}
                                type="number"
                                defaultValue={timeout}
                                onChange={e => setTimeout(e.currentTarget.valueAsNumber)}
                            />
                        }
                        label="Default Timeout in Seconds"
                    /><br /><br />

                    {/* Firmware */}
                    <Typography>Firmware Version: <b>{getVersionDisplay()}</b></Typography>
                    <Button
                        variant="contained"
                        color="secondary"
                        size="small"
                        fullWidth
                    >
                        Update Firmware
                    </Button>
                    <br /><br />

                    {/* Feedrate */}
                    <FormControlLabel
                        control={
                            <Checkbox checked={enableSlider} onChange={e => setEnableSlider(e.currentTarget.checked)} />
                        }
                        label="Enable Feedrate Percentage"
                    />

                    <FormControl
                        component="fieldset"
                        className={classes.radioGroup}
                    >
                        <FormLabel
                            component="legend"
                            className={classes.feedRatePercentage}
                        >
                            FeedRate Percentage
                        </FormLabel>
                        <RadioGroup>
                            <FormControlLabel
                                control={
                                    <Radio checked={maxFeedRate == 100} onChange={e => setMaxFeedRate(100)} />
                                }
                                label="30% - 100%"
                                className={classes.radio}
                            />
                            <FormControlLabel
                                control={
                                    <Radio checked={maxFeedRate == 300} onChange={e => setMaxFeedRate(300)} />
                                }
                                label="30% - 300%"
                                className={classes.radio}
                            />
                        </RadioGroup>
                    </FormControl>


                    <br /><br />
                    <div
                        style={{ textAlign: "right", width: "100%" }}
                    >
                        <Button
                            variant="contained"
                            className={classes.cancel}
                            onClick={handleClose}
                        >
                            CANCEL
                        </Button>
                        <Button
                            variant="contained"
                            className={classes.save}
                            color="secondary"
                            onClick={handleSave}
                        >
                            SAVE CHANGES
                        </Button>
                    </div>
                </DialogContent>
            </Dialog>
        </React.Fragment>
    );
}

Settings.propTypes = {
    classes: PropTypes.object.isRequired,
    disabled: PropTypes.bool.isRequired
};

export default withStyles(styles)(Settings);

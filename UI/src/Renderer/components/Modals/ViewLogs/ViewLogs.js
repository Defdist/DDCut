import React from 'react';
import PropTypes from 'prop-types';
import withStyles from '@material-ui/core/styles/withStyles';
import { ipcRenderer, shell } from 'electron';
import {
    Dialog, Typography, Button, Grid, DialogTitle, DialogContent, DialogActions, Select
} from '@material-ui/core';

const styles = theme => ({
    cancel: {
        marginTop: -theme.spacing.unit,
        marginBottom: theme.spacing.unit
    },
    open: {
        marginTop: -theme.spacing.unit,
        marginBottom: theme.spacing.unit
    },
    logOutput: {
        width: "calc(100% - 6px)"
    },
});

function ViewLogs(props) {
    const { classes, open, onClose } = props;
    const [logText, setLogText] = React.useState("");
    const [logFile, setLogFile] = React.useState("");

    function handleOpen(event) {
        var path = logFile;
        if (process.platform == 'darwin') {
            path = 'file://' + logFile;
        }

        shell.openExternal(path);
        onClose(event);
    }

    function handleClose(event) {
        onClose(event);
    }

    function getLogText() {
        if (logFile.length == 0) {
            setLogFile(ipcRenderer.sendSync("Logs::GetLogFile"));
        } else if (logText.length == 0) {
            ipcRenderer.removeAllListeners("File::FileOpened");
            ipcRenderer.on("File::FileOpened", function (event, data) {
                if (data != null && data.length > 0) {
                    setLogText(data + "\nClick Open/Save to see the full log.");
                } else {
                    setLogText("No logs found.");
                }
            });
            ipcRenderer.send('File::ReadFile', logFile);
        } else {
            return logText;
        }

        return "Loading";
    }

    return (
        <Dialog
            open={open}
            aria-labelledby="form-dialog-title"
            maxWidth="sm"
            fullWidth
            PaperProps={{style: {overflow:'hidden'}}}
        >
            <DialogTitle>
                <center>
                    View Logs
                </center>    
            </DialogTitle>
            <DialogContent>
                <br />
                <textarea type="text" disabled={true} overflow="auto" rows="12" cols="78" value={getLogText()} className={classes.logOutput} />
                <br />
            </DialogContent>
            <DialogActions>
                <Grid container spacing={8} justify="center">
                    <Grid item xs={3}>
                        <Button
                            variant="contained"
                            className={classes.cancel}
                            onClick={handleClose}
                            fullWidth
                        >
                            CLOSE
                        </Button>
                    </Grid>
                    <Grid item xs={3}>
                        <Button
                            variant="contained"
                            className={classes.open}
                            color="secondary"
                            onClick={handleOpen}
                            fullWidth
                        >
                            OPEN/SAVE
                        </Button>
                    </Grid>
                </Grid>
            </DialogActions>
        </Dialog>
    );
}

ViewLogs.propTypes = {
    classes: PropTypes.object.isRequired,
    open: PropTypes.bool.isRequired,
    onClose: PropTypes.func,
};

export default withStyles(styles)(ViewLogs);
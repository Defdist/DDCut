import React from 'react';
import PropTypes from 'prop-types';
import withStyles from '@material-ui/core/styles/withStyles';
import { ipcRenderer } from 'electron';
import {
    Dialog, Typography, Button, Grid, DialogTitle, DialogContent, DialogActions
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
    ghostList: {
        width: "100%"
    },
    switch: {
        marginLeft: -2 * theme.spacing.unit
    }
});

function Alert(props) {
    const { classes, open, yesNo, message, onOk, onCancel } = props;

    function getActions() {
        if (yesNo == true) {
            return (
                <DialogActions>
                    <Button
                        variant="contained"
                        className={classes.select}
                        color="secondary"
                        onClick={onOk}
                    >
                        YES
                    </Button>
                    <Button
                        variant="contained"
                        className={classes.select}
                        color="secondary"
                        onClick={onCancel}
                    >
                        NO
                    </Button>
                </DialogActions>
            );
        } else {
            return (
                <DialogActions>
                    <Button
                        variant="contained"
                        className={classes.select}
                        color="secondary"
                        onClick={onOk}
                    >
                        OK
                    </Button>
                </DialogActions>
            );
        }
    }

    return (
        <React.Fragment>
            <Dialog
                open={open}
                aria-labelledby="form-dialog-title"
                maxWidth="xs"
                fullWidth
            >
                <DialogContent>
                    <Typography>{message}</Typography>
                    <br />
                </DialogContent>
                {getActions()}
            </Dialog>
        </React.Fragment>
    );
}

Alert.propTypes = {
    classes: PropTypes.object.isRequired,
    open: PropTypes.bool.isRequired,
    yesNo: PropTypes.bool.isRequired,
    message: PropTypes.string.isRequired,
    onOk: PropTypes.func.isRequired,
    onCancel: PropTypes.func.isRequired
};

export default withStyles(styles)(Alert);
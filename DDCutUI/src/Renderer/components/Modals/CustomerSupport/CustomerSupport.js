import React from 'react';
import PropTypes from 'prop-types';
import withStyles from '@material-ui/core/styles/withStyles';
import { ipcRenderer } from 'electron';
import {
    Dialog, Typography, Button, Grid, DialogTitle, DialogContent, DialogActions, Select,
    FormControl, FormLabel, FormControlLabel, Checkbox, TextField
} from '@material-ui/core';

const styles = theme => ({
    cancel: {
        marginTop: -theme.spacing.unit,
        marginBottom: theme.spacing.unit
    },
    send: {
        marginTop: -theme.spacing.unit,
        marginBottom: theme.spacing.unit
    },
    emailText: {
        width: '100%',
        height: 30,
        marginTop: 0
    },
});

function CustomerSupport(props) {
    const { classes, open, onClose } = props;
    const [errors, setErrors] = React.useState(new Array());
    const [email, setEmail] = React.useState("");
    const [description, setDescription] = React.useState("");
    const [includeLogs, setIncludeLogs] = React.useState(false);

    function handleClose(event) {
        setErrors(new Array());
        setEmail("");
        setDescription("");
        setIncludeLogs(false);
        onClose(event);
    }

    function handleSend(event) {
        const error = ipcRenderer.sendSync("Support::SendRequest", email, description, includeLogs);
        if (error == null) {
            handleClose(null);
        } else {
            console.log(error);
            var errorsArray = new Array();

            if (error.hasOwnProperty("name")) {
                errorsArray.push("NAME: " + error.name);
            }

            if (error.hasOwnProperty("email")) {
                errorsArray.push("EMAIL: " + error.email);
            }

            if (error.hasOwnProperty("description")) {
                errorsArray.push("DESCRIPTION: " + error.description);
            }

            setErrors(errorsArray);
        }
    }

    console.log(errors);

    return (
        <Dialog
            open={open}
            aria-labelledby="form-dialog-title"
            style={{ overflow: 'none' }}
            maxWidth="sm"
            fullWidth
        >
            <DialogTitle>
                <center>
                    Customer Support Request
                </center>
            </DialogTitle>
            <DialogContent style={{ overflowX: 'hidden' }}>

                {
                    errors.map((error, index) => {
                        return (
                            <Typography color="error">{error}</Typography>
                        );
                    })
                }

                {/* Email */}
                <br/>
                <Grid container spacing={8} justify="center">
                    <Grid item xs={3}>
                        <Typography inline style={{ lineHeight: '30px' }}> Your e-mail address:</Typography>
                    </Grid>
                    <Grid item xs={9}>
                        <TextField
                            margin="normal"
                            variant="outlined"
                            className={classes.emailText}
                            onChange={e => setEmail(e.currentTarget.value)}
                        />
                    </Grid>
                </Grid>
                <TextField
                    margin="normal"
                    variant="outlined"
                    placeholder="Please enter a description of your problem."
                    rows={4}
                    fullWidth
                    multiline={true}
                    onChange={e => setDescription(e.currentTarget.value)}
                />

                <br />
                <FormControlLabel
                    control={
                        <Checkbox
                            checked={includeLogs}
                            onChange={e => { setIncludeLogs(e.currentTarget.checked) }}
                        />
                    }
                    label="Include logs and data that might help us solve your problem."
                />
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
                            CANCEL
                        </Button>
                    </Grid>
                    <Grid item xs={3}>
                        <Button
                            variant="contained"
                            className={classes.send}
                            color="secondary"
                            onClick={handleSend}
                            fullWidth
                        >
                            SEND REPORT
                        </Button>
                    </Grid>
                </Grid>
            </DialogActions>
        </Dialog>
    );
}

CustomerSupport.propTypes = {
    classes: PropTypes.object.isRequired,
    open: PropTypes.bool.isRequired,
    onClose: PropTypes.func,
};

export default withStyles(styles)(CustomerSupport);
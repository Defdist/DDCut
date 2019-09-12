import React from 'react';
import PropTypes from 'prop-types';
import withStyles from '@material-ui/core/styles/withStyles';
import { ipcRenderer } from 'electron';
import {
    Dialog, Typography, Button, Grid, DialogTitle, DialogContent, DialogActions, Select,
    DialogContentText, FormControlLabel, Checkbox, TextField
} from '@material-ui/core';

const styles = theme => ({
    cancel: {
        marginTop: -theme.spacing.unit,
        marginBottom: theme.spacing.unit,
        marginRight: '4px'
    },
    send: {
        marginTop: -theme.spacing.unit,
        marginBottom: theme.spacing.unit,
        marginLeft: '4px'
    },
    emailText: {
        width: '100%',
        height: 30,
        marginTop: 0
    },
});

function CustomerSupport(props) {
    const { classes, open, onClose } = props;
    const [ submitted, setSubmitted ] = React.useState(false);
    const [errors, setErrors] = React.useState(new Array());
    const [email, setEmail] = React.useState("");
    const [description, setDescription] = React.useState("");
    const [includeLogs, setIncludeLogs] = React.useState(false);

    function handleClose(event) {
        setSubmitted(false);
        setErrors(new Array());
        setEmail("");
        setDescription("");
        setIncludeLogs(false);
        onClose(event);
    }

    function handleSend(event) {
        const error = ipcRenderer.sendSync("Support::SendRequest", email, description, includeLogs);
        if (error == null) {
            setSubmitted(true);
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

            if (errorsArray.length == 0) {
                errorsArray.push("Unable to send. Server may be down.");
            }

            setErrors(errorsArray);
        }
    }

    return (
        <Dialog
            open={open}
            aria-labelledby="form-dialog-title"
            maxWidth="sm"
            fullWidth
        >

            <Dialog
              open={submitted}
              onClose={handleClose}
              aria-describedby="alert-dialog-description"
            >
                <DialogContent>
                    <DialogContentText id="alert-dialog-description">
                        Your support request was sent successfully.
                    </DialogContentText>
                </DialogContent>
                <DialogActions>
                    <center>
                        <Button onClick={handleClose} color="secondary" autoFocus>
                            OK
                        </Button>
                    </center>
                </DialogActions>
            </Dialog>

            <DialogTitle>
                <center>
                    Bug Report
                </center>
            </DialogTitle>
            <DialogContent style={{ overflowX: 'hidden' }}>

                {
                    errors.map((error, index) => {
                        return (
                            <Typography variant="body1" color="error">{error}</Typography>
                        );
                    })
                }

                {/* Email */}
                <br/>
                <Grid container spacing={0} justify="center">
                    <Grid item xs={3}>
                        <Typography variant="body1" display="inline" style={{ lineHeight: '30px' }}>Your e-mail address:</Typography>
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
                <Grid container spacing={0} justify="center">
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
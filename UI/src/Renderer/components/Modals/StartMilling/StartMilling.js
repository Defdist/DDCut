import React from 'react';
import PropTypes from 'prop-types';
import withStyles from '@material-ui/core/styles/withStyles';
import {
    Dialog, Typography, Button, Grid, DialogTitle, DialogContent, DialogActions, Select
} from '@material-ui/core';

const styles = theme => ({
    cancel: {
        marginTop: -theme.spacing.unit,
        marginBottom: theme.spacing.unit
    },
    select: {
        marginTop: -theme.spacing.unit,
        marginBottom: theme.spacing.unit
    }
});

function StartMilling(props) {
    const { classes, open, onClose } = props;

    return (
        <Dialog
            open={open}
            aria-labelledby="form-dialog-title"
            maxWidth="xs"
            fullWidth
            PaperProps={{style: {overflow:'hidden'}}}
        >
            <DialogTitle>
                <center>
                    START MOVING
                </center>
            </DialogTitle>
            <DialogContent>
                <Typography align="center">The machine is about to start moving. Are you sure you<br />want to continue?</Typography>
            </DialogContent>
            <DialogActions>
                <Grid container spacing={8} justify="center">
                    <Grid item xs={3}>
                        <Button
                            variant="contained"
                            className={classes.cancel}
                            onClick={(event) => { onClose(false) }}
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
                            onClick={(event) => { onClose(true) }}
                            fullWidth
                        >
                            START
                        </Button>
                    </Grid>
                </Grid>
            </DialogActions>
        </Dialog>
    );
}

StartMilling.propTypes = {
    classes: PropTypes.object.isRequired,
    open: PropTypes.bool.isRequired,
    onClose: PropTypes.func,
};

export default withStyles(styles)(StartMilling);

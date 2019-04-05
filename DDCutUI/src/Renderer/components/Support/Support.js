import React from "react";
import PropTypes from "prop-types";
import {
    Button, Dialog, DialogActions, DialogContent,
    DialogContentText, DialogTitle, Fab
} from "@material-ui/core";
import path from "path";
import { withStyles } from "@material-ui/core/styles";

const styles = theme => ({
    supportButton: {
        paddingTop: 0,
        paddingBottom: 0,
        paddingLeft: theme.spacing.unit,
        paddingRight: theme.spacing.unit,
        backgroundColor: "transparent"
    },
    supportImg: {
        width: '100px',
        height: '25px',
        objectFit: 'contain',
        padding: 0,
        margin: 0
    }
});

function Support(props) {
    const { classes } = props;
    const [open, setOpen] = React.useState(false);

    function handleClickOpen() {
        setOpen(true);
    }

    function handleClose() {
        setOpen(false);
    }

    return (
        <React.Fragment>
            <Fab
                variant="extended"
                aria-label="Support"
                onClick={handleClickOpen}
                className={classes.supportButton}
                size="small"
            >
                <img src={path.join(__dirname, '../../static/img/support_button.png')} className={classes.supportImg} /> 
            </Fab>

            <Dialog
                open={open}
                onClose={handleClose}
                aria-labelledby="form-dialog-title"
            >
                <DialogTitle id="form-dialog-title">Support</DialogTitle>
                <DialogContent>
                    <DialogContentText>
                        To subscribe to this website, please enter your email address here.
                        We will send updates occasionally.
                    </DialogContentText>

                </DialogContent>
                <DialogActions>
                    <Button onClick={handleClose} color="primary">
                        Cancel
                    </Button>
                    <Button onClick={handleClose} color="primary">
                        Subscribe
                    </Button>
                </DialogActions>
            </Dialog>
        </React.Fragment>
    );
}

Support.propTypes = {
    classes: PropTypes.object.isRequired
};

export default withStyles(styles)(Support);

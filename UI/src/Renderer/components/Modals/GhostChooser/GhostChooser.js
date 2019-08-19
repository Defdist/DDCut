import React from 'react';
import PropTypes from 'prop-types';
import withStyles from '@material-ui/core/styles/withStyles';
import { ipcRenderer } from 'electron';
import {
    Dialog, Typography, Button, Grid, DialogTitle, DialogContent, DialogActions
} from '@material-ui/core';
import app from 'app';

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
        marginLeft: -2 * theme.spacing.unit,
        color: 'white'
    }
});

function GhostChooser(props) {
    const { classes, disabled } = props;
    const [open, setOpen] = React.useState(false);
    const [availableGhosts, setAvailableGhosts] = React.useState(null);
    const [selectedGhost, setSelectedGhost] = React.useState(-1);
    
    function handleSelect(event) {
        if (selectedGhost >= 0) {
            ipcRenderer.send("Ghost::ChooseGhost", availableGhosts[selectedGhost].path, availableGhosts[selectedGhost].serial_number);
        }

        setOpen(false);
    }

    function handleClickOpen(event) {
        const available = ipcRenderer.sendSync("Ghost::GetAvailableGhosts");
        console.log(available);
        setAvailableGhosts(available);

        for (var i = 0; i < available.length; i++) {
            if (available[i].selected == true) {
                setSelectedGhost(i);
            }
        }

        setOpen(true);
    }

    function handleClose(event) {
        setOpen(false);
    }

    function handleSelectGhost(event) {
        setSelectedGhost(event.target.selectedIndex);
    }

    function getGhostOptions() {
        if (availableGhosts != null) {
            const options = availableGhosts.map((ghost, index) => {
                return (<option key={index}> SN: {ghost.serial_number} PATH: {ghost.path}</option>);
            });

            return options;
        }

        return null;
    }

    function getSwitchButton() {
        if (!disabled) {
            return (
                <Button color="secondary" onClick={handleClickOpen} className={classes.switch}>(<span style={{ textDecoration: 'underline' }}>Select</span>)</Button>
			);
		}

		return null;
	}

    return (
        <React.Fragment>
            {getSwitchButton()}

            <Dialog
                open={open}
                aria-labelledby="form-dialog-title"
                maxWidth="sm"
                fullWidth
                PaperProps={{style: {overflow:'hidden'}}}
            >
                <DialogTitle>
                    <center>
                        {app.chooser.title}
                    </center>
                </DialogTitle>
                <DialogContent>
                    <Typography>{app.chooser.select}</Typography>
                    <select size="5" onChange={handleSelectGhost} className={classes.ghostList} value={selectedGhost}>
                        {getGhostOptions()}
                    </select>
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
                                className={classes.select}
                                color="secondary"
                                onClick={handleSelect}
                                fullWidth
                            >
                                SELECT
                            </Button>
                        </Grid>
                    </Grid>
                </DialogActions>
            </Dialog>
        </React.Fragment>
    );
}

GhostChooser.propTypes = {
    classes: PropTypes.object.isRequired,
	disabled: PropTypes.bool.isRequired
};

export default withStyles(styles)(GhostChooser);
import React from 'react';
import PropTypes from 'prop-types';
import withStyles from '@material-ui/core/styles/withStyles';
import { ipcRenderer } from 'electron';
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
    },
    jobList: {
        width: "100%"
    },
    jobText: {
        width: "calc(100% - 6px)"
    },
});

function JobSelection(props) {
    const { classes, open, onClose, jobs } = props;
    const [selectedJob, setSelectedJob] = React.useState(0);
    

    function handleSelect(event) {
        ipcRenderer.send("Jobs::SelectJob", selectedJob);
        onClose(event);
    }

    function handleClose(event) {
        onClose(event);
    }

    function handleSelectJob(event) {
        setSelectedJob(event.target.selectedIndex);
    }

    function getJobText() {
        if (selectedJob >= 0 && jobs.length > selectedJob) {
            return jobs[selectedJob].prompt;
        }

        return "";
    }

    return (
        <Dialog
            open={open}
            aria-labelledby="form-dialog-title"
            maxWidth="sm"
            PaperProps={{style: {overflow:'hidden'}}}
            fullWidth
        >
            <DialogTitle>
                <center>
                    Job Selection
                </center>    
            </DialogTitle>
            <DialogContent>
                <Typography>Select job to continue.</Typography>
                <select size="5" onChange={handleSelectJob} className={classes.jobList}>
                    {
                        jobs.map((job, index) => {
                            return (<option key={index}>{job.title}</option>);
                        })
                    }
                </select>
                <br /><br />
                <textarea type="text" disabled={true} rows="6" cols="78" value={getJobText()} className={classes.jobText} />
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
    );
}

JobSelection.propTypes = {
    classes: PropTypes.object.isRequired,
    open: PropTypes.bool.isRequired,
    onClose: PropTypes.func,
    jobs: PropTypes.array.isRequired,
};

export default withStyles(styles)(JobSelection);
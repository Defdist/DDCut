import React from 'react';
import PropTypes from 'prop-types';
import { ipcRenderer } from 'electron';
import { withStyles } from '@material-ui/core/styles';
import { Grid, Button, Dialog, Typography } from '@material-ui/core';

const styles = theme => ({
    root: {
        width: '100%',
        height: '100%',
    },
    gcodes: {
        width: '100%',
        height: 'calc(100% - 50px)',
        overflow: 'auto',
        backgroundColor: 'black',
        position: 'relative',
        border: '#FFFFFF 1px solid',
        color: '#FFFFFF'
    }
});

class ImageRaw extends React.Component {
    constructor() {
        super();
        this.state = {
            imageSelected: true,
            zoom: false,
            readWrites: []
        };

        this.gcodeEnd = null;
        this.updateReadWrites = this.updateReadWrites.bind(this);
    }

    shouldComponentUpdate(nextProps, nextState) {
        if (this.props.selectedStep != nextProps.selectedStep) {
            return true;
        } else if (this.state.imageSelected != nextState.imageSelected) {
            return true;
        } else if (this.state.zoom != nextState.zoom) {
            return true;
        } else if (this.props.millingInProgress != nextProps.millingInProgress) {
            return true;
        } else if (this.state.readWrites != nextState.readWrites) {
            return true;
        }

        return false;
    }

    componentDidUpdate(prevProps) {
        if (this.props.selectedStep !== prevProps.selectedStep) {
            this.setState({
                imageSelected: true,
                zoom: false,
                readWrites: []
            });
        }
    }

    updateReadWrites(event, newLines) {
        if (newLines.length > 0) {
            this.setState({
                readWrites: [...this.state.readWrites, ...newLines]
            });
        }
    }

    render() {
        const { classes, selectedStep, millingInProgress } = this.props;

        ipcRenderer.removeAllListeners("Jobs::ReadWrites");
        ipcRenderer.on("Jobs::ReadWrites", this.updateReadWrites);

        function getGCodeDisplay(milling, readWrites) {
            if (milling) {
                return readWrites.map((readWrite, index) => {
                    return (
                        <Typography variant="body1" color="textPrimary" key={index} align="left" style={{ marginLeft: '10px' }}>
                            {readWrite.TYPE} : {readWrite.VALUE}
                        </Typography>
                    )
                });
            } else {
                var gcodes = [];
                if (selectedStep.GCode != null) {
                    gcodes = selectedStep.GCode;
                }

                return gcodes.map((gcode, index) => {
                    return (
                        <Typography variant="body1" color="textPrimary" key={index} align="left" style={{ marginLeft: '10px' }}>
                            {gcode}
                        </Typography>
                    )
                });
            }
        }

        function getDisplay(component) {
            if (component.state.imageSelected == true) {
                if (component.state.zoom == true) {
                    return (
                        <Dialog
                            open={component.state.zoom}
                            aria-labelledby="form-dialog-title"
                            maxWidth="md"
                            onClose={() => {
                                component.setState({ zoom: false });
                            }}
                            fullWidth
                        >
                            <Button onClick={() => {
                                component.setState({ zoom: false });
                            }}>
                                <img style={{ width: 'auto', height: 'auto' }} src={'data:image/jpeg;base64,' + selectedStep.Image} />
                            </Button>
                        </Dialog>
                    );
                } else {
                    return (
                        <Button onClick={() => {
                            component.setState({ zoom: true });
                        }}>
                            <img style={{ width: '100%', height: 'auto' }} src={'data:image/jpeg;base64,' + selectedStep.Image} />
                        </Button>
                    );
                }
            } else {
                return (
                    <div className={classes.gcodes} >
                        {getGCodeDisplay(millingInProgress, component.state.readWrites)}
                        <div style={{ float: "left", clear: "both" }}
                            ref={(el) => { component.gcodeEnd = el; }}>
                        </div>
                    </div>
                );
            }
        }

        function onClickImage(event) {
            this.setState({
                imageSelected: true
            });
        }

        function onClickRaw(event) {
            if (selectedStep.GCode != null) {
                this.setState({
                    imageSelected: false
                });
            }
        }

        function scrollToBottom(component) {
            if (millingInProgress && component.gcodeEnd != null && !component.state.imageSelected) {
                component.gcodeEnd.scrollIntoView({ behavior: "auto", block: 'center' });
            }
        }

        return (
            <div className={classes.root}>
                <Grid container spacing={0}>
                    <Grid item xs={3} />
                    <Grid item xs={3}>
                        <Button
                            fullWidth
                            variant="contained"
                            color={this.state.imageSelected === true ? "secondary" : "primary"}
                            size="small"
                            onClick={onClickImage.bind(this)}
                            style={{ borderRadius: '0px', padding: '0px' }}
                        >
                            IMAGE
                        </Button>
                    </Grid>
                    <Grid item xs={3}>

                        {/*disabled={selectedStep.GCode == null ? true : false}*/}
                        <Button
                            fullWidth
                            variant="contained"
                            color={this.state.imageSelected === true ? "primary" : "secondary"}
                            size="small"
                            onClick={onClickRaw.bind(this)}
                            style={{ borderRadius: '0px', padding: '0px' }}
                        >
                            RAW
                        </Button>
                    </Grid>
                    <Grid item xs={3} />
                </Grid>
                <br />
                {getDisplay(this)}
                {scrollToBottom(this)}
            </div>
        );
    }
};

ImageRaw.propTypes = {
    classes: PropTypes.object.isRequired,
    selectedStep: PropTypes.object.isRequired,
    millingInProgress: PropTypes.bool.isRequired
};

export default withStyles(styles)(ImageRaw);
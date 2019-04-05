import React from 'react';
import PropTypes from 'prop-types';
import { withStyles } from '@material-ui/core/styles';
import { Grid, Button, Typography } from '@material-ui/core';

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
        border: '#FFFFFF 1px solid' 
    }
});

class ImageRaw extends React.Component {
    constructor() {
        super();
        this.state = {
            imageSelected: true
        };
    }

    shouldComponentUpdate(nextProps, nextState) {
        if (this.props.selectedStep != nextProps.selectedStep) {
            return true;
        } else if (this.state.imageSelected != nextState.imageSelected) {
            return true;
        }

        return false;
    }

    componentDidUpdate(prevProps) {
        if (this.props.selectedStep !== prevProps.selectedStep) {
            if (this.state.imageSelected != true) {
                this.setState({ imageSelected: true });
            }
        }
    }

    render() {
        const { classes, selectedStep } = this.props;

        function getDisplay(component) {
            if (component.state.imageSelected == true) {
                return (
                    <img style={{ width: '100%', height: 'auto' }} src={'data:image/jpeg;base64,' + selectedStep.Image} />
                );
            } else {
                var gcodes = [];
                if (selectedStep.GCode != null) {
                    gcodes = selectedStep.GCode.split('<br/>');//selectedStep.GCode.replace(/<br\/>/g, "\r\n");
                }

                return (
                    <div className={classes.gcodes} >
                        {gcodes.map((gcode, index) => {
                            return (
                                <Typography key={index} align="left" style={{ marginLeft: '10px' }}>
                                    {gcode}
                                </Typography>
                            )
                        })}
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
            </div>
        );
    }
};

ImageRaw.propTypes = {
    classes: PropTypes.object.isRequired,
    selectedStep: PropTypes.object.isRequired
};

export default withStyles(styles)(ImageRaw);
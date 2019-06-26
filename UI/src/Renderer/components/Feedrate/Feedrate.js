import React from 'react';
import PropTypes from 'prop-types';
import { ipcRenderer } from 'electron';
import { withStyles, makeStyles } from '@material-ui/core/styles';
import { Grid, Button, Dialog, Typography, Paper } from '@material-ui/core';
import Slider from '@material-ui/lab/Slider';
import { fade } from '@material-ui/core/styles/colorManipulator';

const useStyles = makeStyles({
  root: {
    width: 'calc(100%-48px)',
    padding: 24,
  },
});

const StyledSlider = withStyles({
  thumb: {
    height: 24,
    width: 24,
    backgroundColor: '#fff',
    border: '2px solid #de235b',
    '&$focused, &:hover': {
      boxShadow: `0px 0px 0px ${8}px ${fade('#de235b', 0.16)}`,
    },
    '&$activated': {
      boxShadow: `0px 0px 0px ${8 * 1.5}px ${fade('#de235b', 0.16)}`,
    },
    '&$jumped': {
      boxShadow: `0px 0px 0px ${8 * 1.5}px ${fade('#de235b', 0.16)}`,
    },
  },
  track: {
    backgroundColor: '#de235b',
    height: 8,
  },
  trackAfter: {
    backgroundColor: '#d0d7dc',
  },
  focused: {},
  activated: {},
  jumped: {},
})(Slider);

class Feedrate extends React.Component {
    /*const [feedRate, setFeedRate] = React.useState(ipcRenderer.sendSync("Settings::GetFeedRate"));
    const [settings] = React.useState(ipcRenderer.sendSync("Settings::GetSettings"));*/
    
    constructor() {
        super();
        this.state = {
            feedRate: ipcRenderer.sendSync("Settings::GetFeedRate"),
            settings: ipcRenderer.sendSync("Settings::GetSettings"),
        };
        //this.classes = useStyles();
    }
    
    componentDidUpdate(prevProps) {
        if (this.props.selectedStep !== prevProps.selectedStep) {
            this.setState({
                feedRate: ipcRenderer.sendSync("Settings::GetFeedRate"),
                settings: ipcRenderer.sendSync("Settings::GetSettings"),
            });
        }
    }

    render() {

        if (this.state.settings == null || this.state.settings.enable_slider != true) {
            return "";
        }

        const handleChange = (event, newValue) => {
            const newFeedRate = Math.round(newValue * (maxFeedRate / 100));
            ipcRenderer.send("Settings::SetFeedRate", newFeedRate);
            this.setState({
                feedRate: newFeedRate
            });
        };

        const maxFeedRate = this.state.settings.maxFeedRate;

        /*var sliderValue = value;
        if (value == -1) {
            sliderValue = (10000/maxFeedRate);
        }*/

        return (
            <React.Fragment>
                <Typography variant="h5" color="textPrimary">{this.state.feedRate}%</Typography>
                <Paper style={{width: 'calc(100%-48px)', padding: 24}}>
                    <StyledSlider value={this.state.feedRate / (maxFeedRate / 100)} aria-labelledby="label" onChange={handleChange} />
                </Paper>
            </React.Fragment>
        );
    }
}

Feedrate.propTypes = {
    //classes: PropTypes.object.isRequired,
    selectedStep: PropTypes.number.isRequired
};

export default Feedrate;
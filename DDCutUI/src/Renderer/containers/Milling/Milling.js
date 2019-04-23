import React from 'react';
import PropTypes from 'prop-types';
import { ipcRenderer } from 'electron';
import withStyles from '@material-ui/core/styles/withStyles';
import StepList from '../../components/StepList';
import ImageRaw from '../../components/ImageRaw';
import StartMilling from '../../components/Modals/StartMilling';
import path from "path";
import { Button, IconButton, Typography, LinearProgress } from '@material-ui/core';
import { Redirect } from 'react-router-dom';

const styles = theme => ({
    millingStyle: {
        backgroundImage: `url(${"./static/img/milling-background.jpg"})`,
        backgroundSize: 'cover',
        overflow: 'hidden',
        width: '100%',
        height: '100%',
        position: 'fixed',
        left: 0,
        top: 0,
        z: -1,
        flex: 1,
        justifyContent: 'left',
        alignItems: 'left',
        display: 'flex',
        verticalAlign: 'middle',
    },
    stepsList: {
        width: 'calc(20% - 20px)',
        height: 'calc(100% - 120px)',
        marginTop: '30px',
        marginLeft: '10px',
        position: 'fixed'
    },
    middle: {
        width: 'calc(38% - 20px)',
        height: 'calc(100% - 110px)',
        marginTop: '60px',
        marginLeft: 'calc(20% + 10px)',
        position: 'fixed'
    },
    instructions: {
        width: '100%',
        height: '50%',
        postion: 'fixed'
    },
    warning: {
        height: '40px',
        textAlign: 'center',
    },
    actions: {
        textAlign: 'center',
    },
    right: {
        width: 'calc(42% - 20px)',
        height: 'calc(100% - 160px)',
        marginTop: '110px',
        marginLeft: 'calc(58% + 10px)',
    }
});

class Milling extends React.Component {
    constructor() {
        super();
        this.state = {
            steps: ipcRenderer.sendSync("Jobs::GetSteps"),
            selectedStepIndex: 0,
            selectedStep: ipcRenderer.sendSync("Jobs::GetStep", 0),
            showImage: true,
            showStartMilling: false,
            goBack: false,
            millingProgress: -1
        };
    }

    progress(milling) {
        const millingProgress = milling.state.millingProgress;
        if (millingProgress === 100) {
            clearInterval(milling.timer);
            milling.showNextStep(milling);
        } else {
            const updatedProgress = ipcRenderer.sendSync("Jobs::GetProgress", milling.state.selectedStepIndex);
            milling.setState({ millingProgress: updatedProgress });
        }
    };

    showNextStep(milling) {
        const nextStepIndex = (milling.state.selectedStepIndex + 1);
        if (nextStepIndex < milling.state.steps.length) {
            milling.setState({
                showStartMilling: false,
                millingProgress: -1,
                selectedStepIndex: nextStepIndex,
                selectedStep: ipcRenderer.sendSync("Jobs::GetStep", nextStepIndex)
            });
        } else {
            milling.setState({
                goBack: true
            });
        }
    }

    render() {
        const { classes } = this.props;

        function getWarning(milling) {
            if (milling.state.selectedStep != null) {
                if (milling.state.selectedStep.GCode != null && milling.state.millingProgress == -1) {
                    return (
                        <Typography align='center' color='error'>
                            Warning!<br />
                            GG will move after pressing start
                    </Typography>
                    );
                }
            }

            return "";
        }

        function getMillingInProgressDisplay(milling) {
            if (milling.state.millingProgress >= 0) {
                return (
                    <LinearProgress variant="determinate" color="secondary" style={{ height: '15px' }} value={milling.state.millingProgress} />
                );
            }

            return "";
        }

        function handleNext(event) {
            if (this.state.selectedStep.GCode != null) {
                this.setState({
                    showStartMilling: true
                });
            } else {
                this.showNextStep(this);
            }
        }

        function handleStop(event) {
            ipcRenderer.send("Jobs::EmergencyStop");
            clearInterval(this.timer);

            // TODO: Show dialog
            this.setState({
                millingProgress: -1,
                selectedStepIndex: 0,
                selectedStep: ipcRenderer.sendSync("Jobs::GetStep", 0)
            });
        }

        function handleCloseStartMilling(start) {
            if (start) {
                this.setState({
                    millingProgress: 0,
                    showStartMilling: false
                });
                ipcRenderer.send("Jobs::StartMilling", this.state.selectedStepIndex);
                this.timer = setInterval(this.progress, 200, this);
            } else {
                this.setState({ showStartMilling: false });
            }
        }

        function getActionButton(component) {
            if (component.state.millingProgress == -1) {
                return (
                    <IconButton onClick={handleNext.bind(component)}>
                        <img
                            style={{ height: '90px' }}
                            onMouseOver={e => e.currentTarget.src = path.join(__dirname, '../../static/img/next_hover.png')}
                            onMouseOut={e => e.currentTarget.src = path.join(__dirname, '../../static/img/next.png')}
                            src={path.join(__dirname, '../../static/img/next.png')}
                        />
                    </IconButton>
                );
            } else {
                return (
                    <IconButton onClick={handleStop.bind(component)}>
                        <img
                            style={{ height: '80px' }}
                            src={path.join(__dirname, '../../static/img/stop_circle.png')}
                        />
                    </IconButton>
                );
            }
        }

        if (this.state.goBack == true) {
            return (<Redirect to='/' />);
        }

        return (
            <section className={classes.millingStyle}>
                <section className={classes.stepsList}>
                    <Button style={{ marginTop: '5px' }} onClick={(event) => { this.setState({ goBack: true }) }}>
                        <img
                            style={{ height: '16px' }}
                            src={path.join(__dirname, '../../static/img/back-to-main.png')}
                        />
                    </Button>
                    <StepList steps={this.state.steps} selectedStep={this.state.selectedStepIndex} />
                </section>
                <section className={classes.middle}>
                    <StartMilling open={this.state.showStartMilling} onClose={handleCloseStartMilling.bind(this)} />
                    <div className={classes.instructions}>
                        <Typography variant="subtitle1" style={{ textTransform: 'uppercase' }}><b> {this.state.selectedStep.Title} </b></Typography>
                        <br />
                        <Typography>{this.state.selectedStep.Prompt}</Typography>
                    </div>
                    <div className={classes.warning}>
                        {getMillingInProgressDisplay(this)}
                        {getWarning(this)}
                    </div>
                    <div className={classes.actions}>
                        {getActionButton(this)}
                    </div>
                </section>
                <section className={classes.right}>
                    <ImageRaw selectedStep={this.state.selectedStep} />
                </section>
            </section>
        );
    }
}

Milling.propTypes = {
    classes: PropTypes.object.isRequired,
};

export default withStyles(styles)(Milling);
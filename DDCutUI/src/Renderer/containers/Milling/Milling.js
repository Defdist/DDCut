import React from 'react';
import PropTypes from 'prop-types';
import { ipcRenderer } from 'electron';
import withStyles from '@material-ui/core/styles/withStyles';
import StepList from '../../components/StepList';
import ImageRaw from '../../components/ImageRaw';
import StartMilling from '../../components/Modals/StartMilling';
import Alert from '../../components/Modals/Alert';
import path from "path";
import { Button, IconButton, Typography, LinearProgress, Grid } from '@material-ui/core';
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
    },
    prev: {
		float: 'left',
		padding: '5px'
        //marginLeft: -2 * theme.spacing.unit
    },
    next: {
		float: 'right',
		padding: '5px'
        //marginLeft: 2 * theme.spacing.unit
    },
    stepNumber: {
        marginTop: '6px',
        opacity: 0.87,
        fontSize: '14px',
        color: '#9f9f9f'
    }
});

class Milling extends React.Component {
    constructor() {
        super();
        this.state = {
            steps: ipcRenderer.sendSync("Jobs::GetSteps"),
            selectedStepIndex: 0,
            selectedStep: ipcRenderer.sendSync("Jobs::GetStep", 0),
			previousMillingStep: 0,
            showImage: true,
            showStartMilling: false,
            goBack: false,
            millingProgress: -1,
			showAlert: false,
			alertMessage: ""
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

    showPrevStep(milling) {
        const prevStepIndex = (milling.state.selectedStepIndex - 1);
        milling.setState({
            showStartMilling: false,
            millingProgress: -1,
            selectedStepIndex: prevStepIndex,
            selectedStep: ipcRenderer.sendSync("Jobs::GetStep", prevStepIndex)
        });
    }

    skipToNextMillingStep(milling) {
        const stepIndex = milling.state.selectedStep.next_milling_step;
        milling.setState({
            showStartMilling: false,
            millingProgress: -1,
            selectedStepIndex: stepIndex,
            selectedStep: ipcRenderer.sendSync("Jobs::GetStep", stepIndex)
        });
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

        function handlePrev(event) {
			this.showPrevStep(this);
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

		function handleSkip(event) {
			this.skipToNextMillingStep(this);
		}

        function handleStop(event) {
            ipcRenderer.send("Jobs::EmergencyStop");
            clearInterval(this.timer);

            this.setState({
                millingProgress: -1,
                selectedStepIndex: 0,
                selectedStep: ipcRenderer.sendSync("Jobs::GetStep", 0),
				previousMillingStep: 0,
				showAlert: true,
				alertMessage: 'Emergency stop was pressed. Resetting job.'
            });
        }

        function handleCloseStartMilling(start) {
            if (start) {
                this.setState({
                    millingProgress: 0,
                    showStartMilling: false,
					previousMillingStep: this.state.selectedStepIndex
                });
                ipcRenderer.send("Jobs::StartMilling", this.state.selectedStepIndex);
                this.timer = setInterval(this.progress, 100, this);
            } else {
                this.setState({ showStartMilling: false });
            }
        }

		function isNextAvailable(component) {
			return component.state.millingProgress == -1;
		}

		function isPrevAvailable(component) {
			if (component.state.millingProgress == -1) {
				if (component.state.selectedStepIndex == 0) {
					return false;
				}

				if (component.state.selectedStepIndex - 1 > component.state.previousMillingStep) {
					return true;
				}
			}

			return false;
		}

		function isSkipAvailable(component) {
			return component.state.selectedStep.next_milling_step != null;
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
			<React.Fragment>
				<Alert open={this.state.showAlert} message={this.state.alertMessage} close={(event) => { this.setState({ showAlert: false }) }} />

				<section className={classes.millingStyle}>
					<section className={classes.stepsList}>
						<Button style={{ marginTop: '5px' }} onClick={(event) => { this.setState({ goBack: true }) }}>
							<img
								style={{ height: '16px' }}
								src={path.join(__dirname, '../../static/img/back-to-main.png')}
							/>
						</Button>
						<StepList steps={this.state.steps} selectedStep={this.state.selectedStepIndex} />
						<Grid container spacing={0}>
							<Grid item xs={4}>
								<Button color="secondary" disabled={!isPrevAvailable(this)} className={classes.prev} onClick={handlePrev.bind(this)}>&#60; Prev</Button>
							</Grid>
							<Grid item xs={4}>
								<center><Typography className={classes.stepNumber}>Step {this.state.selectedStepIndex + 1}/{this.state.steps.length}</Typography></center>
							</Grid>
							<Grid item xs={4}>
								<Button color="secondary" disabled={!isNextAvailable(this)} className={classes.next} onClick={handleNext.bind(this)}>Next &#62;</Button>
							</Grid>
						</Grid>
						<Button color="secondary" disabled={!isSkipAvailable(this)} className={classes.next} onClick={handleSkip.bind(this)}>Skip to Next Milling Step &#62;</Button>
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
						<ImageRaw selectedStep={this.state.selectedStep} millingInProgress={this.state.millingProgress != -1} />
					</section>
				</section>
			</React.Fragment>
        );
    }
}

Milling.propTypes = {
    classes: PropTypes.object.isRequired,
};

export default withStyles(styles)(Milling);
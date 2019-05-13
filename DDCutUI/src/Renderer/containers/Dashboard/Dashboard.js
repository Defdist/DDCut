import React from 'react';
import PropTypes from 'prop-types';
import Menu from '../../components/Menu';
import { Button, Grid } from "@material-ui/core";
import withStyles from '@material-ui/core/styles/withStyles';
import path from "path";
import { ipcRenderer, shell } from "electron";
import JobSelection from '../../components/Modals/JobSelection';
import { Redirect } from 'react-router-dom';
import CustomerSupport from '../../components/Modals/CustomerSupport';

const styles = theme => ({
    main: {
        width: '80%',
        height: '45%',
        marginTop: 'auto',
        marginBottom: 'auto',
        marginLeft: 'auto',
        marginRight: 'auto',
        position: 'absolute',
        borderLeft: 'solid 3px #969696',
        borderRight: 'solid 3px #969696',
        borderBottom: 'solid 3px #969696',
    },
    dashboardStyle: {
        backgroundImage: `url(${"./static/img/back-texture.jpg"})`,
        backgroundSize: 'cover',
        overflow: 'hidden',
        width: '100%',
        height: '100%',
        position: 'fixed',
        left: 0,
        top: 0,
        z: -1,
        flex: 1,
        justifyContent: 'center',
        alignItems: 'center',
        display: 'flex',
        verticalAlign: 'middle',
    },
    topLeft: {
        width: 'calc(40% - 60px)',
        height: '45%',
        marginTop: 'auto',
        marginBottom: 'auto',
        marginLeft: 'calc(-20% - 30px)',
        position: 'absolute',
        borderTop: 'solid 3px #969696',
    },
    topRight: {
        width: 'calc(40% - 60px)',
        height: '45%',
        marginTop: 'auto',
        marginBottom: 'auto',
        marginLeft: 'calc(20% + 30px)',
        position: 'absolute',
        borderTop: 'solid 3px #969696',
    }
});

function Dashboard(props) {
    const { classes, status } = props;
    const [availableJobs, setAvailableJobs] = React.useState(new Array());
    const [showJobSelection, setShowJobSelection] = React.useState(false);
    const [navigateToMilling, setNavigateToMilling] = React.useState(false);
    const [openCustomerSupport, setOpenCustomerSupport] = React.useState(false);

    function onClickRun() {
        if (status == 2) {
            ipcRenderer.removeAllListeners("Jobs::JobSelected");
            ipcRenderer.on("Jobs::JobSelected", (event) => {
                setNavigateToMilling(true);
            });

            ipcRenderer.removeAllListeners("ShowJobSelection");
            ipcRenderer.on("ShowJobSelection", (event, jobs) => {
                setAvailableJobs(jobs);
                setShowJobSelection(true);
            });

            ipcRenderer.send('File::OpenFileDialog');
        }
    }

    function onCloseJobSelection(event) {
        setShowJobSelection(false);
    }

    function onClickHelp() {
        setOpenCustomerSupport(true);
    }

    if (navigateToMilling) {
        return (<Redirect to='/milling' />);
    }

    function getRunImage() {
        if (status == 2) {
            return (
                <img
                    style={{ marginTop: '20px', height: '14vh' }}
                    src={path.join(__dirname, '../../static/img/run.png')}
                    onMouseOver={e => e.currentTarget.src = path.join(__dirname, '../../static/img/run_hover.png')}
                    onMouseOut={e => e.currentTarget.src = path.join(__dirname, '../../static/img/run.png')}
                    onClick={onClickRun}
                />
            );
        } else {
            return (
                <img
                    style={{ marginTop: '20px', height: '14vh' }}
                    src={path.join(__dirname, '../../static/img/run.png')}
                />
            );
        }
    }

    return (
        <section className={classes.dashboardStyle} >
            <Menu />
            <JobSelection open={showJobSelection} onClose={onCloseJobSelection} jobs={availableJobs} />

            <div className={classes.topLeft} />
            <div className={classes.topRight} />
            <div className={classes.main}>
                <div style={{ position: "absolute", width: "100%" }}>
                    <center>
                        <img src={path.join(__dirname, '../../static/img/logo-white.png')} width="88px" style={{ marginTop: "-44px" }} />
                    </center>
                </div>
                <Grid container
                    spacing={8}
                    direction="row"
                    justify="center"
                    alignItems="center"
                    style={{ height: '100%' }}
                >
                    <Grid item xs={4}>
                        <center>
                            <Button style={{ backgroundColor: "transparent" }} id="store">
                                <img
                                    style={{ marginTop: '20px', marginLeft: '30px', height: '14vh' }}
                                    src={path.join(__dirname, '../../static/img/store.png')}
                                    onMouseOver={e => e.currentTarget.src = path.join(__dirname, '../../static/img/store_hover.png')}
                                    onMouseOut={e => e.currentTarget.src = path.join(__dirname, '../../static/img/store.png')}
                                    onClick={() => { shell.openExternal("https://ghostgunner.net/collections/featured-products") }}
                                />
                            </Button>
                        </center>
                    </Grid>
                    <Grid item xs={4}>
                        <center>
                            <Button style={{ backgroundColor: "transparent" }} disabled={status != 2} id="run">
                                {getRunImage()}
                            </Button>
                        </center>
                    </Grid>
                    <Grid item xs={4}>
                        <center>
                            <Button style={{ backgroundColor: "transparent" }}>
                                <img
                                    style={{ marginTop: '20px', marginRight: '30px', height: '14vh' }}
                                    src={path.join(__dirname, '../../static/img/help.png')}
                                    onMouseOver={e => e.currentTarget.src = path.join(__dirname, '../../static/img/help_hover.png')}
                                    onMouseOut={e => e.currentTarget.src = path.join(__dirname, '../../static/img/help.png')}
                                    onClick={onClickHelp}
                                />
                            </Button>
                        </center>
                    </Grid>
                </Grid>
            </div>

            <CustomerSupport open={openCustomerSupport} onClose={() => { setOpenCustomerSupport(false) }} />
        </section>
    );
}

Dashboard.propTypes = {
    classes: PropTypes.object.isRequired,
    status: PropTypes.number.isRequired
};

export default withStyles(styles)(Dashboard);
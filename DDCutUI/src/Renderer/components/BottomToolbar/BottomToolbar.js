import React from "react";
import PropTypes from "prop-types";
import { withStyles } from "@material-ui/core/styles";
import { AppBar, Button, Grid, Toolbar } from "@material-ui/core";
import { shell } from "electron";
import Status from '../Status';
import Settings from '../Modals/Settings';
import GhostChooser from '../Modals/GhostChooser';
import Support from '../Support';

const styles = theme => ({
    root: {
        marginBottom: theme.spacing.unit * 3,
        flexGrow: 1
    },
    appBar: {
        top: 'auto',
        height: 39,
        bottom: 0,
        backgroundImage: `url(${"./static/img/bottom-bar.png"})`,
        backgroundSize: 'cover',
        backgroundPosition: 'center',
    },
    right: {
        float: 'right'
    }
});

function BottomToolbar(props) {
    const { classes, status, milling } = props;

    function openGhostGunnerNet() {
        shell.openExternal("https://ghostgunner.net/");
    }

    return (
        <footer className={classes.root}>
            <AppBar position="fixed" className={classes.appBar}>
                <Toolbar>
                    <Grid container spacing={0} className={classes.root} alignItems="center">
                        <Grid item xs={4}>
                            <Status status={status} />
                            <GhostChooser disabled={milling} />
                        </Grid>
                        <Grid item xs={8}>
                            <div className={classes.right}>
                                <Button color="secondary" onClick={openGhostGunnerNet}>
                                    Ghostgunner.net
                                </Button>
                                <Settings disabled={milling} />
                                <Support disabled={milling} />
                            </div>
                        </Grid>
                    </Grid>
                </Toolbar>
            </AppBar>
        </footer>
    );
}

BottomToolbar.propTypes = {
    classes: PropTypes.object.isRequired,
    status: PropTypes.number.isRequired,
	milling: PropTypes.bool.isRequired
};

export default withStyles(styles)(BottomToolbar);

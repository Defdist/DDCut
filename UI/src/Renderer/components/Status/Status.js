import React from "react";
import PropTypes from "prop-types";
import {
    MuiThemeProvider, createMuiTheme, Fab, Typography
} from "@material-ui/core";
import { withStyles } from "@material-ui/core/styles";
import { red, yellow } from "@material-ui/core/colors";
import StatusIcon from "@material-ui/icons/lens";
import app from 'app';

const styles = theme => ({
    leftRightPadding: {
        padding: theme.spacing.unit,
    },
    status: {
        marginLeft: 0,
        paddingLeft: 0,
    }
});

function Status(props) {
    const { classes, status } = props;


    const statusTheme = createMuiTheme({
        palette: {
            primary: {
                main: app.colors.secondary,
            },
            secondary: yellow,
            error: red
        },
        typography: {
            useNextVariants: true,
            body1: {
                fontSize: 14
            }
        }
    });

    function getColor() {
        var color = "error";

        if (status == 1) {
            color = "secondary";
        } else if (status == 2) {
            color = "primary";
        }

        return color;
    }

    function getStatusText() {
        var statusText = "Not Connected";

        if (status == 1) {
            statusText = "Connecting";
        } else if (status == 2) {
            statusText = "Connected";
        }

        return statusText;
    }

    return (
        <React.Fragment>
            <MuiThemeProvider theme={statusTheme}>
                <Fab
                    variant="extended"
                    disabled={true}
                    align="left"
                    className={classes.status}
					id="GGStatus"
                >
                    <StatusIcon color={getColor()} style={{ width: "18px" }} />
                    <Typography variant="body1" color={getColor()}>
                        <b>
                            <span className={classes.leftRightPadding} style={{ color: '#ffffff' }}>
                                {app.toolbar.status.label}
                            </span>
                            {getStatusText()}
                        </b>
                    </Typography>
                </Fab>
            </MuiThemeProvider>
        </React.Fragment>
    );
}

Status.propTypes = {
    classes: PropTypes.object.isRequired,
    status: PropTypes.number.isRequired
};

export default withStyles(styles)(Status);

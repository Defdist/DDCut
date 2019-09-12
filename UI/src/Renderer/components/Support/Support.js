import React from "react";
import PropTypes from "prop-types";
import path from "path";
import { shell, ipcRenderer } from 'electron';
import {
    Fab, Popper, Grow, Paper, ClickAwayListener, MenuList, MenuItem, Tooltip
} from "@material-ui/core";
import { withStyles } from "@material-ui/core/styles";
import CustomerSupport from '../Modals/CustomerSupport';
import ViewLogs from '../Modals/ViewLogs';
import app from 'app';

const styles = theme => ({
    root: {
        display: 'flex',
    },
    paper: {
        marginBottom: '5px',
        border: '#FFFFFF 1px solid',
    },
    menuItem: {
        '&:hover': {
            backgroundColor: theme.palette.primary.dark
        },
        color: '#ffffff'
    },
    supportButton: {
        paddingTop: 0,
        paddingBottom: 0,
        paddingLeft: theme.spacing.unit,
        paddingRight: theme.spacing.unit,
        backgroundColor: "transparent",
        '&:disabled': {
            opacity: 0.5
        }
    },
    supportImg: {
        width: '100px',
        height: '25px',
        objectFit: 'contain',
        padding: 0,
        margin: 0
    }
});

class Support extends React.Component {
    constructor() {
        super();
        this.state = {
            openDialog: false,
            openMenu: false,
            openLogViewer: false,
        };

        this.anchor = React.createRef();
        this.handleToggleMenu = this.handleToggleMenu.bind(this);
        this.handleCloseMenu = this.handleCloseMenu.bind(this);
        this.handleOpenDialog = this.handleOpenDialog.bind(this);
        this.handleCloseDialog = this.handleCloseDialog.bind(this);
        this.handleShowLogs = this.handleShowLogs.bind(this);
        this.handleCloseLogViewer = this.handleCloseLogViewer.bind(this);
    }

    handleToggleMenu() {
        this.setState({
            openMenu: !this.state.openMenu
        });
    }

    handleCloseMenu(event) {
        if (this.anchor.contains(event.target)) {
            return;
        }

        this.setState({
            openMenu: false
        });
    }

    handleOpenDialog() {
        this.setState({
            openDialog: true,
            openMenu: false
        });
    }

    handleCloseDialog() {
        this.setState({
            openDialog: false
        });
    }

    handleShowLogs() {
        this.setState({
            openMenu: false,
            openLogViewer: true
        });
    }

    handleCloseLogViewer() {
        this.setState({
            openMenu: false,
            openLogViewer: false
        });
    }

    render() {
        const { classes, disabled } = this.props;

        if (disabled && this.state.openMenu === true) {
            this.setState({
                openMenu: false
            });
        }

		function onClickWalkthrough(event) {
			const currentPage = ipcRenderer.sendSync("DD_GetCurrentPage");
			if (currentPage == "Dashboard") {
				window.ShowDashboardWalkthrough(app.machine_name);
			} else if (currentPage == "Milling") {
				window.ShowMillingWalkthrough(app.machine_name);
			}

			this.handleCloseMenu(event);
		}

        function onClickViewManual(event) {
            shell.openExternal(path.join(__dirname, app.support.manual));
            this.handleCloseMenu(event);
        }

        function onClickVisitSupport(event) {
            shell.openExternal(app.support.link);
            this.handleCloseMenu(event);
        }

		function onClickOpenDialog() {
			this.handleOpenDialog();
		}

		function onClickShowLogs() {
			this.handleShowLogs();
        }

        function getManualMenu(_this) {
            if (app.support.manual.length > 0) {
                return(
                    <MenuItem className={ classes.menuItem } onClick={ onClickViewManual.bind(_this) }>View Manual</MenuItem>
                );
            }
        }

        return (
            <React.Fragment>
                <Tooltip
                    disableHoverListener={!disabled}
                    disableFocusListener={true}
                    disableTouchListener={true}
                    title="Disabled while machine is running"
                >
                    <span>
                        <Fab
                            variant="extended"
                            aria-label="Support"
                            onClick={this.handleToggleMenu}
                            className={classes.supportButton}
				            disabled={disabled}
                            size="small"
                            buttonRef={node => { this.anchor = node }}
					        id="support"
                        >
                            <img src={path.join(__dirname, './static/img/support_button.png')} className={classes.supportImg} />
                        </Fab>
                    </span>
                </Tooltip>

                <Popper open={this.state.openMenu} anchorEl={this.anchor} transition disablePortal>
                    {({ TransitionProps, placement }) => (
                        <Grow
                            {...TransitionProps}
                            id="menu-list-grow"
                            style={{ transformOrigin: placement === 'bottom' ? 'center top' : 'center bottom' }}
                        >
                            <Paper className={classes.paper}>
                                <ClickAwayListener onClickAway={this.handleCloseMenu}>
                                    <MenuList>
                                        <MenuItem className={classes.menuItem} onClick={onClickWalkthrough.bind(this)}>'How to' Walkthrough</MenuItem>
                                        {getManualMenu(this)}
                                        <MenuItem className={classes.menuItem} onClick={onClickVisitSupport.bind(this)}>Visit Support Page</MenuItem>
                                        <MenuItem className={classes.menuItem} onClick={onClickOpenDialog.bind(this)}>Bug Report</MenuItem>
                                        <MenuItem className={classes.menuItem} onClick={onClickShowLogs.bind(this)}>Show Logs</MenuItem>
                                    </MenuList>
                                </ClickAwayListener>
                            </Paper>
                        </Grow>
                    )}
                </Popper>

                <CustomerSupport open={this.state.openDialog} onClose={this.handleCloseDialog} />
                <ViewLogs open={this.state.openLogViewer} onClose={this.handleCloseLogViewer} />
            </React.Fragment>
        );
    }
};

Support.propTypes = {
    classes: PropTypes.object.isRequired,
    disabled: PropTypes.bool.isRequired
};

export default withStyles(styles)(Support);

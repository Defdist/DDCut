import React from 'react';
import PropTypes from 'prop-types';
import { withStyles } from '@material-ui/core/styles';
import { List, ListItem, ListItemText, Typography } from '@material-ui/core';
import app from 'app';

const styles = theme => ({
    root: {
        width: '100%',
        height: 'calc(100% - 40px)',
    },
    list: {
        width: '100%',
        height: '100%',
        overflow: 'auto',
        backgroundColor: app.milling.steps.list.background,
        webkitAppearance: 'none',
        mozAppearance: 'none',
        appearance: 'none',
        border: '0px',
        padding: '0px'
    },
    item: {
        '&:hover': {
            height: '35px',
            backgroundColor: app.milling.steps.items.background,
            border: '0px',
            marginLeft: '0px',
            marginRight: '0px',
        },
        '&:focus': {
            height: '35px',
            backgroundColor: app.milling.steps.items.background,
            border: '0px',
            marginLeft: '0px',
            marginRight: '0px',
        },
        height: '35px',
        backgroundColor: app.milling.steps.items.background,
        border: '0px',
        marginLeft: '0px',
        marginRight: '0px',
    },
    itemText: {
        marginLeft: '0px',
        marginRight: '0px',
        opacity: 0.87,
        fontSize: '14px',
        color: app.milling.steps.fontColor /* selected: color: #069076;*/
    }
});

class StepList extends React.Component {
    constructor() {
        super();
        this.selectedRef = React.createRef();
    }
    
    componentWillReceiveProps(prevProps) {
        setTimeout(() => {
            this.selectedRef.scrollIntoView({ behavior: "smooth", block: 'center' });
        });
    }

    render() {
        const { classes, steps, selectedStep } = this.props;

        function getListItem(step, index, component) {
            var selectedDiv = null;
            if (selectedStep === index) {
                selectedDiv = (<div style={{ float: "left", clear: "both" }} ref={(el) => { component.selectedRef = el; }} />);
            }

            var color = app.milling.steps.items.background;
            if (selectedStep === index) {
                color = app.milling.steps.items.selected;
            }

            return (
                <ListItem
                    button
                    disableGutters
                    key={index}
                    selected={selectedStep === index}
                    className={classes.item}
                    style={{ backgroundColor: color }}
                >
                    <ListItemText disableTypography>
                        {selectedDiv}
                        <Typography noWrap className={classes.itemText}>{step.Title}</Typography>
                    </ListItemText>
                </ListItem>
            );
        }

        return (
            <div className={classes.root}>
                <List component="nav" className={classes.list}>
                    {
                        steps.map((step, index) => {
                            return getListItem(step, index, this);
                        })
                    }
                </List>
                {/*<Typography className={classes.stepNumber} align="right">Step {selectedStep + 1}/{steps.length}</Typography>*/}
            </div>
        );
    }
};

StepList.propTypes = {
    classes: PropTypes.object.isRequired,
    steps: PropTypes.array.isRequired,
    selectedStep: PropTypes.number.isRequired
};

export default withStyles(styles)(StepList);
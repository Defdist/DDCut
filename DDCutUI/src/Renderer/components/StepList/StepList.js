import React from 'react';
import PropTypes from 'prop-types';
import { withStyles } from '@material-ui/core/styles';
import { List, ListItem, ListItemText, Typography } from '@material-ui/core';

const styles = theme => ({
    root: {
        width: '100%',
        height: 'calc(100% - 40px)',
    },
    list: {
        width: '100%',
        height: '100%',
        overflow: 'auto',
        backgroundColor: '#9f9f9f',
        webkitAppearance: 'none',
        mozAppearance: 'none',
        appearance: 'none',
        border: '0px',
        padding: '0px'
    },
    item: {
        height: '35px',
        backgroundColor: 'black',
        border: '0px',
        marginLeft: '0px',
        marginRight: '0px',
    },
    itemText: {
        marginLeft: '0px',
        marginRight: '0px',
        fontFamily: 'Arial',
        opacity: 0.87,
        fontSize: '14px',
        color: '#9f9f9f' /* selected: color: #069076;*/
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

            return (
                <ListItem
                    button
                    disableGutters
                    key={index}
                    selected={selectedStep === index}
                    className={classes.item}
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
import React from 'react';
import PropTypes from 'prop-types';
import { withStyles } from '@material-ui/core/styles';
import { List, ListItem, ListItemText, Typography } from '@material-ui/core';

const styles = theme => ({
    root: {
        width: '100%',
        height: '100%',
    },
    list: {
        width: '100%',
        height: 'calc(100% - 20px)',
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
    },
    stepNumber: {
        marginTop: '10px',
        opacity: 0.87,
        fontSize: '14px',
        color: '#9f9f9f'
    }
});

class StepList extends React.Component {
    constructor() {
        super();
        this.selectedRef = React.createRef();
    }

    //isScrolledIntoView(el) {
    //    var rect = el.getBoundingClientRect();
    //    var elemTop = rect.top;
    //    var elemBottom = rect.bottom;

    //    // Only completely visible elements return true:
    //    var isVisible = (elemTop >= 0) && (elemBottom <= window.innerHeight);
    //    // Partially visible elements return true:
    //    //isVisible = elemTop < window.innerHeight && elemBottom >= 0;
    //    return isVisible;
    //}

    //handleScrollToElement(event) {
    //    if (!isScrolledIntoView(this.selectedRef)) {
    //        window.scrollTo(0, this.selectedRef.current.offsetTop);
    //    }
    //}

    render() {
        const { classes, steps, selectedStep } = this.props;

        return (
            <div className={classes.root}>
                <List component="nav" className={classes.list}>
                    {
                        steps.map((step, index) => {
                            return (
                                <ListItem
                                    button
                                    disableGutters
                                    key={index}
                                    ref={selectedStep === index ? this.selectedRef : null}
                                    selected={selectedStep === index}
                                    className={classes.item}
                                >
                                    <ListItemText disableTypography>
                                        <Typography noWrap className={classes.itemText}>{step.Title}</Typography>
                                    </ListItemText>
                                </ListItem>
                            );
                        })
                    }
                </List>
                <Typography className={classes.stepNumber} align="right">Step {selectedStep + 1}/{steps.length}</Typography>
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
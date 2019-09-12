import React from 'react';
import { Route, HashRouter as Router, Switch } from 'react-router-dom';
import PropTypes from "prop-types";
import ScrollToTop from './util/ScrollToTop'
import Dashboard from './containers/Dashboard';
import Milling from './containers/Milling';


function Routes(props) {
    const { status } = props;

    return (
        <Router>
            <ScrollToTop>
                <Switch>
                    <Route exact path='/' render={(props) => <Dashboard {...props} status={status} />} />
                    <Route exact path='/milling' component={Milling} />
                </Switch>
            </ScrollToTop>
        </Router>
    );
}

Routes.propTypes = {
    status: PropTypes.number.isRequired
};

export default (Routes);

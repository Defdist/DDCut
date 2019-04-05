import React from 'react';
import { Route, HashRouter as Router, Switch } from 'react-router-dom';
import PropTypes from "prop-types";
import ScrollToTop from './util/ScrollToTop'
import Dashboard from './containers/Dashboard';
import Milling from './containers/Milling';


function Routes() {
    return (
        <Router>
            <ScrollToTop>
                <Switch>
                    <Route exact path='/' component={Dashboard} />
                    <Route exact path='/milling' component={Milling} />
                </Switch>
            </ScrollToTop>
        </Router>
    );
}

export default (Routes);

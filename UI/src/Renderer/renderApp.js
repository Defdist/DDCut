/*import React from 'react';
import ReactDOM from 'react-dom';
import {AppContainer} from 'react-hot-loader';

// main app
import App from './App';

ReactDOM.render(
    <AppContainer>
        <App />
    </AppContainer>, document.getElementById('App')
);
*/


import React from 'react';
import ReactDOM from 'react-dom';
import {AppContainer} from 'react-hot-loader';
//import installExtension, { REACT_DEVELOPER_TOOLS } from 'electron-devtools-installer';

/*installExtension(REACT_DEVELOPER_TOOLS)
    .then((name) => console.log(`Added Extension:  ${name}`))
    .catch((err) => console.log('An error occurred: ', err));*/

    const render = () => {
    const App = require('./App').default;
    ReactDOM.render(
    <AppContainer>
        <App />
    </AppContainer>, document.getElementById('App'));
    }

    render();
if (module.hot) {
    module.hot.accept(render);
}

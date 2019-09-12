const path = require('path');

// TODO: Ask user for version number

const os = ((process.platform == 'win32') ? "win32" : "mac");

const UI_PATH = path.join(__dirname, '/UI');
var child_process = require('child_process');
child_process.execSync("npm install && cd " + UI_PATH + " && npm install && npm run dist:" + os, {stdio:[0,1,2]});
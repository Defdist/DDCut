const childProcess = require("child_process");
const electron = require("electron");
const webpack = require("webpack");
const config = require("./webpack.app.config");

let app = {
  app: "ddcut"
};
for (var i = 0; i < process.argv.length; i++) {
    console.log(process.argv[i]);
    if (process.argv[i].startsWith('--app=')) {
        app.app = process.argv[i].substr(6);
        break;
    }
}

console.log("Running " + app);

const env = "development";
const compiler = webpack(config(env, app));
let electronStarted = false;

const watching = compiler.watch({}, (err, stats) => {
  if (!err && !stats.hasErrors() && !electronStarted) {
    electronStarted = true;

    childProcess
      .spawn(electron, ["."], { stdio: "inherit" })
      .on("close", () => {
        watching.close();
      });
  }
});

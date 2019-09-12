const path = require("path");
const merge = require("webpack-merge");
const base = require("./webpack.base.config");

module.exports = (env, app) => {
  return merge(base(env, app.app), {
    entry: {
      index: "./src/index.js",
      app: "./src/Renderer/renderApp.js"
    },
    output: {
      filename: "[name].js",
      path: path.resolve(__dirname, "../app")
    }
  });
};

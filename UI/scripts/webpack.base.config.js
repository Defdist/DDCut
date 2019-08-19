const path = require("path");
const nodeExternals = require("webpack-node-externals");
const FriendlyErrorsWebpackPlugin = require("friendly-errors-webpack-plugin");

const translateEnvToMode = (env) => {
  if (env === "production") {
    return "production";
  }
  return "development";
};

module.exports = (env, app) => {
  return {
    target: "electron-renderer",
    mode: translateEnvToMode(env),
    node: {
        console: true,
        __dirname: false,
        __filename: false
    },
    externals: [nodeExternals()],
    resolve: {
      alias: {
        app: path.resolve(__dirname, `../config/app_${app}.json`),
        env: path.resolve(__dirname, `../config/env_${env}.json`),
        ddcut: path.resolve("./app/Backend/ddcut.node")
      }
    },
    devtool: "source-map",
    module: {
      rules: [
        {
          test: /(\.js$|\.jsx$)/,
          exclude: /node_modules/,
          use: [
            {
              loader: "babel-loader",
              options: {
                presets: ['@babel/preset-react']
              }
            }
          ]
        },
        {
          test: /\.css$/,
          use: ["style-loader", "css-loader"]
        },
        {
          test: /\.node$/,
          use: [
            {
              loader: 'native-ext-loader',
              options: {
                basePath: ['Backend'],// path.resolve(__dirname, '../app')
                emit: false
              }
            }
          ]
        }
      ]
    },
    plugins: [
      new FriendlyErrorsWebpackPlugin({ clearConsole: env === "development" })
    ]
  };
};

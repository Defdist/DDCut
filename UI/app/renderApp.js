/******/ (function(modules) { // webpackBootstrap
/******/ 	// The module cache
/******/ 	var installedModules = {};
/******/
/******/ 	// The require function
/******/ 	function __webpack_require__(moduleId) {
/******/
/******/ 		// Check if module is in cache
/******/ 		if(installedModules[moduleId]) {
/******/ 			return installedModules[moduleId].exports;
/******/ 		}
/******/ 		// Create a new module (and put it into the cache)
/******/ 		var module = installedModules[moduleId] = {
/******/ 			i: moduleId,
/******/ 			l: false,
/******/ 			exports: {}
/******/ 		};
/******/
/******/ 		// Execute the module function
/******/ 		modules[moduleId].call(module.exports, module, module.exports, __webpack_require__);
/******/
/******/ 		// Flag the module as loaded
/******/ 		module.l = true;
/******/
/******/ 		// Return the exports of the module
/******/ 		return module.exports;
/******/ 	}
/******/
/******/
/******/ 	// expose the modules object (__webpack_modules__)
/******/ 	__webpack_require__.m = modules;
/******/
/******/ 	// expose the module cache
/******/ 	__webpack_require__.c = installedModules;
/******/
/******/ 	// define getter function for harmony exports
/******/ 	__webpack_require__.d = function(exports, name, getter) {
/******/ 		if(!__webpack_require__.o(exports, name)) {
/******/ 			Object.defineProperty(exports, name, { enumerable: true, get: getter });
/******/ 		}
/******/ 	};
/******/
/******/ 	// define __esModule on exports
/******/ 	__webpack_require__.r = function(exports) {
/******/ 		if(typeof Symbol !== 'undefined' && Symbol.toStringTag) {
/******/ 			Object.defineProperty(exports, Symbol.toStringTag, { value: 'Module' });
/******/ 		}
/******/ 		Object.defineProperty(exports, '__esModule', { value: true });
/******/ 	};
/******/
/******/ 	// create a fake namespace object
/******/ 	// mode & 1: value is a module id, require it
/******/ 	// mode & 2: merge all properties of value into the ns
/******/ 	// mode & 4: return value when already ns object
/******/ 	// mode & 8|1: behave like require
/******/ 	__webpack_require__.t = function(value, mode) {
/******/ 		if(mode & 1) value = __webpack_require__(value);
/******/ 		if(mode & 8) return value;
/******/ 		if((mode & 4) && typeof value === 'object' && value && value.__esModule) return value;
/******/ 		var ns = Object.create(null);
/******/ 		__webpack_require__.r(ns);
/******/ 		Object.defineProperty(ns, 'default', { enumerable: true, value: value });
/******/ 		if(mode & 2 && typeof value != 'string') for(var key in value) __webpack_require__.d(ns, key, function(key) { return value[key]; }.bind(null, key));
/******/ 		return ns;
/******/ 	};
/******/
/******/ 	// getDefaultExport function for compatibility with non-harmony modules
/******/ 	__webpack_require__.n = function(module) {
/******/ 		var getter = module && module.__esModule ?
/******/ 			function getDefault() { return module['default']; } :
/******/ 			function getModuleExports() { return module; };
/******/ 		__webpack_require__.d(getter, 'a', getter);
/******/ 		return getter;
/******/ 	};
/******/
/******/ 	// Object.prototype.hasOwnProperty.call
/******/ 	__webpack_require__.o = function(object, property) { return Object.prototype.hasOwnProperty.call(object, property); };
/******/
/******/ 	// __webpack_public_path__
/******/ 	__webpack_require__.p = "";
/******/
/******/
/******/ 	// Load entry module and return exports
/******/ 	return __webpack_require__(__webpack_require__.s = "./src/Renderer/renderApp.js");
/******/ })
/************************************************************************/
/******/ ({

/***/ "./src/Renderer/App.js":
/*!*****************************!*\
  !*** ./src/Renderer/App.js ***!
  \*****************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "default", function() { return App; });
/* harmony import */ var react__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! react */ "react");
/* harmony import */ var react__WEBPACK_IMPORTED_MODULE_0___default = /*#__PURE__*/__webpack_require__.n(react__WEBPACK_IMPORTED_MODULE_0__);
/* harmony import */ var _material_ui_core_styles__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! @material-ui/core/styles */ "@material-ui/core/styles");
/* harmony import */ var _material_ui_core_styles__WEBPACK_IMPORTED_MODULE_1___default = /*#__PURE__*/__webpack_require__.n(_material_ui_core_styles__WEBPACK_IMPORTED_MODULE_1__);
/* harmony import */ var electron__WEBPACK_IMPORTED_MODULE_2__ = __webpack_require__(/*! electron */ "electron");
/* harmony import */ var electron__WEBPACK_IMPORTED_MODULE_2___default = /*#__PURE__*/__webpack_require__.n(electron__WEBPACK_IMPORTED_MODULE_2__);
/* harmony import */ var _Routes__WEBPACK_IMPORTED_MODULE_3__ = __webpack_require__(/*! ./Routes */ "./src/Renderer/Routes.js");
/* harmony import */ var custom_electron_titlebar__WEBPACK_IMPORTED_MODULE_4__ = __webpack_require__(/*! custom-electron-titlebar */ "custom-electron-titlebar");
/* harmony import */ var custom_electron_titlebar__WEBPACK_IMPORTED_MODULE_4___default = /*#__PURE__*/__webpack_require__.n(custom_electron_titlebar__WEBPACK_IMPORTED_MODULE_4__);
/* harmony import */ var _components_BottomToolbar__WEBPACK_IMPORTED_MODULE_5__ = __webpack_require__(/*! ./components/BottomToolbar */ "./src/Renderer/components/BottomToolbar/index.js");





 //import { Steps, Hints } from 'intro.js-react';
//import 'intro.js/introjs.css';

const theme = Object(_material_ui_core_styles__WEBPACK_IMPORTED_MODULE_1__["createMuiTheme"])({
  palette: {
    secondary: {
      main: "#069076"
    },
    primary: {
      main: '#ffffff',
      dark: '#888888',
      dark: '#333333'
    },
    text: {
      primary: "#ffffff",
      secondary: "#cccccc",
      disabled: "#444444"
    },
    background: {
      paper: "#000000"
    }
  },
  typography: {
    useNextVariants: true,
    // Use the system font instead of the default Roboto font.
    fontFamily: ['"Lato"', 'sans-serif'].join(',')
  },
  props: {
    MuiButtonBase: {
      disableRipple: true
    },
    MuiDialog: {
      TransitionProps: {
        enter: false,
        exit: false,
        timeout: 0
      }
    }
  },
  overrides: {
    MuiFormControl: {
      root: {
        backgroundColor: '#555555'
      }
    },
    MuiDialog: {
      paper: {
        border: '#FFFFFF 1px solid'
      }
    }
  }
});
class App extends react__WEBPACK_IMPORTED_MODULE_0__["Component"] {
  constructor() {
    super();
    this.state = {
      ghostGunnerStatus: 0,
      millingInProgress: false
    };
  }

  componentWillMount() {
    if (!this.props.data) {
      new custom_electron_titlebar__WEBPACK_IMPORTED_MODULE_4__["Titlebar"]({
        backgroundColor: custom_electron_titlebar__WEBPACK_IMPORTED_MODULE_4__["Color"].fromHex('#333333'),
        icon: './static/img/DD_icon.ico',
        menu: null,
        titleHorizontalAlignment: "left"
      });
    }
  }

  componentDidMount() {
    if (electron__WEBPACK_IMPORTED_MODULE_2__["ipcRenderer"].sendSync("Walkthrough::ShouldDisplay", "Dashboard")) {
      window.ShowDashboardWalkthrough();
      electron__WEBPACK_IMPORTED_MODULE_2__["ipcRenderer"].send("Walkthrough::SetShowWalkthrough", "Dashboard", false);
    }
  }

  render() {
    function updateStatus(event, newStatus) {
      if (newStatus != this.state.ghostGunnerStatus) {
        this.setState({
          ghostGunnerStatus: newStatus
        });
      }
    }

    function updateMillingStatus(event, newStatus) {
      if (newStatus != this.state.millingInProgress) {
        this.setState({
          millingInProgress: newStatus
        });
      }
    }

    electron__WEBPACK_IMPORTED_MODULE_2__["ipcRenderer"].removeAllListeners("DD_UpdateGGStatus");
    electron__WEBPACK_IMPORTED_MODULE_2__["ipcRenderer"].on("DD_UpdateGGStatus", updateStatus.bind(this));
    electron__WEBPACK_IMPORTED_MODULE_2__["ipcRenderer"].removeAllListeners("Milling::Status");
    electron__WEBPACK_IMPORTED_MODULE_2__["ipcRenderer"].on("Milling::Status", updateMillingStatus.bind(this));
    document.getElementsByClassName('window-appicon')[0].style.width = "20px";
    document.getElementsByClassName('window-appicon')[0].style.height = "20px";
    document.getElementsByClassName('window-appicon')[0].style.backgroundSize = "20px 20px";
    document.getElementsByClassName('window-appicon')[0].style.marginLeft = "5px";
    return react__WEBPACK_IMPORTED_MODULE_0__["createElement"](react__WEBPACK_IMPORTED_MODULE_0__["Fragment"], null, react__WEBPACK_IMPORTED_MODULE_0__["createElement"](_material_ui_core_styles__WEBPACK_IMPORTED_MODULE_1__["MuiThemeProvider"], {
      theme: theme
    }, react__WEBPACK_IMPORTED_MODULE_0__["createElement"](_Routes__WEBPACK_IMPORTED_MODULE_3__["default"], {
      status: this.state.ghostGunnerStatus
    }), react__WEBPACK_IMPORTED_MODULE_0__["createElement"](_components_BottomToolbar__WEBPACK_IMPORTED_MODULE_5__["default"], {
      status: this.state.ghostGunnerStatus,
      milling: this.state.millingInProgress
    })));
  }

}

/***/ }),

/***/ "./src/Renderer/Routes.js":
/*!********************************!*\
  !*** ./src/Renderer/Routes.js ***!
  \********************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony import */ var react__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! react */ "react");
/* harmony import */ var react__WEBPACK_IMPORTED_MODULE_0___default = /*#__PURE__*/__webpack_require__.n(react__WEBPACK_IMPORTED_MODULE_0__);
/* harmony import */ var react_router_dom__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! react-router-dom */ "react-router-dom");
/* harmony import */ var react_router_dom__WEBPACK_IMPORTED_MODULE_1___default = /*#__PURE__*/__webpack_require__.n(react_router_dom__WEBPACK_IMPORTED_MODULE_1__);
/* harmony import */ var prop_types__WEBPACK_IMPORTED_MODULE_2__ = __webpack_require__(/*! prop-types */ "prop-types");
/* harmony import */ var prop_types__WEBPACK_IMPORTED_MODULE_2___default = /*#__PURE__*/__webpack_require__.n(prop_types__WEBPACK_IMPORTED_MODULE_2__);
/* harmony import */ var _util_ScrollToTop__WEBPACK_IMPORTED_MODULE_3__ = __webpack_require__(/*! ./util/ScrollToTop */ "./src/Renderer/util/ScrollToTop.js");
/* harmony import */ var _containers_Dashboard__WEBPACK_IMPORTED_MODULE_4__ = __webpack_require__(/*! ./containers/Dashboard */ "./src/Renderer/containers/Dashboard/index.js");
/* harmony import */ var _containers_Milling__WEBPACK_IMPORTED_MODULE_5__ = __webpack_require__(/*! ./containers/Milling */ "./src/Renderer/containers/Milling/index.js");
function _extends() { _extends = Object.assign || function (target) { for (var i = 1; i < arguments.length; i++) { var source = arguments[i]; for (var key in source) { if (Object.prototype.hasOwnProperty.call(source, key)) { target[key] = source[key]; } } } return target; }; return _extends.apply(this, arguments); }








function Routes(props) {
  const {
    status
  } = props;
  return react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(react_router_dom__WEBPACK_IMPORTED_MODULE_1__["HashRouter"], null, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_util_ScrollToTop__WEBPACK_IMPORTED_MODULE_3__["default"], null, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(react_router_dom__WEBPACK_IMPORTED_MODULE_1__["Switch"], null, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(react_router_dom__WEBPACK_IMPORTED_MODULE_1__["Route"], {
    exact: true,
    path: "/",
    render: props => react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_containers_Dashboard__WEBPACK_IMPORTED_MODULE_4__["default"], _extends({}, props, {
      status: status
    }))
  }), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(react_router_dom__WEBPACK_IMPORTED_MODULE_1__["Route"], {
    exact: true,
    path: "/milling",
    component: _containers_Milling__WEBPACK_IMPORTED_MODULE_5__["default"]
  }))));
}

Routes.propTypes = {
  status: prop_types__WEBPACK_IMPORTED_MODULE_2___default.a.number.isRequired
};
/* harmony default export */ __webpack_exports__["default"] = (Routes);

/***/ }),

/***/ "./src/Renderer/components/BottomToolbar/BottomToolbar.js":
/*!****************************************************************!*\
  !*** ./src/Renderer/components/BottomToolbar/BottomToolbar.js ***!
  \****************************************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony import */ var react__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! react */ "react");
/* harmony import */ var react__WEBPACK_IMPORTED_MODULE_0___default = /*#__PURE__*/__webpack_require__.n(react__WEBPACK_IMPORTED_MODULE_0__);
/* harmony import */ var prop_types__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! prop-types */ "prop-types");
/* harmony import */ var prop_types__WEBPACK_IMPORTED_MODULE_1___default = /*#__PURE__*/__webpack_require__.n(prop_types__WEBPACK_IMPORTED_MODULE_1__);
/* harmony import */ var _material_ui_core_styles__WEBPACK_IMPORTED_MODULE_2__ = __webpack_require__(/*! @material-ui/core/styles */ "@material-ui/core/styles");
/* harmony import */ var _material_ui_core_styles__WEBPACK_IMPORTED_MODULE_2___default = /*#__PURE__*/__webpack_require__.n(_material_ui_core_styles__WEBPACK_IMPORTED_MODULE_2__);
/* harmony import */ var _material_ui_core__WEBPACK_IMPORTED_MODULE_3__ = __webpack_require__(/*! @material-ui/core */ "@material-ui/core");
/* harmony import */ var _material_ui_core__WEBPACK_IMPORTED_MODULE_3___default = /*#__PURE__*/__webpack_require__.n(_material_ui_core__WEBPACK_IMPORTED_MODULE_3__);
/* harmony import */ var electron__WEBPACK_IMPORTED_MODULE_4__ = __webpack_require__(/*! electron */ "electron");
/* harmony import */ var electron__WEBPACK_IMPORTED_MODULE_4___default = /*#__PURE__*/__webpack_require__.n(electron__WEBPACK_IMPORTED_MODULE_4__);
/* harmony import */ var _Status__WEBPACK_IMPORTED_MODULE_5__ = __webpack_require__(/*! ../Status */ "./src/Renderer/components/Status/index.js");
/* harmony import */ var _Modals_Settings__WEBPACK_IMPORTED_MODULE_6__ = __webpack_require__(/*! ../Modals/Settings */ "./src/Renderer/components/Modals/Settings/index.js");
/* harmony import */ var _Modals_GhostChooser__WEBPACK_IMPORTED_MODULE_7__ = __webpack_require__(/*! ../Modals/GhostChooser */ "./src/Renderer/components/Modals/GhostChooser/index.js");
/* harmony import */ var _Support__WEBPACK_IMPORTED_MODULE_8__ = __webpack_require__(/*! ../Support */ "./src/Renderer/components/Support/index.js");










const styles = theme => ({
  root: {
    marginBottom: theme.spacing.unit * 3,
    flexGrow: 1
  },
  appBar: {
    top: 'auto',
    height: 39,
    bottom: 0,
    backgroundImage: `url(${"./static/img/bottom-bar.png"})`,
    backgroundSize: 'cover',
    backgroundPosition: 'center'
  },
  right: {
    float: 'right'
  }
});

function BottomToolbar(props) {
  const {
    classes,
    status,
    milling
  } = props;

  function openGhostGunnerNet() {
    electron__WEBPACK_IMPORTED_MODULE_4__["shell"].openExternal("https://ghostgunner.net/");
  }

  return react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("footer", {
    className: classes.root
  }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_3__["AppBar"], {
    position: "fixed",
    className: classes.appBar
  }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_3__["Toolbar"], null, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_3__["Grid"], {
    container: true,
    spacing: 0,
    className: classes.root,
    alignItems: "center"
  }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_3__["Grid"], {
    item: true,
    xs: 4
  }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_Status__WEBPACK_IMPORTED_MODULE_5__["default"], {
    status: status
  }), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_Modals_GhostChooser__WEBPACK_IMPORTED_MODULE_7__["default"], {
    disabled: milling
  })), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_3__["Grid"], {
    item: true,
    xs: 8
  }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("div", {
    className: classes.right
  }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_3__["Button"], {
    color: "secondary",
    onClick: openGhostGunnerNet
  }, "GhostGunner.net"), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_Modals_Settings__WEBPACK_IMPORTED_MODULE_6__["default"], {
    disabled: milling
  }), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_Support__WEBPACK_IMPORTED_MODULE_8__["default"], {
    disabled: milling
  })))))));
}

BottomToolbar.propTypes = {
  classes: prop_types__WEBPACK_IMPORTED_MODULE_1___default.a.object.isRequired,
  status: prop_types__WEBPACK_IMPORTED_MODULE_1___default.a.number.isRequired,
  milling: prop_types__WEBPACK_IMPORTED_MODULE_1___default.a.bool.isRequired
};
/* harmony default export */ __webpack_exports__["default"] = (Object(_material_ui_core_styles__WEBPACK_IMPORTED_MODULE_2__["withStyles"])(styles)(BottomToolbar));

/***/ }),

/***/ "./src/Renderer/components/BottomToolbar/index.js":
/*!********************************************************!*\
  !*** ./src/Renderer/components/BottomToolbar/index.js ***!
  \********************************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony import */ var _BottomToolbar__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ./BottomToolbar */ "./src/Renderer/components/BottomToolbar/BottomToolbar.js");

/* harmony default export */ __webpack_exports__["default"] = (_BottomToolbar__WEBPACK_IMPORTED_MODULE_0__["default"]);

/***/ }),

/***/ "./src/Renderer/components/ImageRaw/ImageRaw.js":
/*!******************************************************!*\
  !*** ./src/Renderer/components/ImageRaw/ImageRaw.js ***!
  \******************************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony import */ var react__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! react */ "react");
/* harmony import */ var react__WEBPACK_IMPORTED_MODULE_0___default = /*#__PURE__*/__webpack_require__.n(react__WEBPACK_IMPORTED_MODULE_0__);
/* harmony import */ var prop_types__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! prop-types */ "prop-types");
/* harmony import */ var prop_types__WEBPACK_IMPORTED_MODULE_1___default = /*#__PURE__*/__webpack_require__.n(prop_types__WEBPACK_IMPORTED_MODULE_1__);
/* harmony import */ var electron__WEBPACK_IMPORTED_MODULE_2__ = __webpack_require__(/*! electron */ "electron");
/* harmony import */ var electron__WEBPACK_IMPORTED_MODULE_2___default = /*#__PURE__*/__webpack_require__.n(electron__WEBPACK_IMPORTED_MODULE_2__);
/* harmony import */ var _material_ui_core_styles__WEBPACK_IMPORTED_MODULE_3__ = __webpack_require__(/*! @material-ui/core/styles */ "@material-ui/core/styles");
/* harmony import */ var _material_ui_core_styles__WEBPACK_IMPORTED_MODULE_3___default = /*#__PURE__*/__webpack_require__.n(_material_ui_core_styles__WEBPACK_IMPORTED_MODULE_3__);
/* harmony import */ var _material_ui_core__WEBPACK_IMPORTED_MODULE_4__ = __webpack_require__(/*! @material-ui/core */ "@material-ui/core");
/* harmony import */ var _material_ui_core__WEBPACK_IMPORTED_MODULE_4___default = /*#__PURE__*/__webpack_require__.n(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__);






const styles = theme => ({
  root: {
    width: '100%',
    height: '100%'
  },
  gcodes: {
    width: '100%',
    height: 'calc(100% - 50px)',
    overflow: 'auto',
    backgroundColor: 'black',
    position: 'relative',
    border: '#FFFFFF 1px solid'
  }
});

class ImageRaw extends react__WEBPACK_IMPORTED_MODULE_0___default.a.Component {
  constructor() {
    super();
    this.state = {
      imageSelected: true,
      readWrites: []
    };
    this.gcodeEnd = null;
    this.updateReadWrites = this.updateReadWrites.bind(this);
  }

  shouldComponentUpdate(nextProps, nextState) {
    if (this.props.selectedStep != nextProps.selectedStep) {
      return true;
    } else if (this.state.imageSelected != nextState.imageSelected) {
      return true;
    } else if (this.props.millingInProgress != nextProps.millingInProgress) {
      return true;
    } else if (this.state.readWrites != nextState.readWrites) {
      return true;
    }

    return false;
  }

  componentDidUpdate(prevProps) {
    if (this.props.selectedStep !== prevProps.selectedStep) {
      this.setState({
        imageSelected: true,
        readWrites: []
      });
    }
  }

  updateReadWrites(event, newLines) {
    if (newLines.length > 0) {
      this.setState({
        readWrites: [...this.state.readWrites, ...newLines]
      });
    }
  }

  render() {
    const {
      classes,
      selectedStep,
      millingInProgress
    } = this.props;
    electron__WEBPACK_IMPORTED_MODULE_2__["ipcRenderer"].removeAllListeners("Jobs::ReadWrites");
    electron__WEBPACK_IMPORTED_MODULE_2__["ipcRenderer"].on("Jobs::ReadWrites", this.updateReadWrites);

    function getGCodeDisplay(milling, readWrites) {
      if (milling) {
        return readWrites.map((readWrite, index) => {
          return react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["Typography"], {
            key: index,
            align: "left",
            style: {
              marginLeft: '10px'
            }
          }, readWrite.TYPE, " : ", readWrite.VALUE);
        });
      } else {
        var gcodes = [];

        if (selectedStep.GCode != null) {
          gcodes = selectedStep.GCode;
        }

        return gcodes.map((gcode, index) => {
          return react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["Typography"], {
            key: index,
            align: "left",
            style: {
              marginLeft: '10px'
            }
          }, gcode);
        });
      }
    }

    function getDisplay(component) {
      if (component.state.imageSelected == true) {
        return react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("img", {
          style: {
            width: '100%',
            height: 'auto'
          },
          src: 'data:image/jpeg;base64,' + selectedStep.Image
        });
      } else {
        return react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("div", {
          className: classes.gcodes
        }, getGCodeDisplay(millingInProgress, component.state.readWrites), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("div", {
          style: {
            float: "left",
            clear: "both"
          },
          ref: el => {
            component.gcodeEnd = el;
          }
        }));
      }
    }

    function onClickImage(event) {
      this.setState({
        imageSelected: true
      });
    }

    function onClickRaw(event) {
      if (selectedStep.GCode != null) {
        this.setState({
          imageSelected: false
        });
      }
    }

    function scrollToBottom(component) {
      if (millingInProgress && component.gcodeEnd != null && !component.state.imageSelected) {
        component.gcodeEnd.scrollIntoView({
          behavior: "auto",
          block: 'center'
        });
      }
    }

    return react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("div", {
      className: classes.root
    }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["Grid"], {
      container: true,
      spacing: 0
    }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["Grid"], {
      item: true,
      xs: 3
    }), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["Grid"], {
      item: true,
      xs: 3
    }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["Button"], {
      fullWidth: true,
      variant: "contained",
      color: this.state.imageSelected === true ? "secondary" : "primary",
      size: "small",
      onClick: onClickImage.bind(this),
      style: {
        borderRadius: '0px',
        padding: '0px'
      }
    }, "IMAGE")), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["Grid"], {
      item: true,
      xs: 3
    }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["Button"], {
      fullWidth: true,
      variant: "contained",
      color: this.state.imageSelected === true ? "primary" : "secondary",
      size: "small",
      onClick: onClickRaw.bind(this),
      style: {
        borderRadius: '0px',
        padding: '0px'
      }
    }, "RAW")), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["Grid"], {
      item: true,
      xs: 3
    })), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("br", null), getDisplay(this), scrollToBottom(this));
  }

}

;
ImageRaw.propTypes = {
  classes: prop_types__WEBPACK_IMPORTED_MODULE_1___default.a.object.isRequired,
  selectedStep: prop_types__WEBPACK_IMPORTED_MODULE_1___default.a.object.isRequired,
  millingInProgress: prop_types__WEBPACK_IMPORTED_MODULE_1___default.a.bool.isRequired
};
/* harmony default export */ __webpack_exports__["default"] = (Object(_material_ui_core_styles__WEBPACK_IMPORTED_MODULE_3__["withStyles"])(styles)(ImageRaw));

/***/ }),

/***/ "./src/Renderer/components/ImageRaw/index.js":
/*!***************************************************!*\
  !*** ./src/Renderer/components/ImageRaw/index.js ***!
  \***************************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony import */ var _ImageRaw__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ./ImageRaw */ "./src/Renderer/components/ImageRaw/ImageRaw.js");

/* harmony default export */ __webpack_exports__["default"] = (_ImageRaw__WEBPACK_IMPORTED_MODULE_0__["default"]);

/***/ }),

/***/ "./src/Renderer/components/Menu/Menu.js":
/*!**********************************************!*\
  !*** ./src/Renderer/components/Menu/Menu.js ***!
  \**********************************************/
/*! exports provided: Menu, default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "Menu", function() { return Menu; });
/* harmony import */ var react__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! react */ "react");
/* harmony import */ var react__WEBPACK_IMPORTED_MODULE_0___default = /*#__PURE__*/__webpack_require__.n(react__WEBPACK_IMPORTED_MODULE_0__);

class Menu extends react__WEBPACK_IMPORTED_MODULE_0__["Component"] {
  render() {
    return react__WEBPACK_IMPORTED_MODULE_0__["createElement"]("div", {
      id: "MainMenu"
    });
  }

}
/* harmony default export */ __webpack_exports__["default"] = (Menu);

/***/ }),

/***/ "./src/Renderer/components/Menu/index.js":
/*!***********************************************!*\
  !*** ./src/Renderer/components/Menu/index.js ***!
  \***********************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony import */ var _Menu__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ./Menu */ "./src/Renderer/components/Menu/Menu.js");

/* harmony default export */ __webpack_exports__["default"] = (_Menu__WEBPACK_IMPORTED_MODULE_0__["default"]);

/***/ }),

/***/ "./src/Renderer/components/Modals/Alert/Alert.js":
/*!*******************************************************!*\
  !*** ./src/Renderer/components/Modals/Alert/Alert.js ***!
  \*******************************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony import */ var react__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! react */ "react");
/* harmony import */ var react__WEBPACK_IMPORTED_MODULE_0___default = /*#__PURE__*/__webpack_require__.n(react__WEBPACK_IMPORTED_MODULE_0__);
/* harmony import */ var prop_types__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! prop-types */ "prop-types");
/* harmony import */ var prop_types__WEBPACK_IMPORTED_MODULE_1___default = /*#__PURE__*/__webpack_require__.n(prop_types__WEBPACK_IMPORTED_MODULE_1__);
/* harmony import */ var _material_ui_core_styles_withStyles__WEBPACK_IMPORTED_MODULE_2__ = __webpack_require__(/*! @material-ui/core/styles/withStyles */ "@material-ui/core/styles/withStyles");
/* harmony import */ var _material_ui_core_styles_withStyles__WEBPACK_IMPORTED_MODULE_2___default = /*#__PURE__*/__webpack_require__.n(_material_ui_core_styles_withStyles__WEBPACK_IMPORTED_MODULE_2__);
/* harmony import */ var electron__WEBPACK_IMPORTED_MODULE_3__ = __webpack_require__(/*! electron */ "electron");
/* harmony import */ var electron__WEBPACK_IMPORTED_MODULE_3___default = /*#__PURE__*/__webpack_require__.n(electron__WEBPACK_IMPORTED_MODULE_3__);
/* harmony import */ var _material_ui_core__WEBPACK_IMPORTED_MODULE_4__ = __webpack_require__(/*! @material-ui/core */ "@material-ui/core");
/* harmony import */ var _material_ui_core__WEBPACK_IMPORTED_MODULE_4___default = /*#__PURE__*/__webpack_require__.n(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__);






const styles = theme => ({
  cancel: {
    marginTop: -theme.spacing.unit,
    marginBottom: theme.spacing.unit
  },
  select: {
    marginTop: -theme.spacing.unit,
    marginBottom: theme.spacing.unit
  },
  ghostList: {
    width: "100%"
  },
  switch: {
    marginLeft: -2 * theme.spacing.unit
  }
});

function Alert(props) {
  const {
    classes,
    open,
    message,
    close
  } = props;
  return react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(react__WEBPACK_IMPORTED_MODULE_0___default.a.Fragment, null, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["Dialog"], {
    open: open,
    "aria-labelledby": "form-dialog-title",
    maxWidth: "xs",
    fullWidth: true
  }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["DialogContent"], null, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["Typography"], null, message), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("br", null)), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["DialogActions"], null, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["Button"], {
    variant: "contained",
    className: classes.select,
    color: "secondary",
    onClick: close
  }, "OK"))));
}

Alert.propTypes = {
  classes: prop_types__WEBPACK_IMPORTED_MODULE_1___default.a.object.isRequired,
  open: prop_types__WEBPACK_IMPORTED_MODULE_1___default.a.bool.isRequired,
  message: prop_types__WEBPACK_IMPORTED_MODULE_1___default.a.string.isRequired,
  close: prop_types__WEBPACK_IMPORTED_MODULE_1___default.a.func.isRequired
};
/* harmony default export */ __webpack_exports__["default"] = (_material_ui_core_styles_withStyles__WEBPACK_IMPORTED_MODULE_2___default()(styles)(Alert));

/***/ }),

/***/ "./src/Renderer/components/Modals/Alert/index.js":
/*!*******************************************************!*\
  !*** ./src/Renderer/components/Modals/Alert/index.js ***!
  \*******************************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony import */ var _Alert__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ./Alert */ "./src/Renderer/components/Modals/Alert/Alert.js");

/* harmony default export */ __webpack_exports__["default"] = (_Alert__WEBPACK_IMPORTED_MODULE_0__["default"]);

/***/ }),

/***/ "./src/Renderer/components/Modals/CustomerSupport/CustomerSupport.js":
/*!***************************************************************************!*\
  !*** ./src/Renderer/components/Modals/CustomerSupport/CustomerSupport.js ***!
  \***************************************************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony import */ var react__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! react */ "react");
/* harmony import */ var react__WEBPACK_IMPORTED_MODULE_0___default = /*#__PURE__*/__webpack_require__.n(react__WEBPACK_IMPORTED_MODULE_0__);
/* harmony import */ var prop_types__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! prop-types */ "prop-types");
/* harmony import */ var prop_types__WEBPACK_IMPORTED_MODULE_1___default = /*#__PURE__*/__webpack_require__.n(prop_types__WEBPACK_IMPORTED_MODULE_1__);
/* harmony import */ var _material_ui_core_styles_withStyles__WEBPACK_IMPORTED_MODULE_2__ = __webpack_require__(/*! @material-ui/core/styles/withStyles */ "@material-ui/core/styles/withStyles");
/* harmony import */ var _material_ui_core_styles_withStyles__WEBPACK_IMPORTED_MODULE_2___default = /*#__PURE__*/__webpack_require__.n(_material_ui_core_styles_withStyles__WEBPACK_IMPORTED_MODULE_2__);
/* harmony import */ var electron__WEBPACK_IMPORTED_MODULE_3__ = __webpack_require__(/*! electron */ "electron");
/* harmony import */ var electron__WEBPACK_IMPORTED_MODULE_3___default = /*#__PURE__*/__webpack_require__.n(electron__WEBPACK_IMPORTED_MODULE_3__);
/* harmony import */ var _material_ui_core__WEBPACK_IMPORTED_MODULE_4__ = __webpack_require__(/*! @material-ui/core */ "@material-ui/core");
/* harmony import */ var _material_ui_core__WEBPACK_IMPORTED_MODULE_4___default = /*#__PURE__*/__webpack_require__.n(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__);






const styles = theme => ({
  cancel: {
    marginTop: -theme.spacing.unit,
    marginBottom: theme.spacing.unit
  },
  send: {
    marginTop: -theme.spacing.unit,
    marginBottom: theme.spacing.unit
  },
  emailText: {
    width: '100%',
    height: 30,
    marginTop: 0
  }
});

function CustomerSupport(props) {
  const {
    classes,
    open,
    onClose
  } = props;
  const [errors, setErrors] = react__WEBPACK_IMPORTED_MODULE_0___default.a.useState(new Array());
  const [email, setEmail] = react__WEBPACK_IMPORTED_MODULE_0___default.a.useState("");
  const [description, setDescription] = react__WEBPACK_IMPORTED_MODULE_0___default.a.useState("");
  const [includeLogs, setIncludeLogs] = react__WEBPACK_IMPORTED_MODULE_0___default.a.useState(false);

  function handleClose(event) {
    setErrors(new Array());
    setEmail("");
    setDescription("");
    setIncludeLogs(false);
    onClose(event);
  }

  function handleSend(event) {
    const error = electron__WEBPACK_IMPORTED_MODULE_3__["ipcRenderer"].sendSync("Support::SendRequest", email, description, includeLogs);

    if (error == null) {
      handleClose(null);
    } else {
      console.log(error);
      var errorsArray = new Array();

      if (error.hasOwnProperty("name")) {
        errorsArray.push("NAME: " + error.name);
      }

      if (error.hasOwnProperty("email")) {
        errorsArray.push("EMAIL: " + error.email);
      }

      if (error.hasOwnProperty("description")) {
        errorsArray.push("DESCRIPTION: " + error.description);
      }

      setErrors(errorsArray);
    }
  }

  console.log(errors);
  return react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["Dialog"], {
    open: open,
    "aria-labelledby": "form-dialog-title",
    style: {
      overflow: 'none'
    },
    maxWidth: "sm",
    fullWidth: true
  }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["DialogTitle"], null, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("center", null, "Customer Support Request")), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["DialogContent"], {
    style: {
      overflowX: 'hidden'
    }
  }, errors.map((error, index) => {
    return react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["Typography"], {
      color: "error"
    }, error);
  }), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("br", null), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["Grid"], {
    container: true,
    spacing: 8,
    justify: "center"
  }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["Grid"], {
    item: true,
    xs: 3
  }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["Typography"], {
    inline: true,
    style: {
      lineHeight: '30px'
    }
  }, " Your e-mail address:")), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["Grid"], {
    item: true,
    xs: 9
  }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["TextField"], {
    margin: "normal",
    variant: "outlined",
    className: classes.emailText,
    onChange: e => setEmail(e.currentTarget.value)
  }))), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["TextField"], {
    margin: "normal",
    variant: "outlined",
    placeholder: "Please enter a description of your problem.",
    rows: 4,
    fullWidth: true,
    multiline: true,
    onChange: e => setDescription(e.currentTarget.value)
  }), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("br", null), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["FormControlLabel"], {
    control: react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["Checkbox"], {
      checked: includeLogs,
      onChange: e => {
        setIncludeLogs(e.currentTarget.checked);
      }
    }),
    label: "Include logs and data that might help us solve your problem."
  }), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("br", null)), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["DialogActions"], null, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["Grid"], {
    container: true,
    spacing: 8,
    justify: "center"
  }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["Grid"], {
    item: true,
    xs: 3
  }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["Button"], {
    variant: "contained",
    className: classes.cancel,
    onClick: handleClose,
    fullWidth: true
  }, "CANCEL")), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["Grid"], {
    item: true,
    xs: 3
  }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["Button"], {
    variant: "contained",
    className: classes.send,
    color: "secondary",
    onClick: handleSend,
    fullWidth: true
  }, "SEND REPORT")))));
}

CustomerSupport.propTypes = {
  classes: prop_types__WEBPACK_IMPORTED_MODULE_1___default.a.object.isRequired,
  open: prop_types__WEBPACK_IMPORTED_MODULE_1___default.a.bool.isRequired,
  onClose: prop_types__WEBPACK_IMPORTED_MODULE_1___default.a.func
};
/* harmony default export */ __webpack_exports__["default"] = (_material_ui_core_styles_withStyles__WEBPACK_IMPORTED_MODULE_2___default()(styles)(CustomerSupport));

/***/ }),

/***/ "./src/Renderer/components/Modals/CustomerSupport/index.js":
/*!*****************************************************************!*\
  !*** ./src/Renderer/components/Modals/CustomerSupport/index.js ***!
  \*****************************************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony import */ var _CustomerSupport__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ./CustomerSupport */ "./src/Renderer/components/Modals/CustomerSupport/CustomerSupport.js");

/* harmony default export */ __webpack_exports__["default"] = (_CustomerSupport__WEBPACK_IMPORTED_MODULE_0__["default"]);

/***/ }),

/***/ "./src/Renderer/components/Modals/GhostChooser/GhostChooser.js":
/*!*********************************************************************!*\
  !*** ./src/Renderer/components/Modals/GhostChooser/GhostChooser.js ***!
  \*********************************************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony import */ var react__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! react */ "react");
/* harmony import */ var react__WEBPACK_IMPORTED_MODULE_0___default = /*#__PURE__*/__webpack_require__.n(react__WEBPACK_IMPORTED_MODULE_0__);
/* harmony import */ var prop_types__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! prop-types */ "prop-types");
/* harmony import */ var prop_types__WEBPACK_IMPORTED_MODULE_1___default = /*#__PURE__*/__webpack_require__.n(prop_types__WEBPACK_IMPORTED_MODULE_1__);
/* harmony import */ var _material_ui_core_styles_withStyles__WEBPACK_IMPORTED_MODULE_2__ = __webpack_require__(/*! @material-ui/core/styles/withStyles */ "@material-ui/core/styles/withStyles");
/* harmony import */ var _material_ui_core_styles_withStyles__WEBPACK_IMPORTED_MODULE_2___default = /*#__PURE__*/__webpack_require__.n(_material_ui_core_styles_withStyles__WEBPACK_IMPORTED_MODULE_2__);
/* harmony import */ var electron__WEBPACK_IMPORTED_MODULE_3__ = __webpack_require__(/*! electron */ "electron");
/* harmony import */ var electron__WEBPACK_IMPORTED_MODULE_3___default = /*#__PURE__*/__webpack_require__.n(electron__WEBPACK_IMPORTED_MODULE_3__);
/* harmony import */ var _material_ui_core__WEBPACK_IMPORTED_MODULE_4__ = __webpack_require__(/*! @material-ui/core */ "@material-ui/core");
/* harmony import */ var _material_ui_core__WEBPACK_IMPORTED_MODULE_4___default = /*#__PURE__*/__webpack_require__.n(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__);






const styles = theme => ({
  cancel: {
    marginTop: -theme.spacing.unit,
    marginBottom: theme.spacing.unit
  },
  select: {
    marginTop: -theme.spacing.unit,
    marginBottom: theme.spacing.unit
  },
  ghostList: {
    width: "100%"
  },
  switch: {
    marginLeft: -2 * theme.spacing.unit
  }
});

function GhostChooser(props) {
  const {
    classes,
    disabled
  } = props;
  const [open, setOpen] = react__WEBPACK_IMPORTED_MODULE_0___default.a.useState(false);
  const [availableGhosts, setAvailableGhosts] = react__WEBPACK_IMPORTED_MODULE_0___default.a.useState(null);
  const [selectedGhost, setSelectedGhost] = react__WEBPACK_IMPORTED_MODULE_0___default.a.useState(-1);

  function handleSelect(event) {
    if (selectedGhost >= 0) {
      electron__WEBPACK_IMPORTED_MODULE_3__["ipcRenderer"].send("Ghost::ChooseGhost", availableGhosts[selectedGhost].path, availableGhosts[selectedGhost].serial_number);
    }

    setOpen(false);
  }

  function handleClickOpen(event) {
    const available = electron__WEBPACK_IMPORTED_MODULE_3__["ipcRenderer"].sendSync("Ghost::GetAvailableGhosts");
    console.log(available);
    setAvailableGhosts(available);

    for (var i = 0; i < available.length; i++) {
      if (available[i].selected == true) {
        setSelectedGhost(i);
      }
    }

    setOpen(true);
  }

  function handleClose(event) {
    setOpen(false);
  }

  function handleSelectGhost(event) {
    setSelectedGhost(event.target.selectedIndex);
  }

  function getGhostOptions() {
    if (availableGhosts != null) {
      const options = availableGhosts.map((ghost, index) => {
        return react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("option", {
          key: index
        }, " SN: ", ghost.serial_number, " PATH: ", ghost.path);
      });
      return options;
    }

    return null;
  }

  function getSwitchButton() {
    if (!disabled) {
      return react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["Button"], {
        color: "secondary",
        onClick: handleClickOpen,
        className: classes.switch
      }, "(Switch)");
    }

    return null;
  }

  return react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(react__WEBPACK_IMPORTED_MODULE_0___default.a.Fragment, null, getSwitchButton(), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["Dialog"], {
    open: open,
    "aria-labelledby": "form-dialog-title",
    maxWidth: "sm",
    fullWidth: true
  }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["DialogTitle"], null, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("center", null, "Choose Ghost Gunner")), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["DialogContent"], null, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["Typography"], null, "Select a Ghost Gunner."), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("select", {
    size: "5",
    onChange: handleSelectGhost,
    className: classes.ghostList,
    value: selectedGhost
  }, getGhostOptions()), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("br", null)), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["DialogActions"], null, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["Grid"], {
    container: true,
    spacing: 8,
    justify: "center"
  }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["Grid"], {
    item: true,
    xs: 3
  }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["Button"], {
    variant: "contained",
    className: classes.cancel,
    onClick: handleClose,
    fullWidth: true
  }, "CANCEL")), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["Grid"], {
    item: true,
    xs: 3
  }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["Button"], {
    variant: "contained",
    className: classes.select,
    color: "secondary",
    onClick: handleSelect,
    fullWidth: true
  }, "SELECT"))))));
}

GhostChooser.propTypes = {
  classes: prop_types__WEBPACK_IMPORTED_MODULE_1___default.a.object.isRequired,
  disabled: prop_types__WEBPACK_IMPORTED_MODULE_1___default.a.bool.isRequired
};
/* harmony default export */ __webpack_exports__["default"] = (_material_ui_core_styles_withStyles__WEBPACK_IMPORTED_MODULE_2___default()(styles)(GhostChooser));

/***/ }),

/***/ "./src/Renderer/components/Modals/GhostChooser/index.js":
/*!**************************************************************!*\
  !*** ./src/Renderer/components/Modals/GhostChooser/index.js ***!
  \**************************************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony import */ var _GhostChooser__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ./GhostChooser */ "./src/Renderer/components/Modals/GhostChooser/GhostChooser.js");

/* harmony default export */ __webpack_exports__["default"] = (_GhostChooser__WEBPACK_IMPORTED_MODULE_0__["default"]);

/***/ }),

/***/ "./src/Renderer/components/Modals/JobSelection/JobSelection.js":
/*!*********************************************************************!*\
  !*** ./src/Renderer/components/Modals/JobSelection/JobSelection.js ***!
  \*********************************************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony import */ var react__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! react */ "react");
/* harmony import */ var react__WEBPACK_IMPORTED_MODULE_0___default = /*#__PURE__*/__webpack_require__.n(react__WEBPACK_IMPORTED_MODULE_0__);
/* harmony import */ var prop_types__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! prop-types */ "prop-types");
/* harmony import */ var prop_types__WEBPACK_IMPORTED_MODULE_1___default = /*#__PURE__*/__webpack_require__.n(prop_types__WEBPACK_IMPORTED_MODULE_1__);
/* harmony import */ var _material_ui_core_styles_withStyles__WEBPACK_IMPORTED_MODULE_2__ = __webpack_require__(/*! @material-ui/core/styles/withStyles */ "@material-ui/core/styles/withStyles");
/* harmony import */ var _material_ui_core_styles_withStyles__WEBPACK_IMPORTED_MODULE_2___default = /*#__PURE__*/__webpack_require__.n(_material_ui_core_styles_withStyles__WEBPACK_IMPORTED_MODULE_2__);
/* harmony import */ var electron__WEBPACK_IMPORTED_MODULE_3__ = __webpack_require__(/*! electron */ "electron");
/* harmony import */ var electron__WEBPACK_IMPORTED_MODULE_3___default = /*#__PURE__*/__webpack_require__.n(electron__WEBPACK_IMPORTED_MODULE_3__);
/* harmony import */ var _material_ui_core__WEBPACK_IMPORTED_MODULE_4__ = __webpack_require__(/*! @material-ui/core */ "@material-ui/core");
/* harmony import */ var _material_ui_core__WEBPACK_IMPORTED_MODULE_4___default = /*#__PURE__*/__webpack_require__.n(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__);






const styles = theme => ({
  cancel: {
    marginTop: -theme.spacing.unit,
    marginBottom: theme.spacing.unit
  },
  select: {
    marginTop: -theme.spacing.unit,
    marginBottom: theme.spacing.unit
  },
  jobList: {
    width: "100%"
  },
  jobText: {
    width: "calc(100% - 6px)"
  }
});

function JobSelection(props) {
  const {
    classes,
    open,
    onClose,
    jobs
  } = props;
  const [selectedJob, setSelectedJob] = react__WEBPACK_IMPORTED_MODULE_0___default.a.useState(0);

  function handleSelect(event) {
    electron__WEBPACK_IMPORTED_MODULE_3__["ipcRenderer"].send("Jobs::SelectJob", selectedJob);
    onClose(event);
  }

  function handleClose(event) {
    onClose(event);
  }

  function handleSelectJob(event) {
    setSelectedJob(event.target.selectedIndex);
  }

  function getJobText() {
    if (selectedJob >= 0 && jobs.length > selectedJob) {
      return jobs[selectedJob].prompt;
    }

    return "";
  }

  return react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["Dialog"], {
    open: open,
    "aria-labelledby": "form-dialog-title",
    maxWidth: "sm",
    fullWidth: true
  }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["DialogTitle"], null, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("center", null, "Job Selection")), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["DialogContent"], null, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["Typography"], null, "Select job to continue."), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("select", {
    size: "5",
    onChange: handleSelectJob,
    className: classes.jobList
  }, jobs.map((job, index) => {
    return react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("option", {
      key: index
    }, job.title);
  })), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("br", null), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("br", null), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("textarea", {
    type: "text",
    disabled: true,
    rows: "6",
    cols: "78",
    value: getJobText(),
    className: classes.jobText
  }), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("br", null)), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["DialogActions"], null, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["Grid"], {
    container: true,
    spacing: 8,
    justify: "center"
  }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["Grid"], {
    item: true,
    xs: 3
  }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["Button"], {
    variant: "contained",
    className: classes.cancel,
    onClick: handleClose,
    fullWidth: true
  }, "CANCEL")), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["Grid"], {
    item: true,
    xs: 3
  }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["Button"], {
    variant: "contained",
    className: classes.select,
    color: "secondary",
    onClick: handleSelect,
    fullWidth: true
  }, "SELECT")))));
}

JobSelection.propTypes = {
  classes: prop_types__WEBPACK_IMPORTED_MODULE_1___default.a.object.isRequired,
  open: prop_types__WEBPACK_IMPORTED_MODULE_1___default.a.bool.isRequired,
  onClose: prop_types__WEBPACK_IMPORTED_MODULE_1___default.a.func,
  jobs: prop_types__WEBPACK_IMPORTED_MODULE_1___default.a.array.isRequired
};
/* harmony default export */ __webpack_exports__["default"] = (_material_ui_core_styles_withStyles__WEBPACK_IMPORTED_MODULE_2___default()(styles)(JobSelection));

/***/ }),

/***/ "./src/Renderer/components/Modals/JobSelection/index.js":
/*!**************************************************************!*\
  !*** ./src/Renderer/components/Modals/JobSelection/index.js ***!
  \**************************************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony import */ var _JobSelection__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ./JobSelection */ "./src/Renderer/components/Modals/JobSelection/JobSelection.js");

/* harmony default export */ __webpack_exports__["default"] = (_JobSelection__WEBPACK_IMPORTED_MODULE_0__["default"]);

/***/ }),

/***/ "./src/Renderer/components/Modals/Settings/Settings.js":
/*!*************************************************************!*\
  !*** ./src/Renderer/components/Modals/Settings/Settings.js ***!
  \*************************************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony import */ var react__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! react */ "react");
/* harmony import */ var react__WEBPACK_IMPORTED_MODULE_0___default = /*#__PURE__*/__webpack_require__.n(react__WEBPACK_IMPORTED_MODULE_0__);
/* harmony import */ var prop_types__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! prop-types */ "prop-types");
/* harmony import */ var prop_types__WEBPACK_IMPORTED_MODULE_1___default = /*#__PURE__*/__webpack_require__.n(prop_types__WEBPACK_IMPORTED_MODULE_1__);
/* harmony import */ var _material_ui_core__WEBPACK_IMPORTED_MODULE_2__ = __webpack_require__(/*! @material-ui/core */ "@material-ui/core");
/* harmony import */ var _material_ui_core__WEBPACK_IMPORTED_MODULE_2___default = /*#__PURE__*/__webpack_require__.n(_material_ui_core__WEBPACK_IMPORTED_MODULE_2__);
/* harmony import */ var path__WEBPACK_IMPORTED_MODULE_3__ = __webpack_require__(/*! path */ "path");
/* harmony import */ var path__WEBPACK_IMPORTED_MODULE_3___default = /*#__PURE__*/__webpack_require__.n(path__WEBPACK_IMPORTED_MODULE_3__);
/* harmony import */ var _material_ui_core_styles__WEBPACK_IMPORTED_MODULE_4__ = __webpack_require__(/*! @material-ui/core/styles */ "@material-ui/core/styles");
/* harmony import */ var _material_ui_core_styles__WEBPACK_IMPORTED_MODULE_4___default = /*#__PURE__*/__webpack_require__.n(_material_ui_core_styles__WEBPACK_IMPORTED_MODULE_4__);
/* harmony import */ var electron__WEBPACK_IMPORTED_MODULE_5__ = __webpack_require__(/*! electron */ "electron");
/* harmony import */ var electron__WEBPACK_IMPORTED_MODULE_5___default = /*#__PURE__*/__webpack_require__.n(electron__WEBPACK_IMPORTED_MODULE_5__);







const styles = theme => ({
  settingsButton: {
    paddingTop: 0,
    paddingBottom: 0,
    paddingLeft: theme.spacing.unit,
    paddingRight: theme.spacing.unit,
    backgroundColor: "transparent"
  },
  settingsCog: {
    width: '25px',
    height: '25px',
    marginRight: theme.spacing.unit,
    padding: 0,
    marginTop: 0
  },
  settingsText: {
    width: '62px',
    height: '28px',
    objectFit: 'contain',
    padding: 0,
    margin: 0
  },
  timeoutText: {
    width: 100,
    height: 30,
    marginLeft: theme.spacing.unit * 2,
    marginRight: theme.spacing.unit * 2,
    marginTop: theme.spacing.unit
  },
  cancel: {
    marginRight: theme.spacing.unit
  },
  save: {
    marginLeft: theme.spacing.unit
  },
  radio: {
    marginLeft: theme.spacing.unit,
    marginTop: 0,
    marginBottom: 0
  },
  radioGroup: {
    width: "100%",
    backgroundColor: "black",
    borderStyle: "solid",
    borderColor: "white",
    borderWidth: "2px",
    borderRadius: "2px"
  },
  feedRatePercentage: {
    marginLeft: theme.spacing.unit,
    padding: theme.spacing.unit,
    backgroundColor: "black"
  }
});

function Settings(props) {
  const {
    classes,
    disabled
  } = props;
  const [open, setOpen] = react__WEBPACK_IMPORTED_MODULE_0___default.a.useState(false);
  const [pause, setPause] = react__WEBPACK_IMPORTED_MODULE_0___default.a.useState(false);
  const [timeout, setTimeout] = react__WEBPACK_IMPORTED_MODULE_0___default.a.useState(0);
  const [enableSlider, setEnableSlider] = react__WEBPACK_IMPORTED_MODULE_0___default.a.useState(false);
  const [maxFeedRate, setMaxFeedRate] = react__WEBPACK_IMPORTED_MODULE_0___default.a.useState(0);
  const [ddVersion, setDDVersion] = react__WEBPACK_IMPORTED_MODULE_0___default.a.useState("");
  const [grblVersion, setGrblVersion] = react__WEBPACK_IMPORTED_MODULE_0___default.a.useState("");

  function handleClickOpen() {
    if (!disabled) {
      setOpen(true);
      var settings = electron__WEBPACK_IMPORTED_MODULE_5__["ipcRenderer"].sendSync("Settings::GetSettings");
      setPause(settings.pauseAfterGCode);
      setTimeout(settings.timeout);
      setEnableSlider(settings.enable_slider);
      setMaxFeedRate(settings.maxFeedRate);
      var firmware = electron__WEBPACK_IMPORTED_MODULE_5__["ipcRenderer"].sendSync("Firmware::GetFirmwareVersion");
      setDDVersion(firmware.ddVersion);
      setGrblVersion(firmware.grblVersion);
    }
  }

  function handleClose() {
    setOpen(false);
  }

  function handleSave() {
    electron__WEBPACK_IMPORTED_MODULE_5__["ipcRenderer"].send("Settings::UpdateSettings", pause, timeout, enableSlider, maxFeedRate);
    setOpen(false);
  }

  function getVersionDisplay() {
    if (ddVersion == "") {
      return "Not Connected";
    }

    return "DD: " + ddVersion + " GRBL: " + grblVersion;
  }

  return react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(react__WEBPACK_IMPORTED_MODULE_0___default.a.Fragment, null, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_2__["Fab"], {
    variant: "extended",
    "aria-label": "Settings",
    disabled: disabled,
    onClick: handleClickOpen,
    className: classes.settingsButton,
    size: "small",
    id: "settings"
  }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("img", {
    src: path__WEBPACK_IMPORTED_MODULE_3___default.a.join(__dirname, '../../../static/img/settings-cog.png'),
    className: classes.settingsCog
  }), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("img", {
    src: path__WEBPACK_IMPORTED_MODULE_3___default.a.join(__dirname, '../../../static/img/settings.png'),
    className: classes.settingsText
  })), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_2__["Dialog"], {
    open: open,
    onClose: handleClose,
    "aria-labelledby": "form-dialog-title",
    maxWidth: "sm",
    PaperProps: {
      className: classes.paper
    }
  }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_2__["DialogTitle"], {
    id: "form-dialog-title"
  }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("center", null, "Settings")), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_2__["DialogContent"], null, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_2__["FormControlLabel"], {
    control: react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_2__["Checkbox"], {
      checked: pause,
      onChange: e => setPause(e.currentTarget.checked)
    }),
    label: "Pause after GCode"
  }), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("br", null), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_2__["FormControlLabel"], {
    control: react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_2__["TextField"], {
      margin: "normal",
      variant: "outlined",
      className: classes.timeoutText,
      type: "number",
      defaultValue: timeout,
      onChange: e => setTimeout(e.currentTarget.valueAsNumber)
    }),
    label: "Default Timeout in Seconds"
  }), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("br", null), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("br", null), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_2__["Typography"], null, "Firmware Version: ", react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("b", null, getVersionDisplay())), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_2__["Button"], {
    variant: "contained",
    color: "secondary",
    size: "small",
    fullWidth: true
  }, "Update Firmware"), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("br", null), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("br", null), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_2__["FormControlLabel"], {
    control: react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_2__["Checkbox"], {
      checked: enableSlider,
      onChange: e => setEnableSlider(e.currentTarget.checked)
    }),
    label: "Enable Feedrate Percentage"
  }), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_2__["FormControl"], {
    component: "fieldset",
    className: classes.radioGroup
  }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_2__["FormLabel"], {
    component: "legend",
    className: classes.feedRatePercentage
  }, "FeedRate Percentage"), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_2__["RadioGroup"], null, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_2__["FormControlLabel"], {
    control: react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_2__["Radio"], {
      checked: maxFeedRate == 100,
      onChange: e => setMaxFeedRate(100)
    }),
    label: "30% - 100%",
    className: classes.radio
  }), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_2__["FormControlLabel"], {
    control: react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_2__["Radio"], {
      checked: maxFeedRate == 300,
      onChange: e => setMaxFeedRate(300)
    }),
    label: "30% - 300%",
    className: classes.radio
  }))), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("br", null), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("br", null), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("div", {
    style: {
      textAlign: "right",
      width: "100%"
    }
  }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_2__["Button"], {
    variant: "contained",
    className: classes.cancel,
    onClick: handleClose
  }, "CANCEL"), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_2__["Button"], {
    variant: "contained",
    className: classes.save,
    color: "secondary",
    onClick: handleSave
  }, "SAVE CHANGES")))));
}

Settings.propTypes = {
  classes: prop_types__WEBPACK_IMPORTED_MODULE_1___default.a.object.isRequired,
  disabled: prop_types__WEBPACK_IMPORTED_MODULE_1___default.a.bool.isRequired
};
/* harmony default export */ __webpack_exports__["default"] = (Object(_material_ui_core_styles__WEBPACK_IMPORTED_MODULE_4__["withStyles"])(styles)(Settings));

/***/ }),

/***/ "./src/Renderer/components/Modals/Settings/index.js":
/*!**********************************************************!*\
  !*** ./src/Renderer/components/Modals/Settings/index.js ***!
  \**********************************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony import */ var _Settings__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ./Settings */ "./src/Renderer/components/Modals/Settings/Settings.js");

/* harmony default export */ __webpack_exports__["default"] = (_Settings__WEBPACK_IMPORTED_MODULE_0__["default"]);

/***/ }),

/***/ "./src/Renderer/components/Modals/StartMilling/StartMilling.js":
/*!*********************************************************************!*\
  !*** ./src/Renderer/components/Modals/StartMilling/StartMilling.js ***!
  \*********************************************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony import */ var react__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! react */ "react");
/* harmony import */ var react__WEBPACK_IMPORTED_MODULE_0___default = /*#__PURE__*/__webpack_require__.n(react__WEBPACK_IMPORTED_MODULE_0__);
/* harmony import */ var prop_types__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! prop-types */ "prop-types");
/* harmony import */ var prop_types__WEBPACK_IMPORTED_MODULE_1___default = /*#__PURE__*/__webpack_require__.n(prop_types__WEBPACK_IMPORTED_MODULE_1__);
/* harmony import */ var _material_ui_core_styles_withStyles__WEBPACK_IMPORTED_MODULE_2__ = __webpack_require__(/*! @material-ui/core/styles/withStyles */ "@material-ui/core/styles/withStyles");
/* harmony import */ var _material_ui_core_styles_withStyles__WEBPACK_IMPORTED_MODULE_2___default = /*#__PURE__*/__webpack_require__.n(_material_ui_core_styles_withStyles__WEBPACK_IMPORTED_MODULE_2__);
/* harmony import */ var _material_ui_core__WEBPACK_IMPORTED_MODULE_3__ = __webpack_require__(/*! @material-ui/core */ "@material-ui/core");
/* harmony import */ var _material_ui_core__WEBPACK_IMPORTED_MODULE_3___default = /*#__PURE__*/__webpack_require__.n(_material_ui_core__WEBPACK_IMPORTED_MODULE_3__);





const styles = theme => ({
  cancel: {
    marginTop: -theme.spacing.unit,
    marginBottom: theme.spacing.unit
  },
  select: {
    marginTop: -theme.spacing.unit,
    marginBottom: theme.spacing.unit
  }
});

function StartMilling(props) {
  const {
    classes,
    open,
    onClose
  } = props;
  return react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_3__["Dialog"], {
    open: open,
    "aria-labelledby": "form-dialog-title",
    maxWidth: "xs",
    fullWidth: true
  }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_3__["DialogTitle"], null, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("center", null, "START MILLING")), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_3__["DialogContent"], null, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_3__["Typography"], {
    align: "center"
  }, "You are about to start milling. Are you sure you", react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("br", null), "want to continue?")), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_3__["DialogActions"], null, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_3__["Grid"], {
    container: true,
    spacing: 8,
    justify: "center"
  }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_3__["Grid"], {
    item: true,
    xs: 3
  }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_3__["Button"], {
    variant: "contained",
    className: classes.cancel,
    onClick: event => {
      onClose(false);
    },
    fullWidth: true
  }, "CANCEL")), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_3__["Grid"], {
    item: true,
    xs: 3
  }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_3__["Button"], {
    variant: "contained",
    className: classes.select,
    color: "secondary",
    onClick: event => {
      onClose(true);
    },
    fullWidth: true
  }, "START")))));
}

StartMilling.propTypes = {
  classes: prop_types__WEBPACK_IMPORTED_MODULE_1___default.a.object.isRequired,
  open: prop_types__WEBPACK_IMPORTED_MODULE_1___default.a.bool.isRequired,
  onClose: prop_types__WEBPACK_IMPORTED_MODULE_1___default.a.func
};
/* harmony default export */ __webpack_exports__["default"] = (_material_ui_core_styles_withStyles__WEBPACK_IMPORTED_MODULE_2___default()(styles)(StartMilling));

/***/ }),

/***/ "./src/Renderer/components/Modals/StartMilling/index.js":
/*!**************************************************************!*\
  !*** ./src/Renderer/components/Modals/StartMilling/index.js ***!
  \**************************************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony import */ var _StartMilling__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ./StartMilling */ "./src/Renderer/components/Modals/StartMilling/StartMilling.js");

/* harmony default export */ __webpack_exports__["default"] = (_StartMilling__WEBPACK_IMPORTED_MODULE_0__["default"]);

/***/ }),

/***/ "./src/Renderer/components/Modals/ViewLogs/ViewLogs.js":
/*!*************************************************************!*\
  !*** ./src/Renderer/components/Modals/ViewLogs/ViewLogs.js ***!
  \*************************************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony import */ var react__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! react */ "react");
/* harmony import */ var react__WEBPACK_IMPORTED_MODULE_0___default = /*#__PURE__*/__webpack_require__.n(react__WEBPACK_IMPORTED_MODULE_0__);
/* harmony import */ var prop_types__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! prop-types */ "prop-types");
/* harmony import */ var prop_types__WEBPACK_IMPORTED_MODULE_1___default = /*#__PURE__*/__webpack_require__.n(prop_types__WEBPACK_IMPORTED_MODULE_1__);
/* harmony import */ var _material_ui_core_styles_withStyles__WEBPACK_IMPORTED_MODULE_2__ = __webpack_require__(/*! @material-ui/core/styles/withStyles */ "@material-ui/core/styles/withStyles");
/* harmony import */ var _material_ui_core_styles_withStyles__WEBPACK_IMPORTED_MODULE_2___default = /*#__PURE__*/__webpack_require__.n(_material_ui_core_styles_withStyles__WEBPACK_IMPORTED_MODULE_2__);
/* harmony import */ var electron__WEBPACK_IMPORTED_MODULE_3__ = __webpack_require__(/*! electron */ "electron");
/* harmony import */ var electron__WEBPACK_IMPORTED_MODULE_3___default = /*#__PURE__*/__webpack_require__.n(electron__WEBPACK_IMPORTED_MODULE_3__);
/* harmony import */ var _material_ui_core__WEBPACK_IMPORTED_MODULE_4__ = __webpack_require__(/*! @material-ui/core */ "@material-ui/core");
/* harmony import */ var _material_ui_core__WEBPACK_IMPORTED_MODULE_4___default = /*#__PURE__*/__webpack_require__.n(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__);






const styles = theme => ({
  cancel: {
    marginTop: -theme.spacing.unit,
    marginBottom: theme.spacing.unit
  },
  open: {
    marginTop: -theme.spacing.unit,
    marginBottom: theme.spacing.unit
  },
  logOutput: {
    width: "calc(100% - 6px)"
  }
});

function ViewLogs(props) {
  const {
    classes,
    open,
    onClose
  } = props;
  const [logText, setLogText] = react__WEBPACK_IMPORTED_MODULE_0___default.a.useState("");
  const [logFile, setLogFile] = react__WEBPACK_IMPORTED_MODULE_0___default.a.useState("");

  function handleOpen(event) {
    electron__WEBPACK_IMPORTED_MODULE_3__["shell"].openExternal(logFile);
    onClose(event);
  }

  function handleClose(event) {
    onClose(event);
  }

  function getLogText() {
    if (logFile.length == 0) {
      setLogFile(electron__WEBPACK_IMPORTED_MODULE_3__["ipcRenderer"].sendSync("Logs::GetLogFile"));
    } else if (logText.length == 0) {
      electron__WEBPACK_IMPORTED_MODULE_3__["ipcRenderer"].removeAllListeners("File::FileOpened");
      electron__WEBPACK_IMPORTED_MODULE_3__["ipcRenderer"].on("File::FileOpened", function (event, data) {
        if (data != null && data.length > 0) {
          setLogText(data);
        } else {
          setLogText("No logs found.");
        }
      });
      electron__WEBPACK_IMPORTED_MODULE_3__["ipcRenderer"].send('File::ReadFile', logFile);
    } else {
      return logText;
    }

    return "Loading";
  }

  return react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["Dialog"], {
    open: open,
    "aria-labelledby": "form-dialog-title",
    maxWidth: "sm",
    fullWidth: true
  }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["DialogTitle"], null, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("center", null, "View Logs")), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["DialogContent"], null, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("br", null), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("textarea", {
    type: "text",
    disabled: true,
    overflow: "auto",
    rows: "12",
    cols: "78",
    value: getLogText(),
    className: classes.logOutput
  }), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("br", null)), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["DialogActions"], null, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["Grid"], {
    container: true,
    spacing: 8,
    justify: "center"
  }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["Grid"], {
    item: true,
    xs: 3
  }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["Button"], {
    variant: "contained",
    className: classes.cancel,
    onClick: handleClose,
    fullWidth: true
  }, "CLOSE")), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["Grid"], {
    item: true,
    xs: 3
  }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["Button"], {
    variant: "contained",
    className: classes.open,
    color: "secondary",
    onClick: handleOpen,
    fullWidth: true
  }, "OPEN/SAVE")))));
}

ViewLogs.propTypes = {
  classes: prop_types__WEBPACK_IMPORTED_MODULE_1___default.a.object.isRequired,
  open: prop_types__WEBPACK_IMPORTED_MODULE_1___default.a.bool.isRequired,
  onClose: prop_types__WEBPACK_IMPORTED_MODULE_1___default.a.func
};
/* harmony default export */ __webpack_exports__["default"] = (_material_ui_core_styles_withStyles__WEBPACK_IMPORTED_MODULE_2___default()(styles)(ViewLogs));

/***/ }),

/***/ "./src/Renderer/components/Modals/ViewLogs/index.js":
/*!**********************************************************!*\
  !*** ./src/Renderer/components/Modals/ViewLogs/index.js ***!
  \**********************************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony import */ var _ViewLogs__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ./ViewLogs */ "./src/Renderer/components/Modals/ViewLogs/ViewLogs.js");

/* harmony default export */ __webpack_exports__["default"] = (_ViewLogs__WEBPACK_IMPORTED_MODULE_0__["default"]);

/***/ }),

/***/ "./src/Renderer/components/Status/Status.js":
/*!**************************************************!*\
  !*** ./src/Renderer/components/Status/Status.js ***!
  \**************************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony import */ var react__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! react */ "react");
/* harmony import */ var react__WEBPACK_IMPORTED_MODULE_0___default = /*#__PURE__*/__webpack_require__.n(react__WEBPACK_IMPORTED_MODULE_0__);
/* harmony import */ var prop_types__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! prop-types */ "prop-types");
/* harmony import */ var prop_types__WEBPACK_IMPORTED_MODULE_1___default = /*#__PURE__*/__webpack_require__.n(prop_types__WEBPACK_IMPORTED_MODULE_1__);
/* harmony import */ var _material_ui_core__WEBPACK_IMPORTED_MODULE_2__ = __webpack_require__(/*! @material-ui/core */ "@material-ui/core");
/* harmony import */ var _material_ui_core__WEBPACK_IMPORTED_MODULE_2___default = /*#__PURE__*/__webpack_require__.n(_material_ui_core__WEBPACK_IMPORTED_MODULE_2__);
/* harmony import */ var electron__WEBPACK_IMPORTED_MODULE_3__ = __webpack_require__(/*! electron */ "electron");
/* harmony import */ var electron__WEBPACK_IMPORTED_MODULE_3___default = /*#__PURE__*/__webpack_require__.n(electron__WEBPACK_IMPORTED_MODULE_3__);
/* harmony import */ var _material_ui_core_styles__WEBPACK_IMPORTED_MODULE_4__ = __webpack_require__(/*! @material-ui/core/styles */ "@material-ui/core/styles");
/* harmony import */ var _material_ui_core_styles__WEBPACK_IMPORTED_MODULE_4___default = /*#__PURE__*/__webpack_require__.n(_material_ui_core_styles__WEBPACK_IMPORTED_MODULE_4__);
/* harmony import */ var _material_ui_core_colors__WEBPACK_IMPORTED_MODULE_5__ = __webpack_require__(/*! @material-ui/core/colors */ "@material-ui/core/colors");
/* harmony import */ var _material_ui_core_colors__WEBPACK_IMPORTED_MODULE_5___default = /*#__PURE__*/__webpack_require__.n(_material_ui_core_colors__WEBPACK_IMPORTED_MODULE_5__);
/* harmony import */ var _material_ui_icons_lens__WEBPACK_IMPORTED_MODULE_6__ = __webpack_require__(/*! @material-ui/icons/lens */ "@material-ui/icons/lens");
/* harmony import */ var _material_ui_icons_lens__WEBPACK_IMPORTED_MODULE_6___default = /*#__PURE__*/__webpack_require__.n(_material_ui_icons_lens__WEBPACK_IMPORTED_MODULE_6__);








const styles = theme => ({
  leftRightPadding: {
    padding: theme.spacing.unit
  },
  status: {
    marginLeft: 0,
    //marginBottom: theme.spacing.unit,
    paddingLeft: 0 //paddingBottom: 2 * theme.spacing.unit,

  }
});

function Status(props) {
  const {
    classes,
    status
  } = props; //const [ghostGunnerStatus, setGhostGunnerStatus] = React.useState(0);

  /*ipcRenderer.removeAllListeners("DD_UpdateGGStatus");
  ipcRenderer.on("DD_UpdateGGStatus", function (event, newStatus) {
      if (newStatus != ghostGunnerStatus) {
          setGhostGunnerStatus(newStatus);
      }
  });*/

  const statusTheme = Object(_material_ui_core__WEBPACK_IMPORTED_MODULE_2__["createMuiTheme"])({
    palette: {
      primary: {
        main: '#069076'
      },
      secondary: _material_ui_core_colors__WEBPACK_IMPORTED_MODULE_5__["yellow"],
      error: _material_ui_core_colors__WEBPACK_IMPORTED_MODULE_5__["red"]
    }
  });

  function getColor() {
    var color = "error";

    if (status == 1) {
      color = "secondary";
    } else if (status == 2) {
      color = "primary";
    }

    return color;
  }

  function getStatusText() {
    var statusText = "Not Connected";

    if (status == 1) {
      statusText = "Connecting";
    } else if (status == 2) {
      statusText = "Connected";
    }

    return statusText;
  }

  return react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(react__WEBPACK_IMPORTED_MODULE_0___default.a.Fragment, null, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_2__["MuiThemeProvider"], {
    theme: statusTheme
  }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_2__["Fab"], {
    variant: "extended",
    disabled: true,
    align: "left",
    className: classes.status,
    id: "GGStatus"
  }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_icons_lens__WEBPACK_IMPORTED_MODULE_6___default.a, {
    color: getColor(),
    style: {
      width: "18px"
    }
  }), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_2__["Typography"], {
    color: getColor()
  }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("b", null, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("span", {
    className: classes.leftRightPadding,
    style: {
      color: '#ffffff'
    }
  }, "GG Status:"), getStatusText())))));
}

Status.propTypes = {
  classes: prop_types__WEBPACK_IMPORTED_MODULE_1___default.a.object.isRequired,
  status: prop_types__WEBPACK_IMPORTED_MODULE_1___default.a.number.isRequired
};
/* harmony default export */ __webpack_exports__["default"] = (Object(_material_ui_core_styles__WEBPACK_IMPORTED_MODULE_4__["withStyles"])(styles)(Status));

/***/ }),

/***/ "./src/Renderer/components/Status/index.js":
/*!*************************************************!*\
  !*** ./src/Renderer/components/Status/index.js ***!
  \*************************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony import */ var _Status__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ./Status */ "./src/Renderer/components/Status/Status.js");

/* harmony default export */ __webpack_exports__["default"] = (_Status__WEBPACK_IMPORTED_MODULE_0__["default"]);

/***/ }),

/***/ "./src/Renderer/components/StepList/StepList.js":
/*!******************************************************!*\
  !*** ./src/Renderer/components/StepList/StepList.js ***!
  \******************************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony import */ var react__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! react */ "react");
/* harmony import */ var react__WEBPACK_IMPORTED_MODULE_0___default = /*#__PURE__*/__webpack_require__.n(react__WEBPACK_IMPORTED_MODULE_0__);
/* harmony import */ var prop_types__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! prop-types */ "prop-types");
/* harmony import */ var prop_types__WEBPACK_IMPORTED_MODULE_1___default = /*#__PURE__*/__webpack_require__.n(prop_types__WEBPACK_IMPORTED_MODULE_1__);
/* harmony import */ var _material_ui_core_styles__WEBPACK_IMPORTED_MODULE_2__ = __webpack_require__(/*! @material-ui/core/styles */ "@material-ui/core/styles");
/* harmony import */ var _material_ui_core_styles__WEBPACK_IMPORTED_MODULE_2___default = /*#__PURE__*/__webpack_require__.n(_material_ui_core_styles__WEBPACK_IMPORTED_MODULE_2__);
/* harmony import */ var _material_ui_core__WEBPACK_IMPORTED_MODULE_3__ = __webpack_require__(/*! @material-ui/core */ "@material-ui/core");
/* harmony import */ var _material_ui_core__WEBPACK_IMPORTED_MODULE_3___default = /*#__PURE__*/__webpack_require__.n(_material_ui_core__WEBPACK_IMPORTED_MODULE_3__);





const styles = theme => ({
  root: {
    width: '100%',
    height: 'calc(100% - 40px)'
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
    marginRight: '0px'
  },
  itemText: {
    marginLeft: '0px',
    marginRight: '0px',
    fontFamily: 'Arial',
    opacity: 0.87,
    fontSize: '14px',
    color: '#9f9f9f'
    /* selected: color: #069076;*/

  }
});

class StepList extends react__WEBPACK_IMPORTED_MODULE_0___default.a.Component {
  constructor() {
    super();
    this.selectedRef = react__WEBPACK_IMPORTED_MODULE_0___default.a.createRef();
  }

  componentWillReceiveProps(prevProps) {
    setTimeout(() => {
      this.selectedRef.scrollIntoView({
        behavior: "smooth",
        block: 'center'
      });
    });
  }

  render() {
    const {
      classes,
      steps,
      selectedStep
    } = this.props;

    function getListItem(step, index, component) {
      var selectedDiv = null;

      if (selectedStep === index) {
        selectedDiv = react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("div", {
          style: {
            float: "left",
            clear: "both"
          },
          ref: el => {
            component.selectedRef = el;
          }
        });
      }

      return react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_3__["ListItem"], {
        button: true,
        disableGutters: true,
        key: index,
        selected: selectedStep === index,
        className: classes.item
      }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_3__["ListItemText"], {
        disableTypography: true
      }, selectedDiv, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_3__["Typography"], {
        noWrap: true,
        className: classes.itemText
      }, step.Title)));
    }

    return react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("div", {
      className: classes.root
    }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_3__["List"], {
      component: "nav",
      className: classes.list
    }, steps.map((step, index) => {
      return getListItem(step, index, this);
    })));
  }

}

;
StepList.propTypes = {
  classes: prop_types__WEBPACK_IMPORTED_MODULE_1___default.a.object.isRequired,
  steps: prop_types__WEBPACK_IMPORTED_MODULE_1___default.a.array.isRequired,
  selectedStep: prop_types__WEBPACK_IMPORTED_MODULE_1___default.a.number.isRequired
};
/* harmony default export */ __webpack_exports__["default"] = (Object(_material_ui_core_styles__WEBPACK_IMPORTED_MODULE_2__["withStyles"])(styles)(StepList));

/***/ }),

/***/ "./src/Renderer/components/StepList/index.js":
/*!***************************************************!*\
  !*** ./src/Renderer/components/StepList/index.js ***!
  \***************************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony import */ var _StepList__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ./StepList */ "./src/Renderer/components/StepList/StepList.js");

/* harmony default export */ __webpack_exports__["default"] = (_StepList__WEBPACK_IMPORTED_MODULE_0__["default"]);

/***/ }),

/***/ "./src/Renderer/components/Support/Support.js":
/*!****************************************************!*\
  !*** ./src/Renderer/components/Support/Support.js ***!
  \****************************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony import */ var react__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! react */ "react");
/* harmony import */ var react__WEBPACK_IMPORTED_MODULE_0___default = /*#__PURE__*/__webpack_require__.n(react__WEBPACK_IMPORTED_MODULE_0__);
/* harmony import */ var prop_types__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! prop-types */ "prop-types");
/* harmony import */ var prop_types__WEBPACK_IMPORTED_MODULE_1___default = /*#__PURE__*/__webpack_require__.n(prop_types__WEBPACK_IMPORTED_MODULE_1__);
/* harmony import */ var path__WEBPACK_IMPORTED_MODULE_2__ = __webpack_require__(/*! path */ "path");
/* harmony import */ var path__WEBPACK_IMPORTED_MODULE_2___default = /*#__PURE__*/__webpack_require__.n(path__WEBPACK_IMPORTED_MODULE_2__);
/* harmony import */ var electron__WEBPACK_IMPORTED_MODULE_3__ = __webpack_require__(/*! electron */ "electron");
/* harmony import */ var electron__WEBPACK_IMPORTED_MODULE_3___default = /*#__PURE__*/__webpack_require__.n(electron__WEBPACK_IMPORTED_MODULE_3__);
/* harmony import */ var _material_ui_core__WEBPACK_IMPORTED_MODULE_4__ = __webpack_require__(/*! @material-ui/core */ "@material-ui/core");
/* harmony import */ var _material_ui_core__WEBPACK_IMPORTED_MODULE_4___default = /*#__PURE__*/__webpack_require__.n(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__);
/* harmony import */ var _material_ui_core_styles__WEBPACK_IMPORTED_MODULE_5__ = __webpack_require__(/*! @material-ui/core/styles */ "@material-ui/core/styles");
/* harmony import */ var _material_ui_core_styles__WEBPACK_IMPORTED_MODULE_5___default = /*#__PURE__*/__webpack_require__.n(_material_ui_core_styles__WEBPACK_IMPORTED_MODULE_5__);
/* harmony import */ var _Modals_CustomerSupport__WEBPACK_IMPORTED_MODULE_6__ = __webpack_require__(/*! ../Modals/CustomerSupport */ "./src/Renderer/components/Modals/CustomerSupport/index.js");
/* harmony import */ var _Modals_ViewLogs__WEBPACK_IMPORTED_MODULE_7__ = __webpack_require__(/*! ../Modals/ViewLogs */ "./src/Renderer/components/Modals/ViewLogs/index.js");
function _extends() { _extends = Object.assign || function (target) { for (var i = 1; i < arguments.length; i++) { var source = arguments[i]; for (var key in source) { if (Object.prototype.hasOwnProperty.call(source, key)) { target[key] = source[key]; } } } return target; }; return _extends.apply(this, arguments); }










const styles = theme => ({
  root: {
    display: 'flex'
  },
  paper: {
    marginBottom: '5px',
    border: '#FFFFFF 1px solid'
  },
  menuItem: {
    '&:hover': {
      backgroundColor: theme.palette.primary.dark
    }
  },
  supportButton: {
    paddingTop: 0,
    paddingBottom: 0,
    paddingLeft: theme.spacing.unit,
    paddingRight: theme.spacing.unit,
    backgroundColor: "transparent"
  },
  supportImg: {
    width: '100px',
    height: '25px',
    objectFit: 'contain',
    padding: 0,
    margin: 0
  }
});

class Support extends react__WEBPACK_IMPORTED_MODULE_0___default.a.Component {
  constructor() {
    super();
    this.state = {
      openDialog: false,
      openMenu: false,
      openLogViewer: false
    };
    this.anchor = react__WEBPACK_IMPORTED_MODULE_0___default.a.createRef();
    this.handleToggleMenu = this.handleToggleMenu.bind(this);
    this.handleCloseMenu = this.handleCloseMenu.bind(this);
    this.handleOpenDialog = this.handleOpenDialog.bind(this);
    this.handleCloseDialog = this.handleCloseDialog.bind(this);
    this.handleShowLogs = this.handleShowLogs.bind(this);
    this.handleCloseLogViewer = this.handleCloseLogViewer.bind(this);
  }

  handleToggleMenu() {
    this.setState({
      openMenu: !this.state.openMenu
    });
  }

  handleCloseMenu(event) {
    if (this.anchor.contains(event.target)) {
      return;
    }

    this.setState({
      openMenu: false
    });
  }

  handleOpenDialog() {
    this.setState({
      openDialog: true,
      openMenu: false
    });
  }

  handleCloseDialog() {
    this.setState({
      openDialog: false
    });
  }

  handleShowLogs() {
    this.setState({
      openMenu: false,
      openLogViewer: true
    });
  }

  handleCloseLogViewer() {
    this.setState({
      openMenu: false,
      openLogViewer: false
    });
  }

  render() {
    const {
      classes,
      disabled
    } = this.props;

    function onClickWalkthrough(event) {
      if (!disabled) {
        const currentPage = electron__WEBPACK_IMPORTED_MODULE_3__["ipcRenderer"].sendSync("DD_GetCurrentPage");

        if (currentPage == "Dashboard") {
          window.ShowDashboardWalkthrough();
        } else if (currentPage == "Milling") {
          window.ShowMillingWalkthrough();
        }
      }

      this.handleCloseMenu(event);
    }

    function onClickViewManual(event) {
      electron__WEBPACK_IMPORTED_MODULE_3__["shell"].openExternal(__dirname + '/../../../../doc/GG2Manual.pdf');
      this.handleCloseMenu(event);
    }

    function onClickVisitSupport(event) {
      electron__WEBPACK_IMPORTED_MODULE_3__["shell"].openExternal("https://ghostgunner.net/");
      this.handleCloseMenu(event);
    }

    function onClickOpenDialog() {
      if (!disabled) {
        this.handleOpenDialog();
      }
    }

    function onClickShowLogs() {
      if (!disabled) {
        this.handleShowLogs();
      }
    }

    return react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(react__WEBPACK_IMPORTED_MODULE_0___default.a.Fragment, null, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["Fab"], {
      variant: "extended",
      "aria-label": "Support",
      onClick: this.handleToggleMenu,
      className: classes.supportButton,
      size: "small",
      buttonRef: node => {
        this.anchor = node;
      },
      id: "support"
    }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("img", {
      src: path__WEBPACK_IMPORTED_MODULE_2___default.a.join(__dirname, '../../static/img/support_button.png'),
      className: classes.supportImg
    })), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["Popper"], {
      open: this.state.openMenu,
      anchorEl: this.anchor,
      transition: true,
      disablePortal: true
    }, ({
      TransitionProps,
      placement
    }) => react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["Grow"], _extends({}, TransitionProps, {
      id: "menu-list-grow",
      style: {
        transformOrigin: placement === 'bottom' ? 'center top' : 'center bottom'
      }
    }), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["Paper"], {
      className: classes.paper
    }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["ClickAwayListener"], {
      onClickAway: this.handleCloseMenu
    }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["MenuList"], null, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["MenuItem"], {
      className: classes.menuItem,
      onClick: onClickWalkthrough.bind(this)
    }, "'How to' Walkthrough"), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["MenuItem"], {
      className: classes.menuItem,
      onClick: onClickViewManual.bind(this)
    }, "View Manual"), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["MenuItem"], {
      className: classes.menuItem,
      onClick: onClickVisitSupport.bind(this)
    }, "Visit Support Page"), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["MenuItem"], {
      className: classes.menuItem,
      onClick: onClickOpenDialog.bind(this)
    }, "Customer Support Request"), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_4__["MenuItem"], {
      className: classes.menuItem,
      onClick: onClickShowLogs.bind(this)
    }, "Show Logs")))))), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_Modals_CustomerSupport__WEBPACK_IMPORTED_MODULE_6__["default"], {
      open: this.state.openDialog,
      onClose: this.handleCloseDialog
    }), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_Modals_ViewLogs__WEBPACK_IMPORTED_MODULE_7__["default"], {
      open: this.state.openLogViewer,
      onClose: this.handleCloseLogViewer
    }));
  }

}

;
Support.propTypes = {
  classes: prop_types__WEBPACK_IMPORTED_MODULE_1___default.a.object.isRequired,
  disabled: prop_types__WEBPACK_IMPORTED_MODULE_1___default.a.bool.isRequired
};
/* harmony default export */ __webpack_exports__["default"] = (Object(_material_ui_core_styles__WEBPACK_IMPORTED_MODULE_5__["withStyles"])(styles)(Support));

/***/ }),

/***/ "./src/Renderer/components/Support/index.js":
/*!**************************************************!*\
  !*** ./src/Renderer/components/Support/index.js ***!
  \**************************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony import */ var _Support__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ./Support */ "./src/Renderer/components/Support/Support.js");

/* harmony default export */ __webpack_exports__["default"] = (_Support__WEBPACK_IMPORTED_MODULE_0__["default"]);

/***/ }),

/***/ "./src/Renderer/containers/Dashboard/Dashboard.js":
/*!********************************************************!*\
  !*** ./src/Renderer/containers/Dashboard/Dashboard.js ***!
  \********************************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony import */ var react__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! react */ "react");
/* harmony import */ var react__WEBPACK_IMPORTED_MODULE_0___default = /*#__PURE__*/__webpack_require__.n(react__WEBPACK_IMPORTED_MODULE_0__);
/* harmony import */ var prop_types__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! prop-types */ "prop-types");
/* harmony import */ var prop_types__WEBPACK_IMPORTED_MODULE_1___default = /*#__PURE__*/__webpack_require__.n(prop_types__WEBPACK_IMPORTED_MODULE_1__);
/* harmony import */ var _components_Menu__WEBPACK_IMPORTED_MODULE_2__ = __webpack_require__(/*! ../../components/Menu */ "./src/Renderer/components/Menu/index.js");
/* harmony import */ var _material_ui_core__WEBPACK_IMPORTED_MODULE_3__ = __webpack_require__(/*! @material-ui/core */ "@material-ui/core");
/* harmony import */ var _material_ui_core__WEBPACK_IMPORTED_MODULE_3___default = /*#__PURE__*/__webpack_require__.n(_material_ui_core__WEBPACK_IMPORTED_MODULE_3__);
/* harmony import */ var _material_ui_core_styles_withStyles__WEBPACK_IMPORTED_MODULE_4__ = __webpack_require__(/*! @material-ui/core/styles/withStyles */ "@material-ui/core/styles/withStyles");
/* harmony import */ var _material_ui_core_styles_withStyles__WEBPACK_IMPORTED_MODULE_4___default = /*#__PURE__*/__webpack_require__.n(_material_ui_core_styles_withStyles__WEBPACK_IMPORTED_MODULE_4__);
/* harmony import */ var path__WEBPACK_IMPORTED_MODULE_5__ = __webpack_require__(/*! path */ "path");
/* harmony import */ var path__WEBPACK_IMPORTED_MODULE_5___default = /*#__PURE__*/__webpack_require__.n(path__WEBPACK_IMPORTED_MODULE_5__);
/* harmony import */ var electron__WEBPACK_IMPORTED_MODULE_6__ = __webpack_require__(/*! electron */ "electron");
/* harmony import */ var electron__WEBPACK_IMPORTED_MODULE_6___default = /*#__PURE__*/__webpack_require__.n(electron__WEBPACK_IMPORTED_MODULE_6__);
/* harmony import */ var _components_Modals_JobSelection__WEBPACK_IMPORTED_MODULE_7__ = __webpack_require__(/*! ../../components/Modals/JobSelection */ "./src/Renderer/components/Modals/JobSelection/index.js");
/* harmony import */ var react_router_dom__WEBPACK_IMPORTED_MODULE_8__ = __webpack_require__(/*! react-router-dom */ "react-router-dom");
/* harmony import */ var react_router_dom__WEBPACK_IMPORTED_MODULE_8___default = /*#__PURE__*/__webpack_require__.n(react_router_dom__WEBPACK_IMPORTED_MODULE_8__);
/* harmony import */ var _components_Modals_CustomerSupport__WEBPACK_IMPORTED_MODULE_9__ = __webpack_require__(/*! ../../components/Modals/CustomerSupport */ "./src/Renderer/components/Modals/CustomerSupport/index.js");











const styles = theme => ({
  main: {
    width: '80%',
    height: '45%',
    marginTop: 'auto',
    marginBottom: 'auto',
    marginLeft: 'auto',
    marginRight: 'auto',
    position: 'absolute',
    borderLeft: 'solid 3px #969696',
    borderRight: 'solid 3px #969696',
    borderBottom: 'solid 3px #969696'
  },
  dashboardStyle: {
    backgroundImage: `url(${"./static/img/back-texture.jpg"})`,
    backgroundSize: 'cover',
    overflow: 'hidden',
    width: '100%',
    height: '100%',
    position: 'fixed',
    left: 0,
    top: 0,
    z: -1,
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
    display: 'flex',
    verticalAlign: 'middle'
  },
  topLeft: {
    width: 'calc(40% - 60px)',
    height: '45%',
    marginTop: 'auto',
    marginBottom: 'auto',
    marginLeft: 'calc(-20% - 30px)',
    position: 'absolute',
    borderTop: 'solid 3px #969696'
  },
  topRight: {
    width: 'calc(40% - 60px)',
    height: '45%',
    marginTop: 'auto',
    marginBottom: 'auto',
    marginLeft: 'calc(20% + 30px)',
    position: 'absolute',
    borderTop: 'solid 3px #969696'
  }
});

function Dashboard(props) {
  const {
    classes,
    status
  } = props;
  const [availableJobs, setAvailableJobs] = react__WEBPACK_IMPORTED_MODULE_0___default.a.useState(new Array());
  const [showJobSelection, setShowJobSelection] = react__WEBPACK_IMPORTED_MODULE_0___default.a.useState(false);
  const [navigateToMilling, setNavigateToMilling] = react__WEBPACK_IMPORTED_MODULE_0___default.a.useState(false);
  const [openCustomerSupport, setOpenCustomerSupport] = react__WEBPACK_IMPORTED_MODULE_0___default.a.useState(false);

  function onClickRun() {
    if (status == 2) {
      electron__WEBPACK_IMPORTED_MODULE_6__["ipcRenderer"].removeAllListeners("Jobs::JobSelected");
      electron__WEBPACK_IMPORTED_MODULE_6__["ipcRenderer"].on("Jobs::JobSelected", event => {
        setNavigateToMilling(true);
      });
      electron__WEBPACK_IMPORTED_MODULE_6__["ipcRenderer"].removeAllListeners("ShowJobSelection");
      electron__WEBPACK_IMPORTED_MODULE_6__["ipcRenderer"].on("ShowJobSelection", (event, jobs) => {
        setAvailableJobs(jobs);
        setShowJobSelection(true);
      });
      electron__WEBPACK_IMPORTED_MODULE_6__["ipcRenderer"].send('File::OpenFileDialog');
    }
  }

  function onCloseJobSelection(event) {
    setShowJobSelection(false);
  }

  function onClickHelp() {
    setOpenCustomerSupport(true);
  }

  if (navigateToMilling) {
    return react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(react_router_dom__WEBPACK_IMPORTED_MODULE_8__["Redirect"], {
      to: "/milling"
    });
  }

  function getRunImage() {
    if (status == 2) {
      return react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("img", {
        style: {
          marginTop: '20px',
          height: '14vh'
        },
        src: path__WEBPACK_IMPORTED_MODULE_5___default.a.join(__dirname, '../../static/img/run.png'),
        onMouseOver: e => e.currentTarget.src = path__WEBPACK_IMPORTED_MODULE_5___default.a.join(__dirname, '../../static/img/run_hover.png'),
        onMouseOut: e => e.currentTarget.src = path__WEBPACK_IMPORTED_MODULE_5___default.a.join(__dirname, '../../static/img/run.png'),
        onClick: onClickRun
      });
    } else {
      return react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("img", {
        style: {
          marginTop: '20px',
          height: '14vh'
        },
        src: path__WEBPACK_IMPORTED_MODULE_5___default.a.join(__dirname, '../../static/img/run.png')
      });
    }
  }

  return react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("section", {
    className: classes.dashboardStyle
  }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_components_Menu__WEBPACK_IMPORTED_MODULE_2__["default"], null), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_components_Modals_JobSelection__WEBPACK_IMPORTED_MODULE_7__["default"], {
    open: showJobSelection,
    onClose: onCloseJobSelection,
    jobs: availableJobs
  }), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("div", {
    className: classes.topLeft
  }), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("div", {
    className: classes.topRight
  }), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("div", {
    className: classes.main
  }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("div", {
    style: {
      position: "absolute",
      width: "100%"
    }
  }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("center", null, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("img", {
    src: path__WEBPACK_IMPORTED_MODULE_5___default.a.join(__dirname, './static/img/logo-white.png'),
    width: "88px",
    style: {
      marginTop: "-44px"
    }
  }))), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_3__["Grid"], {
    container: true,
    spacing: 8,
    direction: "row",
    justify: "center",
    alignItems: "center",
    style: {
      height: '100%'
    }
  }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_3__["Grid"], {
    item: true,
    xs: 4
  }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("center", null, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_3__["Button"], {
    style: {
      backgroundColor: "transparent"
    },
    id: "store"
  }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("img", {
    style: {
      marginTop: '20px',
      marginLeft: '30px',
      height: '14vh'
    },
    src: path__WEBPACK_IMPORTED_MODULE_5___default.a.join(__dirname, '../../static/img/store.png'),
    onMouseOver: e => e.currentTarget.src = path__WEBPACK_IMPORTED_MODULE_5___default.a.join(__dirname, '../../static/img/store_hover.png'),
    onMouseOut: e => e.currentTarget.src = path__WEBPACK_IMPORTED_MODULE_5___default.a.join(__dirname, '../../static/img/store.png'),
    onClick: () => {
      electron__WEBPACK_IMPORTED_MODULE_6__["shell"].openExternal("https://ghostgunner.net/collections/featured-products");
    }
  })))), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_3__["Grid"], {
    item: true,
    xs: 4
  }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("center", null, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_3__["Button"], {
    style: {
      backgroundColor: "transparent"
    },
    disabled: status != 2,
    id: "run"
  }, getRunImage()))), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_3__["Grid"], {
    item: true,
    xs: 4
  }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("center", null, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_3__["Button"], {
    style: {
      backgroundColor: "transparent"
    }
  }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("img", {
    style: {
      marginTop: '20px',
      marginRight: '30px',
      height: '14vh'
    },
    src: path__WEBPACK_IMPORTED_MODULE_5___default.a.join(__dirname, '../../static/img/help.png'),
    onMouseOver: e => e.currentTarget.src = path__WEBPACK_IMPORTED_MODULE_5___default.a.join(__dirname, '../../static/img/help_hover.png'),
    onMouseOut: e => e.currentTarget.src = path__WEBPACK_IMPORTED_MODULE_5___default.a.join(__dirname, '../../static/img/help.png'),
    onClick: onClickHelp
  })))))), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_components_Modals_CustomerSupport__WEBPACK_IMPORTED_MODULE_9__["default"], {
    open: openCustomerSupport,
    onClose: () => {
      setOpenCustomerSupport(false);
    }
  }));
}

Dashboard.propTypes = {
  classes: prop_types__WEBPACK_IMPORTED_MODULE_1___default.a.object.isRequired,
  status: prop_types__WEBPACK_IMPORTED_MODULE_1___default.a.number.isRequired
};
/* harmony default export */ __webpack_exports__["default"] = (_material_ui_core_styles_withStyles__WEBPACK_IMPORTED_MODULE_4___default()(styles)(Dashboard));

/***/ }),

/***/ "./src/Renderer/containers/Dashboard/index.js":
/*!****************************************************!*\
  !*** ./src/Renderer/containers/Dashboard/index.js ***!
  \****************************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony import */ var _Dashboard__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ./Dashboard */ "./src/Renderer/containers/Dashboard/Dashboard.js");

/* harmony default export */ __webpack_exports__["default"] = (_Dashboard__WEBPACK_IMPORTED_MODULE_0__["default"]);

/***/ }),

/***/ "./src/Renderer/containers/Milling/Milling.js":
/*!****************************************************!*\
  !*** ./src/Renderer/containers/Milling/Milling.js ***!
  \****************************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony import */ var react__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! react */ "react");
/* harmony import */ var react__WEBPACK_IMPORTED_MODULE_0___default = /*#__PURE__*/__webpack_require__.n(react__WEBPACK_IMPORTED_MODULE_0__);
/* harmony import */ var prop_types__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! prop-types */ "prop-types");
/* harmony import */ var prop_types__WEBPACK_IMPORTED_MODULE_1___default = /*#__PURE__*/__webpack_require__.n(prop_types__WEBPACK_IMPORTED_MODULE_1__);
/* harmony import */ var electron__WEBPACK_IMPORTED_MODULE_2__ = __webpack_require__(/*! electron */ "electron");
/* harmony import */ var electron__WEBPACK_IMPORTED_MODULE_2___default = /*#__PURE__*/__webpack_require__.n(electron__WEBPACK_IMPORTED_MODULE_2__);
/* harmony import */ var _material_ui_core_styles_withStyles__WEBPACK_IMPORTED_MODULE_3__ = __webpack_require__(/*! @material-ui/core/styles/withStyles */ "@material-ui/core/styles/withStyles");
/* harmony import */ var _material_ui_core_styles_withStyles__WEBPACK_IMPORTED_MODULE_3___default = /*#__PURE__*/__webpack_require__.n(_material_ui_core_styles_withStyles__WEBPACK_IMPORTED_MODULE_3__);
/* harmony import */ var _components_StepList__WEBPACK_IMPORTED_MODULE_4__ = __webpack_require__(/*! ../../components/StepList */ "./src/Renderer/components/StepList/index.js");
/* harmony import */ var _components_ImageRaw__WEBPACK_IMPORTED_MODULE_5__ = __webpack_require__(/*! ../../components/ImageRaw */ "./src/Renderer/components/ImageRaw/index.js");
/* harmony import */ var _components_Modals_StartMilling__WEBPACK_IMPORTED_MODULE_6__ = __webpack_require__(/*! ../../components/Modals/StartMilling */ "./src/Renderer/components/Modals/StartMilling/index.js");
/* harmony import */ var _components_Modals_Alert__WEBPACK_IMPORTED_MODULE_7__ = __webpack_require__(/*! ../../components/Modals/Alert */ "./src/Renderer/components/Modals/Alert/index.js");
/* harmony import */ var path__WEBPACK_IMPORTED_MODULE_8__ = __webpack_require__(/*! path */ "path");
/* harmony import */ var path__WEBPACK_IMPORTED_MODULE_8___default = /*#__PURE__*/__webpack_require__.n(path__WEBPACK_IMPORTED_MODULE_8__);
/* harmony import */ var _material_ui_core__WEBPACK_IMPORTED_MODULE_9__ = __webpack_require__(/*! @material-ui/core */ "@material-ui/core");
/* harmony import */ var _material_ui_core__WEBPACK_IMPORTED_MODULE_9___default = /*#__PURE__*/__webpack_require__.n(_material_ui_core__WEBPACK_IMPORTED_MODULE_9__);
/* harmony import */ var react_router_dom__WEBPACK_IMPORTED_MODULE_10__ = __webpack_require__(/*! react-router-dom */ "react-router-dom");
/* harmony import */ var react_router_dom__WEBPACK_IMPORTED_MODULE_10___default = /*#__PURE__*/__webpack_require__.n(react_router_dom__WEBPACK_IMPORTED_MODULE_10__);












const styles = theme => ({
  millingStyle: {
    backgroundImage: `url(${"./static/img/milling-background.jpg"})`,
    backgroundSize: 'cover',
    overflow: 'hidden',
    width: '100%',
    height: '100%',
    position: 'fixed',
    left: 0,
    top: 0,
    z: -1,
    flex: 1,
    justifyContent: 'left',
    alignItems: 'left',
    display: 'flex',
    verticalAlign: 'middle'
  },
  stepsList: {
    width: 'calc(20% - 20px)',
    height: 'calc(100% - 120px)',
    marginTop: '30px',
    marginLeft: '10px',
    position: 'fixed'
  },
  middle: {
    width: 'calc(38% - 20px)',
    height: 'calc(100% - 110px)',
    marginTop: '60px',
    marginLeft: 'calc(20% + 10px)',
    position: 'fixed'
  },
  instructions: {
    width: '100%',
    height: '50%',
    postion: 'fixed'
  },
  warning: {
    height: '40px',
    textAlign: 'center'
  },
  actions: {
    textAlign: 'center'
  },
  right: {
    width: 'calc(42% - 20px)',
    height: 'calc(100% - 160px)',
    marginTop: '110px',
    marginLeft: 'calc(58% + 10px)'
  },
  prev: {
    float: 'left',
    padding: '5px' //marginLeft: -2 * theme.spacing.unit

  },
  next: {
    float: 'right',
    padding: '5px' //marginLeft: 2 * theme.spacing.unit

  },
  stepNumber: {
    marginTop: '6px',
    opacity: 0.87,
    fontSize: '14px',
    color: '#9f9f9f'
  }
});

class Milling extends react__WEBPACK_IMPORTED_MODULE_0___default.a.Component {
  constructor() {
    super();
    this.state = {
      steps: electron__WEBPACK_IMPORTED_MODULE_2__["ipcRenderer"].sendSync("Jobs::GetSteps"),
      selectedStepIndex: 0,
      selectedStep: electron__WEBPACK_IMPORTED_MODULE_2__["ipcRenderer"].sendSync("Jobs::GetStep", 0),
      previousMillingStep: 0,
      showImage: true,
      showStartMilling: false,
      goBack: false,
      millingProgress: -1,
      showAlert: false,
      alertMessage: ""
    };
  }

  componentDidMount() {
    electron__WEBPACK_IMPORTED_MODULE_2__["ipcRenderer"].send('DD_SetCurrentPage', "Milling");

    if (electron__WEBPACK_IMPORTED_MODULE_2__["ipcRenderer"].sendSync("Walkthrough::ShouldDisplay", "Milling")) {
      window.ShowMillingWalkthrough();
      electron__WEBPACK_IMPORTED_MODULE_2__["ipcRenderer"].send("Walkthrough::SetShowWalkthrough", "Milling", false);
    }
  }

  progress(milling) {
    const millingProgress = milling.state.millingProgress;

    if (millingProgress === 100) {
      clearInterval(milling.timer);
      milling.showNextStep(milling);
    } else {
      const updatedProgress = electron__WEBPACK_IMPORTED_MODULE_2__["ipcRenderer"].sendSync("Jobs::GetProgress", milling.state.selectedStepIndex);
      milling.setState({
        millingProgress: updatedProgress
      });
    }
  }

  showNextStep(milling) {
    const nextStepIndex = milling.state.selectedStepIndex + 1;

    if (nextStepIndex < milling.state.steps.length) {
      milling.setState({
        showStartMilling: false,
        millingProgress: -1,
        selectedStepIndex: nextStepIndex,
        selectedStep: electron__WEBPACK_IMPORTED_MODULE_2__["ipcRenderer"].sendSync("Jobs::GetStep", nextStepIndex)
      });
    } else {
      milling.setState({
        goBack: true
      });
    }
  }

  showPrevStep(milling) {
    const prevStepIndex = milling.state.selectedStepIndex - 1;
    milling.setState({
      showStartMilling: false,
      millingProgress: -1,
      selectedStepIndex: prevStepIndex,
      selectedStep: electron__WEBPACK_IMPORTED_MODULE_2__["ipcRenderer"].sendSync("Jobs::GetStep", prevStepIndex)
    });
  }

  skipToNextMillingStep(milling) {
    const stepIndex = milling.state.selectedStep.next_milling_step;
    milling.setState({
      showStartMilling: false,
      millingProgress: -1,
      selectedStepIndex: stepIndex,
      selectedStep: electron__WEBPACK_IMPORTED_MODULE_2__["ipcRenderer"].sendSync("Jobs::GetStep", stepIndex)
    });
  }

  render() {
    const {
      classes
    } = this.props;

    function getWarning(milling) {
      if (milling.state.selectedStep != null) {
        if (milling.state.selectedStep.GCode != null && milling.state.millingProgress == -1) {
          return react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_9__["Typography"], {
            align: "center",
            color: "error"
          }, "Warning!", react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("br", null), "GG will move after pressing start");
        }
      }

      return "";
    }

    function getMillingInProgressDisplay(milling) {
      if (milling.state.millingProgress >= 0) {
        return react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_9__["LinearProgress"], {
          variant: "determinate",
          color: "secondary",
          style: {
            height: '15px'
          },
          value: milling.state.millingProgress
        });
      }

      return "";
    }

    function handlePrev(event) {
      this.showPrevStep(this);
    }

    function handleNext(event) {
      if (this.state.selectedStep.GCode != null) {
        this.setState({
          showStartMilling: true
        });
      } else {
        this.showNextStep(this);
      }
    }

    function handleSkip(event) {
      this.skipToNextMillingStep(this);
    }

    function handleStop(event) {
      electron__WEBPACK_IMPORTED_MODULE_2__["ipcRenderer"].send("Jobs::EmergencyStop");
      clearInterval(this.timer);
      this.setState({
        millingProgress: -1,
        selectedStepIndex: 0,
        selectedStep: electron__WEBPACK_IMPORTED_MODULE_2__["ipcRenderer"].sendSync("Jobs::GetStep", 0),
        previousMillingStep: 0,
        showAlert: true,
        alertMessage: 'Emergency stop was pressed. Resetting job.'
      });
    }

    function handleCloseStartMilling(start) {
      if (start) {
        this.setState({
          millingProgress: 0,
          showStartMilling: false,
          previousMillingStep: this.state.selectedStepIndex
        });
        electron__WEBPACK_IMPORTED_MODULE_2__["ipcRenderer"].send("Jobs::StartMilling", this.state.selectedStepIndex);
        this.timer = setInterval(this.progress, 100, this);
      } else {
        this.setState({
          showStartMilling: false
        });
      }
    }

    function isNextAvailable(component) {
      return component.state.millingProgress == -1;
    }

    function isPrevAvailable(component) {
      if (component.state.millingProgress == -1) {
        if (component.state.selectedStepIndex == 0) {
          return false;
        }

        if (component.state.selectedStepIndex - 1 > component.state.previousMillingStep) {
          return true;
        }
      }

      return false;
    }

    function isSkipAvailable(component) {
      return component.state.selectedStep.next_milling_step != null;
    }

    function getActionButton(component) {
      if (component.state.millingProgress == -1) {
        return react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_9__["IconButton"], {
          onClick: handleNext.bind(component)
        }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("img", {
          style: {
            height: '90px'
          },
          onMouseOver: e => e.currentTarget.src = path__WEBPACK_IMPORTED_MODULE_8___default.a.join(__dirname, '../../static/img/next_hover.png'),
          onMouseOut: e => e.currentTarget.src = path__WEBPACK_IMPORTED_MODULE_8___default.a.join(__dirname, '../../static/img/next.png'),
          src: path__WEBPACK_IMPORTED_MODULE_8___default.a.join(__dirname, '../../static/img/next.png')
        }));
      } else {
        return react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_9__["IconButton"], {
          onClick: handleStop.bind(component)
        }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("img", {
          style: {
            height: '80px'
          },
          src: path__WEBPACK_IMPORTED_MODULE_8___default.a.join(__dirname, '../../static/img/stop_circle.png')
        }));
      }
    }

    if (this.state.goBack == true) {
      electron__WEBPACK_IMPORTED_MODULE_2__["ipcRenderer"].send('DD_SetCurrentPage', "Dashboard");
      return react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(react_router_dom__WEBPACK_IMPORTED_MODULE_10__["Redirect"], {
        to: "/"
      });
    }

    return react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(react__WEBPACK_IMPORTED_MODULE_0___default.a.Fragment, null, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_components_Modals_Alert__WEBPACK_IMPORTED_MODULE_7__["default"], {
      open: this.state.showAlert,
      message: this.state.alertMessage,
      close: event => {
        this.setState({
          showAlert: false
        });
      }
    }), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("section", {
      className: classes.millingStyle
    }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("section", {
      id: "steps",
      className: classes.stepsList
    }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_9__["Button"], {
      style: {
        marginTop: '5px'
      },
      onClick: event => {
        this.setState({
          goBack: true
        });
      }
    }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("img", {
      style: {
        height: '16px'
      },
      src: path__WEBPACK_IMPORTED_MODULE_8___default.a.join(__dirname, '../../static/img/back-to-main.png')
    })), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_components_StepList__WEBPACK_IMPORTED_MODULE_4__["default"], {
      steps: this.state.steps,
      selectedStep: this.state.selectedStepIndex
    }), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_9__["Grid"], {
      container: true,
      spacing: 0
    }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_9__["Grid"], {
      item: true,
      xs: 4
    }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_9__["Button"], {
      color: "secondary",
      disabled: !isPrevAvailable(this),
      className: classes.prev,
      onClick: handlePrev.bind(this)
    }, "< Prev")), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_9__["Grid"], {
      item: true,
      xs: 4
    }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("center", null, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_9__["Typography"], {
      className: classes.stepNumber
    }, "Step ", this.state.selectedStepIndex + 1, "/", this.state.steps.length))), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_9__["Grid"], {
      item: true,
      xs: 4
    }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_9__["Button"], {
      color: "secondary",
      disabled: !isNextAvailable(this),
      className: classes.next,
      onClick: handleNext.bind(this)
    }, "Next >"))), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_9__["Button"], {
      color: "secondary",
      disabled: !isSkipAvailable(this),
      className: classes.next,
      onClick: handleSkip.bind(this)
    }, "Skip to Next Milling Step >")), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("section", {
      id: "middle_section",
      className: classes.middle
    }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_components_Modals_StartMilling__WEBPACK_IMPORTED_MODULE_6__["default"], {
      open: this.state.showStartMilling,
      onClose: handleCloseStartMilling.bind(this)
    }), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("div", {
      className: classes.instructions
    }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_9__["Typography"], {
      variant: "subtitle1",
      style: {
        textTransform: 'uppercase'
      }
    }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("b", null, " ", this.state.selectedStep.Title, " ")), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("br", null), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_material_ui_core__WEBPACK_IMPORTED_MODULE_9__["Typography"], null, this.state.selectedStep.Prompt)), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("div", {
      className: classes.warning
    }, getMillingInProgressDisplay(this), getWarning(this)), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("div", {
      className: classes.actions
    }, getActionButton(this))), react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement("section", {
      id: "image",
      className: classes.right
    }, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(_components_ImageRaw__WEBPACK_IMPORTED_MODULE_5__["default"], {
      selectedStep: this.state.selectedStep,
      millingInProgress: this.state.millingProgress != -1
    }))));
  }

}

Milling.propTypes = {
  classes: prop_types__WEBPACK_IMPORTED_MODULE_1___default.a.object.isRequired
};
/* harmony default export */ __webpack_exports__["default"] = (_material_ui_core_styles_withStyles__WEBPACK_IMPORTED_MODULE_3___default()(styles)(Milling));

/***/ }),

/***/ "./src/Renderer/containers/Milling/index.js":
/*!**************************************************!*\
  !*** ./src/Renderer/containers/Milling/index.js ***!
  \**************************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony import */ var _Milling__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ./Milling */ "./src/Renderer/containers/Milling/Milling.js");

/* harmony default export */ __webpack_exports__["default"] = (_Milling__WEBPACK_IMPORTED_MODULE_0__["default"]);

/***/ }),

/***/ "./src/Renderer/renderApp.js":
/*!***********************************!*\
  !*** ./src/Renderer/renderApp.js ***!
  \***********************************/
/*! no exports provided */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony import */ var react__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! react */ "react");
/* harmony import */ var react__WEBPACK_IMPORTED_MODULE_0___default = /*#__PURE__*/__webpack_require__.n(react__WEBPACK_IMPORTED_MODULE_0__);
/* harmony import */ var react_dom__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! react-dom */ "react-dom");
/* harmony import */ var react_dom__WEBPACK_IMPORTED_MODULE_1___default = /*#__PURE__*/__webpack_require__.n(react_dom__WEBPACK_IMPORTED_MODULE_1__);
/* harmony import */ var react_hot_loader__WEBPACK_IMPORTED_MODULE_2__ = __webpack_require__(/*! react-hot-loader */ "react-hot-loader");
/* harmony import */ var react_hot_loader__WEBPACK_IMPORTED_MODULE_2___default = /*#__PURE__*/__webpack_require__.n(react_hot_loader__WEBPACK_IMPORTED_MODULE_2__);
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


 //import installExtension, { REACT_DEVELOPER_TOOLS } from 'electron-devtools-installer';

/*installExtension(REACT_DEVELOPER_TOOLS)
    .then((name) => console.log(`Added Extension:  ${name}`))
    .catch((err) => console.log('An error occurred: ', err));*/

const render = () => {
  const App = __webpack_require__(/*! ./App */ "./src/Renderer/App.js").default;

  react_dom__WEBPACK_IMPORTED_MODULE_1___default.a.render(react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(react_hot_loader__WEBPACK_IMPORTED_MODULE_2__["AppContainer"], null, react__WEBPACK_IMPORTED_MODULE_0___default.a.createElement(App, null)), document.getElementById('App'));
};

render();

if (false) {}

/***/ }),

/***/ "./src/Renderer/util/ScrollToTop.js":
/*!******************************************!*\
  !*** ./src/Renderer/util/ScrollToTop.js ***!
  \******************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony import */ var react__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! react */ "react");
/* harmony import */ var react__WEBPACK_IMPORTED_MODULE_0___default = /*#__PURE__*/__webpack_require__.n(react__WEBPACK_IMPORTED_MODULE_0__);
/* harmony import */ var react_router_dom__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! react-router-dom */ "react-router-dom");
/* harmony import */ var react_router_dom__WEBPACK_IMPORTED_MODULE_1___default = /*#__PURE__*/__webpack_require__.n(react_router_dom__WEBPACK_IMPORTED_MODULE_1__);



class ScrollToTop extends react__WEBPACK_IMPORTED_MODULE_0__["Component"] {
  componentDidUpdate(prevProps) {
    if (this.props.location.pathname !== prevProps.location.pathname) {
      window.scrollTo(0, 0);
    }
  }

  render() {
    return this.props.children;
  }

}

/* harmony default export */ __webpack_exports__["default"] = (Object(react_router_dom__WEBPACK_IMPORTED_MODULE_1__["withRouter"])(ScrollToTop));

/***/ }),

/***/ "@material-ui/core":
/*!************************************!*\
  !*** external "@material-ui/core" ***!
  \************************************/
/*! no static exports found */
/***/ (function(module, exports) {

module.exports = require("@material-ui/core");

/***/ }),

/***/ "@material-ui/core/colors":
/*!*******************************************!*\
  !*** external "@material-ui/core/colors" ***!
  \*******************************************/
/*! no static exports found */
/***/ (function(module, exports) {

module.exports = require("@material-ui/core/colors");

/***/ }),

/***/ "@material-ui/core/styles":
/*!*******************************************!*\
  !*** external "@material-ui/core/styles" ***!
  \*******************************************/
/*! no static exports found */
/***/ (function(module, exports) {

module.exports = require("@material-ui/core/styles");

/***/ }),

/***/ "@material-ui/core/styles/withStyles":
/*!******************************************************!*\
  !*** external "@material-ui/core/styles/withStyles" ***!
  \******************************************************/
/*! no static exports found */
/***/ (function(module, exports) {

module.exports = require("@material-ui/core/styles/withStyles");

/***/ }),

/***/ "@material-ui/icons/lens":
/*!******************************************!*\
  !*** external "@material-ui/icons/lens" ***!
  \******************************************/
/*! no static exports found */
/***/ (function(module, exports) {

module.exports = require("@material-ui/icons/lens");

/***/ }),

/***/ "custom-electron-titlebar":
/*!*******************************************!*\
  !*** external "custom-electron-titlebar" ***!
  \*******************************************/
/*! no static exports found */
/***/ (function(module, exports) {

module.exports = require("custom-electron-titlebar");

/***/ }),

/***/ "electron":
/*!***************************!*\
  !*** external "electron" ***!
  \***************************/
/*! no static exports found */
/***/ (function(module, exports) {

module.exports = require("electron");

/***/ }),

/***/ "path":
/*!***********************!*\
  !*** external "path" ***!
  \***********************/
/*! no static exports found */
/***/ (function(module, exports) {

module.exports = require("path");

/***/ }),

/***/ "prop-types":
/*!*****************************!*\
  !*** external "prop-types" ***!
  \*****************************/
/*! no static exports found */
/***/ (function(module, exports) {

module.exports = require("prop-types");

/***/ }),

/***/ "react":
/*!************************!*\
  !*** external "react" ***!
  \************************/
/*! no static exports found */
/***/ (function(module, exports) {

module.exports = require("react");

/***/ }),

/***/ "react-dom":
/*!****************************!*\
  !*** external "react-dom" ***!
  \****************************/
/*! no static exports found */
/***/ (function(module, exports) {

module.exports = require("react-dom");

/***/ }),

/***/ "react-hot-loader":
/*!***********************************!*\
  !*** external "react-hot-loader" ***!
  \***********************************/
/*! no static exports found */
/***/ (function(module, exports) {

module.exports = require("react-hot-loader");

/***/ }),

/***/ "react-router-dom":
/*!***********************************!*\
  !*** external "react-router-dom" ***!
  \***********************************/
/*! no static exports found */
/***/ (function(module, exports) {

module.exports = require("react-router-dom");

/***/ })

/******/ });
//# sourceMappingURL=renderApp.js.map
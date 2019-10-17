// Generated by BUCKLESCRIPT VERSION 5.0.6, PLEASE EDIT WITH CARE
'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Header$ReactHooksTemplate = require("./Header.bs.js");
var TodoStore$ReactHooksTemplate = require("./TodoStore.bs.js");
var MainSection$ReactHooksTemplate = require("./MainSection.bs.js");

function App(Props) {
  var dispatch = Curry._1(TodoStore$ReactHooksTemplate.AppStore[/* useDispatch */2], /* () */0);
  var state = Curry._1(TodoStore$ReactHooksTemplate.AppStore[/* useSelector */1], TodoStore$ReactHooksTemplate.selector);
  return React.createElement("div", {
              className: "todoapp"
            }, React.createElement(Header$ReactHooksTemplate.make, {
                  dispatch: dispatch
                }), React.createElement(MainSection$ReactHooksTemplate.make, {
                  state: state,
                  dispatch: dispatch
                }));
}

var make = App;

exports.make = make;
/* react Not a pure module */

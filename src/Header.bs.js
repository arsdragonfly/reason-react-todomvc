// Generated by BUCKLESCRIPT VERSION 5.0.6, PLEASE EDIT WITH CARE
'use strict';

var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var TodoTextInput$ReactHooksTemplate = require("./TodoTextInput.bs.js");

function Header(Props) {
  var dispatch = Props.dispatch;
  var match = React.useState((function () {
          return false;
        }));
  return React.createElement("header", {
              className: "header"
            }, React.createElement("h1", undefined, "todos"), React.createElement(TodoTextInput$ReactHooksTemplate.make, {
                  onSave: (function (text) {
                      if (text.length !== 0) {
                        return Curry._1(dispatch, /* AddTodo */Block.__(0, [text]));
                      } else {
                        return 0;
                      }
                    }),
                  placeholder: "What needs to be done?",
                  editing: match[0],
                  newTodo: true
                }));
}

var make = Header;

exports.make = make;
/* react Not a pure module */

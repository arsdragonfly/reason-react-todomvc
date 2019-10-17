// Generated by BUCKLESCRIPT VERSION 5.0.6, PLEASE EDIT WITH CARE
'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Belt_Array = require("bs-platform/lib/js/belt_Array.js");
var TodoStore$ReactHooksTemplate = require("./TodoStore.bs.js");
var FilterLink$ReactHooksTemplate = require("./FilterLink.bs.js");

function Footer(Props) {
  var state = Props.state;
  var dispatch = Props.dispatch;
  var todosCount = TodoStore$ReactHooksTemplate.getTodosCount(state);
  var completedCount = TodoStore$ReactHooksTemplate.getCompletedCount(state);
  var activeCount = todosCount - completedCount | 0;
  var itemWord = activeCount === 1 ? "item" : "items";
  return React.createElement("footer", {
              className: "footer"
            }, React.createElement("span", {
                  className: "todo-count"
                }, React.createElement("strong", undefined, activeCount === 0 ? "No" : String(activeCount), " " + (itemWord + " left"))), React.createElement("ul", {
                  className: "filters"
                }, Belt_Array.map(/* array */[
                      /* All */0,
                      /* Active */1,
                      /* Completed */2
                    ], (function (filter) {
                        return React.createElement("li", {
                                    key: TodoStore$ReactHooksTemplate.visibilityFilterToString(filter)
                                  }, React.createElement(FilterLink$ReactHooksTemplate.make, {
                                        children: TodoStore$ReactHooksTemplate.visibilityFilterToString(filter),
                                        filter: filter,
                                        state: state,
                                        dispatch: dispatch
                                      }));
                      }))), completedCount > 0 ? React.createElement("button", {
                    className: "clear-completed",
                    onClick: (function (param) {
                        return Curry._1(dispatch, /* ClearCompletedTodos */1);
                      })
                  }, "Clear completed") : null);
}

var make = Footer;

exports.make = make;
/* react Not a pure module */

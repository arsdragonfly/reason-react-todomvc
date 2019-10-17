// ReactDOMRe.renderToElementWithId(<Component1 message="Hello! Click this text." />, "index1");
// ReactDOMRe.renderToElementWithId(<TodoItem id=1 text="fa" completed=false />, "index1");

// ReactDOMRe.renderToElementWithId(<Component2 greeting="Hello!" />, "index2");

open TodoStore;

ReactDOMRe.renderToElementWithId(
  <AppStore.Provider store=appStore> <App /> </AppStore.Provider>,
  "index",
);
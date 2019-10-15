// ReactDOMRe.renderToElementWithId(<Component1 message="Hello! Click this text." />, "index1");
// ReactDOMRe.renderToElementWithId(<TodoItem id=1 text="fa" completed=false />, "index1");

// ReactDOMRe.renderToElementWithId(<Component2 greeting="Hello!" />, "index2");
type appState = int;

/* Action declaration */
type appAction =
  | Click;

let appReducer = (state, action) =>
  switch (action) {
  | Click => state + 1
  };

let stateSelector = state => state;

let appStore =
  Reductive.Store.create(
    ~reducer=appReducer,
    ~preloadedState=
      Dom.Storage2.localStorage
      ->Dom.Storage2.getItem("foo")
      ->Belt.Option.map(str => int_of_string(str))
      ->Belt.Option.getWithDefault(0),
    ~enhancer=
      (store, next, action) => {
        next(action);
        Dom.Storage2.localStorage->Dom.Storage2.setItem(
          "foo",
          string_of_int(Reductive.Store.getState(store)),
        );
      },
    (),
  );
module AppStore = {
  include ReductiveContext.Make({
    type action = appAction;
    type state = appState;
  });
};

module App = {
  [@react.component]
  let make = () => {
    let dispatch = AppStore.useDispatch();
    let state = AppStore.useSelector(stateSelector);
    <div>
      <button onClick={_event => dispatch(Click)}>
        {ReasonReact.string(string_of_int(state))}
      </button>
    </div>;
  };
};

ReactDOMRe.renderToElementWithId(
  <AppStore.Provider store=appStore> <App /> </AppStore.Provider>,
  "index2",
);
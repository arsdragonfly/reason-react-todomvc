type todoItem = {
  text: string,
  completed: bool,
  id: int,
};

let makeTodoItem = (text, completed, id) => {text, completed, id};

type visibilityFilter =
  | All
  | Active
  | Completed;

let visibilityFilterToString = filter =>
  switch (filter) {
  | All => "All"
  | Active => "Active"
  | Completed => "Completed"
  };

let parseVisibilityFilter = str =>
  switch (str) {
  | "All" => Some(All)
  | "Active" => Some(Active)
  | "Completed" => Some(Completed)
  | _ => None
  };

type appState = {
  todoItems: array(todoItem),
  visibilityFilter,
};

let makeAppState = (todoItems, visibilityFilter) => {
  todoItems,
  visibilityFilter,
};

type appAction =
  | AddTodo(string)
  | DeleteTodo(int)
  | EditTodo(int, string)
  | ToggleTodo(int)
  | ToggleAllTodos
  | ClearCompletedTodos
  | SetVisibilityFilter(visibilityFilter);

module Decode = Decode.AsResult.OfParseError;

let decodeTodoItem = json =>
  Decode.Pipeline.(
    succeed(makeTodoItem)
    |> field("text", string)
    |> field("completed", boolean)
    |> field("id", intFromNumber)
    |> run(json)
  );

let decodeStore = json =>
  Decode.Pipeline.(
    succeed(makeAppState)
    |> field("todoItems", Decode.array(decodeTodoItem))
    |> field(
         "visibilityFilter",
         Decode.variantFromString(parseVisibilityFilter),
       )
    |> run(json)
  );

let decodeStoreWithDefault = json =>
  decodeStore(json)
  ->Belt.Result.getWithDefault({todoItems: [||], visibilityFilter: All});

let encodeTodoItem = (t: todoItem) =>
  Json.Encode.(
    object_([
      ("text", string(t.text)),
      ("completed", bool(t.completed)),
      ("id", int(t.id)),
    ])
  );

let encodeStore = (s: appState) =>
  Json.Encode.(
    object_([
      ("todoItems", array(encodeTodoItem, s.todoItems)),
      (
        "visibilityFilter",
        string(visibilityFilterToString(s.visibilityFilter)),
      ),
    ])
  );

open Dom.Storage2;

let setStore = (s: appState) =>
  localStorage->setItem("store", encodeStore(s)->Js.Json.stringify);

let getStore = () =>
  localStorage
  ->getItem("store")
  ->Belt.Option.getWithDefault(
      {|{"todoItems": [], "visibilityFilter": "All"}|},
    )
  ->Js.Json.parseExn
  ->decodeStoreWithDefault;

let addTodo = (text: string, s: appState) => {
  ...s,
  todoItems:
    Array.append(
      s.todoItems,
      [|
        {
          id:
            s.todoItems
            ->Belt.Array.reduce(-1, (maxId, todo) => max(todo.id, maxId) + 1)
            + 1,
          completed: false,
          text,
        },
      |],
    ),
};

let deleteTodo = (id, s: appState) => {
  ...s,
  todoItems: s.todoItems->Belt.Array.keep(todo => todo.id == id),
};

let editTodo = (id, text, s: appState) => {
  ...s,
  todoItems:
    s.todoItems
    ->Belt.Array.map(todo =>
        if (todo.id == id) {
          {...todo, text};
        } else {
          todo;
        }
      ),
};

let toggleTodo = (id, s: appState) => {
  ...s,
  todoItems:
    s.todoItems
    ->Belt.Array.map(todo =>
        if (todo.id == id) {
          {...todo, completed: !todo.completed};
        } else {
          todo;
        }
      ),
};

let toggleAllTodos = (s: appState) => {
  let areAllMarked = s.todoItems->Belt.Array.every(todo => todo.completed);
  {
    ...s,
    todoItems:
      s.todoItems
      ->Belt.Array.map(todo => {...todo, completed: !areAllMarked}),
  };
};

let clearCompletedTodos = (s: appState) => {
  ...s,
  todoItems: s.todoItems->Belt.Array.keep(todo => !todo.completed),
};

let getTodosCount = (s: appState) => s.todoItems->Belt.Array.length;

let getCompletedCount = (s: appState) =>
  s.todoItems
  ->Belt.Array.reduce(0, (count, todo) =>
      if (todo.completed) {
        count + 1;
      } else {
        count;
      }
    );

let setVisibilityFilter = (filter, s: appState) => {
  ...s,
  visibilityFilter: filter,
};

let getFilteredTodos = (filter, s: appState) => {
  let filter =
    switch (filter) {
    | Completed => (
        todoItems => Belt.Array.keep(todoItems, todo => todo.completed)
      )
    | Active => (
        todoItems => Belt.Array.keep(todoItems, todo => !todo.completed)
      )
    | All => (todoItems => todoItems)
    };
  s.todoItems->filter
};

let appReducer = (state, action) =>
  (
    switch (action) {
    | AddTodo(text) => addTodo(text)
    | DeleteTodo(id) => deleteTodo(id)
    | EditTodo(id, text) => editTodo(id, text)
    | ToggleTodo(id) => toggleTodo(id)
    | ToggleAllTodos => toggleAllTodos
    | ClearCompletedTodos => clearCompletedTodos
    | SetVisibilityFilter(filter) => setVisibilityFilter(filter)
    }
  )(
    state,
  );

let appStore =
  Reductive.Store.create(
    ~reducer=appReducer,
    ~preloadedState=getStore(),
    ~enhancer=
      (store, next, action) => {
        next(action);
        setStore(store->Reductive.Store.getState);
      },
    (),
  );
module AppStore = {
  include ReductiveContext.Make({
    type action = appAction;
    type state = appState;
  });
};
let selector = state => state;
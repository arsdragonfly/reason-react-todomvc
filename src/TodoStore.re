type todoItem = {
  text: string,
  completed: bool,
  id: int,
};

let makeTodoItem = (text, completed, id) => {text, completed, id};

type store = {
  todoItems: array(todoItem),
  visibilityFilter: string,
};

let makeStore = (todoItems, visibilityFilter) => {
  todoItems,
  visibilityFilter,
};

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
    succeed(makeStore)
    |> field("todoItems", Decode.array(decodeTodoItem))
    |> field("visibilityFilter", string)
    |> run(json)
  );

let encodeTodoItem = (t: todoItem) =>
  Json.Encode.(
    object_([
      ("text", string(t.text)),
      ("completed", bool(t.completed)),
      ("id", int(t.id)),
    ])
  );

let encodeStore = (s: store) =>
  Json.Encode.(
    object_([
      ("todoItems", array(encodeTodoItem, s.todoItems)),
      ("visibilityFilter", string(s.visibilityFilter)),
    ])
  );

open Dom.Storage2;

let setStore = (s: store) =>
  localStorage->setItem("store", encodeStore(s)->Js.Json.stringify);

let getStore = () =>
  localStorage
  ->getItem("store")
  ->Belt.Option.getWithDefault("{todoItems: [], visibilityFilter: \"All\"}")
  ->Js.Json.parseExn
  ->decodeStore;

let updateStore = (updater: store => store) =>
  getStore()->Belt.Result.map(updater)->Belt.Result.map(setStore);

let addTodo = (text: string) =>
  updateStore((s: store) =>
    {
      ...s,
      todoItems:
        Array.append(
          s.todoItems,
          [|
            {
              id:
                s.todoItems
                ->Belt.Array.reduce(-1, (maxId, todo) =>
                    max(todo.id, maxId) + 1
                  )
                + 1,
              completed: false,
              text,
            },
          |],
        ),
    }
  );

let deleteTodo = id =>
  updateStore((s: store) =>
    {...s, todoItems: s.todoItems->Belt.Array.keep(todo => todo.id == id)}
  );

let editTodo = (id, text) =>
  updateStore((s: store) =>
    {
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
    }
  );

let toggleTodo = id =>
  updateStore((s: store) =>
    {
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
    }
  );

let completeAllTodos = () =>
  updateStore((s: store) => {
    let areAllMarked = s.todoItems->Belt.Array.every(todo => todo.completed);
    {
      ...s,
      todoItems:
        s.todoItems
        ->Belt.Array.map(todo => {...todo, completed: !areAllMarked}),
    };
  });

let clearCompletedTodos = () =>
  updateStore((s: store) =>
    {...s, todoItems: s.todoItems->Belt.Array.keep(todo => !todo.completed)}
  );

let getTodosCount = () =>
  getStore()
  ->Belt.Result.map((s: store) => s.todoItems->Belt.Array.length)
  ->Belt.Result.getWithDefault(0);

let getCompletedCount = () =>
  getStore()
  ->Belt.Result.map((s: store) =>
      s.todoItems
      ->Belt.Array.reduce(0, (count, todo) =>
          if (todo.completed) {
            count + 1;
          } else {
            count;
          }
        )
    )
  ->Belt.Result.getWithDefault(0);

let setVisibilityFilter = filter =>
  updateStore((s: store) => {...s, visibilityFilter: filter});

let getFilteredTodos = filter => {
  let filter =
    switch (filter) {
    | "Completed" => (
        todoItems => Belt.Array.keep(todoItems, todo => todo.completed)
      )
    | "Active" => (
        todoItems => Belt.Array.keep(todoItems, todo => !todo.completed)
      )
    | _ => (todoItems => todoItems)
    };
  getStore()
  ->Belt.Result.map((s: store) => s.todoItems->filter)
  ->Belt.Result.getWithDefault([||]);
};
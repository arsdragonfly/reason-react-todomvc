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
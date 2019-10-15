[@react.component]
let make = (~id, ~text, ~completed) => {
  let (editing, setEditing) = React.useState(() => false);
  let handleDoubleClick = () => setEditing(_ => true);
  let handleSave = (id, text) =>
    if (text->String.length == 0) {
      TodoStore.deleteTodo(id)->Belt.Result.getWithDefault();
    } else {
      TodoStore.editTodo(id, text)->Belt.Result.getWithDefault();
    };
  let element =
    if (editing) {
      <TodoTextInput
        text
        editing
        onSave={text => handleSave(id, text)}
        newTodo=false
        placeholder=""
      />;
    } else {
      <div className="view">
        <input
          className="toggle"
          type_="checkbox"
          checked=completed
          onChange={_ =>
            TodoStore.toggleTodo(id)->Belt.Result.getWithDefault()
          }
        />
        <label onDoubleClick={_ => handleDoubleClick()}>
          {ReasonReact.string(text)}
        </label>
        <button
          className="destroy"
          onClick={_ =>
            TodoStore.deleteTodo(id)->Belt.Result.getWithDefault()
          }
        />
      </div>;
    };
  <li
    className={Cn.make([
      "completed"->Cn.ifTrue(completed),
      "editing"->Cn.ifTrue(editing),
    ])}>
    element
  </li>;
};
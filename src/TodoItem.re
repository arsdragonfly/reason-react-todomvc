[@react.component]
let make = (~id, ~text, ~completed, ~dispatch) => {
  open TodoStore;
  let (editing, setEditing) = React.useState(() => false);
  let handleDoubleClick = () => setEditing(_ => true);
  let handleSave = (id, text) => {
    if (text->String.length == 0) {
      dispatch(DeleteTodo(id));
    } else {
      dispatch(EditTodo(id, text));
    };
    setEditing(_ => false)
  }
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
          onChange={_ => dispatch(ToggleTodo(id))}
        />
        <label onDoubleClick={_ => handleDoubleClick()}>
          {ReasonReact.string(text)}
        </label>
        <button
          className="destroy"
          onClick={_ => dispatch(DeleteTodo(id))}
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
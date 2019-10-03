[@react.component]
let make = (~onSave, ~text="", ~placeholder, ~editing, ~newTodo) => {
  let (text, setText) = React.useState(() => text);
  let handleBlur = e =>
    if (!newTodo) {
      onSave(e->ReactEvent.Focus.target##value);
    };
  let handleChange = e => {
    setText(e->ReactEvent.Form.target##value);
  };
  let handleSubmit = e => {
    let text = String.trim(e->ReactEvent.Keyboard.target##value);
    if (e->ReactEvent.Keyboard.which === 13) {
      onSave(text);
      if (newTodo) {
        setText(_ => "");
      };
    };
  };
  <input
    className={Cn.make([
      "edit"->Cn.ifTrue(editing),
      "new-todo"->Cn.ifTrue(newTodo),
    ])}
    type_="text"
    placeholder
    autoFocus=true
    value=text
    onBlur=handleBlur
    onChange=handleChange
    onKeyDown=handleSubmit
  />;
};
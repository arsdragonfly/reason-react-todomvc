[@react.component]
let make = (~dispatch) => {
  open TodoStore;
  let (editing, _) = React.useState(() => false);
  <header className="header">
    <h1> {ReasonReact.string("todos")} </h1>
    <TodoTextInput
      editing
      newTodo=true
      onSave={text =>
        if (String.length(text) != 0) {
          dispatch(AddTodo(text));
        }
      }
      placeholder="What needs to be done?"
    />
  </header>;
};
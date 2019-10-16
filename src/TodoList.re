[@react.component]
let make = (~state, ~dispatch) => {
  open TodoStore;
  <ul className="todo-list">
    {ReasonReact.array(
       getFilteredTodos(state.visibilityFilter, state)
       ->Belt.Array.map(todo =>
           <TodoItem
             id={todo.id}
             text={todo.text}
             completed={todo.completed}
             dispatch
           />
         ),
     )}
  </ul>;
};
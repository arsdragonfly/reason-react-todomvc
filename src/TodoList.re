[@react.component]
let make = (~state, ~dispatch) => {
  TodoStore.(
    <ul className="todo-list">
      {ReasonReact.array(
         getFilteredTodos(state.visibilityFilter, state)
         ->Belt.Array.map(todo =>
             <TodoItem
               key={string_of_int(todo.id)}
               id={todo.id}
               text={todo.text}
               completed={todo.completed}
               dispatch
             />
           ),
       )}
    </ul>
  );
};
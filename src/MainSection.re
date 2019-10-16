[@react.component]
let make = (~state, ~dispatch) => {
  open TodoStore;
  let todosCount = getTodosCount(state);
  let completedCount = getCompletedCount(state);
  <section className="main">
    <span>
      <input
        className="toggle-all"
        type_="checkbox"
        defaultChecked={completedCount == todosCount}
        onChange={_ => dispatch(ToggleAllTodos)}
      />
      <label htmlFor="toggle-all" />
    </span>
    <TodoList state dispatch />
  </section>;
};
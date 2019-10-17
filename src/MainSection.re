[@react.component]
let make = (~state, ~dispatch) => {
  open TodoStore;
  let todosCount = getTodosCount(state);
  let completedCount = getCompletedCount(state);
  <section className="main">
    {if (todosCount > 0) {
       <span>
         <input
           className="toggle-all"
           type_="checkbox"
           defaultChecked={completedCount == todosCount}
         />
         <label
           htmlFor="toggle-all"
           onClick={_ => dispatch(ToggleAllTodos)}
         />
       </span>;
     } else {
       ReasonReact.null;
     }}
    <TodoList state dispatch />
    {if (todosCount > 0) {
       <Footer state dispatch />;
     } else {
       ReasonReact.null;
     }}
  </section>;
};
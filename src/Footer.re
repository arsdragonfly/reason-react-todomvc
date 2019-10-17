[@react.component]
let make = (~state, ~dispatch) => {
  open TodoStore;
  let todosCount = getTodosCount(state);
  let completedCount = getCompletedCount(state);
  let activeCount = todosCount - completedCount;
  let itemWord =
    if (activeCount == 1) {
      "item";
    } else {
      "items";
    };
  <footer className="footer">
    <span className="todo-count">
      <strong>
        {React.string(
           if (activeCount == 0) {
             "No";
           } else {
             string_of_int(activeCount);
           },
         )}
        {React.string(" " ++ itemWord ++ " " ++ "left")}
      </strong>
    </span>
    <ul className="filters">
      {ReasonReact.array(
         {[|All, Active, Completed|]
          ->Belt.Array.map(filter =>
              <li key={visibilityFilterToString(filter)}>
                <FilterLink filter state dispatch>
                  {React.string(visibilityFilterToString(filter))}
                </FilterLink>
              </li>
            )},
       )}
    </ul>
    {if (completedCount > 0) {
       <button
         className="clear-completed"
         onClick={_ => dispatch(ClearCompletedTodos)}>
         {React.string("Clear completed")}
       </button>;
     } else {
       React.null;
     }}
  </footer>;
};
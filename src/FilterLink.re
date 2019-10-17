[@react.component]
let make = (~children, ~filter, ~state, ~dispatch) => {
  open TodoStore;
  let visibilityFilter = state.visibilityFilter;
  <a
    className={Cn.ifTrue("selected", filter == visibilityFilter)}
    style={ReactDOMRe.Style.make(~cursor="pointer", ())}
    onClick={_ => dispatch(SetVisibilityFilter(filter))}>
    children
  </a>;
};
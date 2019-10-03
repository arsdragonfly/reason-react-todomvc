open Dom.Storage2;
[@react.component]
let make = (~id, ~text, ~completed) => {
  let (editing, setEditing) = React.useState(() => false);
  localStorage->setItem("token", "tk");
  let token = localStorage->getItem("token");

  switch token {
  | Some(str) => <li>{ReasonReact.string(str)}</li>
  | None => <li></li>
  }
  // <li className={Cn.make(["completed"->Cn.ifTrue(completed)])} />;
};
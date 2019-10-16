[@react.component]
let make = () => {
  open TodoStore;
  let dispatch = AppStore.useDispatch();
  let state = AppStore.useSelector(selector);
  <div> <Header dispatch /> <MainSection state dispatch /> </div>;
};
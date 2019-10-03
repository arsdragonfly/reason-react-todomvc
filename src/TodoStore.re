type todoItem = {
    text: string,
    completed: bool,
    id: int,
};

type store = {
    todoItems: array(todoItem),
    visibilityFilter: string,
};

Simple doubly linked list of heap-allocated strings.

Usage:
```c
list* l = init_l();
// l->head == NULL;
// l->tail == NULL;

insert(l, "goku");
// insert goku to the end of the list 
// l->head == goku;
// l->tail == NULL;

insert(l, "gohan");
// l->head == goku;
// l->tail == gohan;
// l->head->next == gohan;
// l->tail->prev == goku;

node* n = search(l, "goku");
delete(l, n);

free_l(l);
```

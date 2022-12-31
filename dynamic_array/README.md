Simple dynamically heap-allocated integers array.
The array will auto double its capacity when its current length exceeds its capacity.
It has 4 APIs:
- `Array* init(size_t cap)` to init a new array of size `cap`
- `void set(Array* arr, int index, int value)`
- `int get(Array* arr, int index)`
- `void free_array(Array* arr)`

Usage:

```c
// initialize a new array with 10 elements
Array* arr = init(10);
get(arr, 0); // 0
set(arr, 0, 1);
get(arr, 0); // 1

get(arr, 10); // out of bound error
set(arr, 10, 1); // out of bound error

free_array(arr);
```

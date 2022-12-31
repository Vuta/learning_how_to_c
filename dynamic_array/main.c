#include <stdlib.h>
#include <stdio.h>

#define BASE_CAP 10

typedef struct {
	int** indices;
	size_t len;
	size_t cap;
} Array;

Array* init(size_t cap);
void set(Array* arr, int index, int value);
int get(Array* arr, int index);
void free_array(Array* arr);
static void resize(Array* arr);

int main() {
	Array* a = init(BASE_CAP);

	puts("-----Initial values-------");
	for (int i = 0; i < a->cap; i++) {
		printf("i = %d, value = %d\n", i, get(a, i));
	}
	puts("--------------------------");

	set(a, 0, 1);
	set(a, 1, 2);
	set(a, 2, 3);
	set(a, 3, 4);
	set(a, 6, 5);
	set(a, 8, 5);
	set(a, 18, 5);

	for (int i = 0; i < a->cap; i++) {
		printf("i = %d, value = %d\n", i, get(a, i));
	}

	free_array(a);

	return 0;
}

Array* init(size_t cap) {
	Array* arr = malloc(sizeof(Array));
	arr->indices = calloc(cap, sizeof(int*));
	arr->len = 0;
	arr->cap = cap;

	return arr;
}

int get(Array* arr, int index) {
	if (arr->cap <= index) {
		fprintf(stderr, "ERROR: out of bound");

		exit(1);
	}

	if (arr->indices[index] != NULL) {
		return *arr->indices[index];
	} else {
		return 0;
	}
}

void set(Array *arr, int index, int value) {
	if (arr->cap <= index && index != 0) {
		fprintf(stderr, "ERROR: out of bound");

		exit(1);
	}

	if (arr->len >= arr->cap / 2) {
		resize(arr);
	}

	arr->indices[index] = malloc(sizeof(int));
	*arr->indices[index] = value;
	arr->len++;
}

void free_array(Array* arr) {
	for (int i = 0; i < arr->cap; i++) {
		free(arr->indices[i]);
	}

	free(arr);
}

static void resize(Array* arr) {
	int** new_indices = calloc(arr->cap * 2, sizeof(int*));
	for (int i = 0; i < arr->cap; i++) {
		new_indices[i] = arr->indices[i];
	}
	arr->cap = arr->cap * 2;
	arr->indices = new_indices;
}

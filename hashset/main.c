/* Naive implementation of an integer hashset.
	 Use chaining approach with a linked list to handle collison.
	 Hash function is a simple modulo operation.
	 The hashset supports 3 operations:
	 1) void add_element(hashset* hs, int value) - add a new element into set
	 2) void remove_element(hashset* hs, int value) - remove the element from the set if it exists
	 3) int contains(hashset* hs, int value) - check if the value exists in the set
*/

#include <stdlib.h>
#include <stdio.h>

typedef struct node_ {
	int val;
	struct node_* next;
} node;

typedef struct {
	int cap;
	node** set;
} hashset;

hashset* new_hashset(int cap);
void add_element(hashset* hs, int value);
void remove_element(hashset* hs, int value);
int contains(hashset* hs, int value);
void free_hashset(hashset *hs);

static int hash(hashset* hs, int value);
static node* new_node(int value, node* next);
static void free_node(node* nod);

int main() {
	hashset* hs = new_hashset(1000);

	add_element(hs, 1);
	add_element(hs, 2);
	printf("%s\n", contains(hs, 1) == 1 ? "true" : "false"); // true
	printf("%s\n", contains(hs, 3) == 1 ? "true" : "false"); // false

	add_element(hs, 2);
	printf("%s\n", contains(hs, 2) == 1 ? "true" : "false"); // true

	remove_element(hs, 2);
	printf("%s\n", contains(hs, 2) == 1 ? "true" : "false"); // false

	add_element(hs, 1001);
	printf("%s\n", contains(hs, 1001) == 1 ? "true" : "false"); // true

	remove_element(hs, 1);
	printf("%s\n", contains(hs, 1001) == 1 ? "true" : "false"); // true

	free_hashset(hs);

	return 0;
}

int hash(hashset* hs, int value) {
	int index = value % hs->cap;

	return index;
}

void add_element(hashset* hs, int value) {
	int index = hash(hs, value);
	node* cur = hs->set[index];

	if (cur == NULL) {
		node* nod = new_node(value, NULL);
		hs->set[index] = nod;
	} else if (cur->val != value) {
		node* nod = new_node(value, cur);
		hs->set[index] = nod;
	}
}

void remove_element(hashset* hs, int value) {
	int index = hash(hs, value);
	node* cur = hs->set[index];

	if (cur != NULL) {
		if (cur->val == value) {
			hs->set[index] = hs->set[index]->next;
		} else {
			while (cur != NULL) {
				node* prev = cur;
				cur = cur->next;
				if (cur != NULL && cur->val == value) {
					prev->next = cur->next;
					break;
				}
			}
		}
	}
}

int contains(hashset* hs, int value) {
	int index = hash(hs, value);
	node* cur = hs->set[index];
	while (cur != NULL) {
		if (cur->val == value) {
			return 1;
		}

		cur = cur->next;
	}

	return 0;
}

hashset* new_hashset(int cap) {
	hashset* hs = malloc(sizeof(hashset));
	hs->cap = cap;
	hs->set = calloc(cap, sizeof(node*));

	return hs;
}

node* new_node(int value, node* next) {
	node* nod = (struct node*)malloc(sizeof(node));
	nod->val = value;
	nod->next = next;

	return nod;
}

void free_node(node* nod) {
	while (nod != NULL) {
		node* next = nod->next;
		free(nod);
		nod = next;
	}
}

void free_hashset(hashset *hs) {
	for (int i = 0; i < hs->cap; i++) {
	 	if (hs->set[i] != NULL) {
	 	 	free_node(hs->set[i]);
		}
	}

	free(hs->set);
	free(hs);
}

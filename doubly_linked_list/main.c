#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _node {
	char* val;
	struct _node* next;
	struct _node* prev;
} node;

typedef struct {
	node* head;
	node* tail;
} list;

node* init_n(char* val) {
	node* n = malloc(sizeof(node));
	n->val = val;
	n->next = NULL;
	n->prev = NULL;

	return n;
}

list* init_l() {
	list* l = malloc(sizeof(list));
	l->head = NULL;
	l->tail = NULL;

	return l;
}

void free_l(list* l) {
	while (l->head != NULL) {
		node* temp = l->head;
		l->head = l->head->next;
		free(temp);
	}

	free(l);
}

// search node with value val in the list
node* search(list* l, char* val) {
	if (l->head == NULL) {
		return NULL;
	}

	node* n = l->head;
	while (n != NULL) {
		if (strcmp(n->val, val) == 0) {
			return n;
		}
		n = n->next;
	}

	return NULL;
}

// insert at the end
void insert(list* l, char* val) {
	node* new_node = init_n(val);
	if (l->head == NULL) {
		l->head = new_node;
	} else {
		if (l->tail == NULL) {
			l->tail = new_node;
			l->head->next = new_node;
			new_node->prev = l->head;
		} else {
			l->tail->next = new_node;
			new_node->prev = l->tail;
			l->tail = new_node;
		}
	}
}

// delete node n in the list
void delete(list* l, node* n) {
	if (l->head == NULL) {
		fprintf(stderr, "%s", "ERROR: Deleting empty list\n");
		exit(1);
	}

	if (n == NULL) {
		fprintf(stderr, "%s", "ERROR: Deleting NULL node\n");
		exit(1);
	}

	if (!search(l, n->val)) {
		fprintf(stderr, "%s", "ERROR: Deleting non existed node\n");
		exit(1);
	}

	// bug
	if (l->head == n) {
		l->head->next->prev = NULL;
		l->head = l->head->next;
	} else if (l->tail == n) {
		l->tail->prev->next = NULL;
		l->tail = l->tail->prev;
	} else {
		node* next = n->next;
		node* prev = n->prev;
		prev->next = next;
		next->prev = prev;
	}

	free(n);
}

void print_list(list* l) {
	node* temp = l->head;
	while (temp != NULL) {
		printf("addr = %p, val = %s\n", temp, temp->val);
		temp = temp->next;
	}
}

int main() {
	list* l = init_l();
	char* names[] = {"james", "goku", "mr.x", "long"};
	for (int i = 0; i < 4; i++) {
		insert(l, names[i]);
	}

	printf("head addr = %p, val = %s\n", l->head, l->head->val);
	printf("tail addr = %p, val = %s\n", l->tail, l->tail->val);
	print_list(l);
	printf("--------------------------------------------------\n");

	node* james = search(l, "james");
	if (james == l->head) {
		printf("node james found at %p\n", james);
	} else {
		printf("BUGGGGG\n");
	}

	node* goku = search(l, "goku");
	if (goku == james->next && goku->prev == james) {
		printf("node goku found at %p\n", goku); 
	} else {
		printf("BUGGGGG\n");
	}

	node* mrx = search(l, "mr.x");
	if (mrx == goku->next && mrx->prev == goku) {
		printf("node mr.x found at %p\n", mrx); 
	} else {
		printf("BUGGGGG\n");
	}

	node* lg = search(l, "long");
	if (lg == l->tail && mrx->next == lg && lg->prev == mrx) {
		printf("node long found at %p\n", lg); 
	} else {
		printf("BUGGGGG\n");
	}

	printf("--------------------------------------------------\n");
	printf("deleting goku ...\n");
	delete(l, goku);
	goku = search(l, "goku");
	if (goku == NULL) {
		printf("done\n");
		printf("head addr = %p, val = %s\n", l->head, l->head->val);
		printf("tail addr = %p, val = %s\n", l->tail, l->tail->val);
		print_list(l);
	} else {
		printf("BUGGGGG\n");
	}

	printf("--------------------------------------------------\n");
	printf("deleting james ...\n");
	delete(l, james);
	james = search(l, "james");
	if (james == NULL) {
		printf("done\n");
		printf("head addr = %p, val = %s\n", l->head, l->head->val);
		printf("tail addr = %p, val = %s\n", l->tail, l->tail->val);
		print_list(l);
	} else {
		printf("BUGGGGG\n");
	}

	free_l(l);

	return 0;
}

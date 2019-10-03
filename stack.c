#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long ULL;

#define STACK(T) struct stack_##T##_node { \
	T data; \
	struct stack_##T##_node* next; \
}; \
struct stack_##T { \
	struct stack_##T##_node* root; \
	ULL size; \
}; \
void stack_##T##_node_init(struct stack_##T##_node* node, T data, struct stack_##T##_node* next) { \
	node->data = data; \
	node->next = next; \
} \
void stack_##T##_init(struct stack_##T* stk) { \
	stk->size = 0; \
	stk->root = NULL; \
} \
void stack_##T##_push(struct stack_##T* stk, T val) { \
	if (stk->root) { \
		struct stack_##T##_node* node = malloc(sizeof(struct stack_##T##_node)); \
		stack_##T##_node_init(node, val, stk->root); \
		stk->root = node; \
	} \
	else { \
		stk->root = malloc(sizeof(struct stack_##T##_node)); \
		stack_##T##_node_init(stk->root, val, NULL); \
	} \
	stk->size++; \
} \
void stack_##T##_pop(struct stack_##T* stk) { \
	if (stk->size == 0) return; \
	stk->size--; \
	free(stk->root); \
	stk->root = stk->root->next; \
} \
void stack_##T##_free(struct stack_##T* stk) { \
	struct stack_##T##_node* node = stk->root; \
	while (node) { \
		struct stack_##T##_node* nxt = node->next; \
		free(node); \
		node = nxt; \
	} \
} \
T stack_##T##_top(struct stack_##T* stk) { \
	return stk->root->data; \
} \
T stack_##T##_empty(struct stack_##T* stk) { \
	return stk->size == 0; \
}

STACK(int)

int main() {
	struct stack_int stack;
	stack_int_init(&stack);
	stack_int_push(&stack, 0);
	printf("%d\n", stack_int_top(&stack));
	stack_int_push(&stack, 1);
	printf("%d\n", stack_int_top(&stack));
	stack_int_push(&stack, 2);
	printf("%d\n", stack_int_top(&stack));
	stack_int_pop(&stack);
	printf("%d\n", stack_int_top(&stack));
	stack_int_free(&stack);
	return 0;
}

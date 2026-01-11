#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "util.h"

/********************************************************************
 * list_node_t
 ********************************************************************/

/**
 * Construit et initialise un nouveau nœud d'une liste doublement chaînée.
 * Le paramètre \p data correspond à la donnée à affecter au nouveau nœud.
 * 
 * @param[in] data
 * @return le nouveau nœud créé
 */
static struct list_node_t * new_list_node(void * data) {
	struct list_node_t * node = malloc(sizeof(struct list_node_t));
	node->data = data;
	node->predecessor = NULL;
	node->successor = NULL;
	return node;
}

void * get_list_node_data(const struct list_node_t * node) {
	assert(node);
	return node->data;
}

struct list_node_t * get_successor(const struct list_node_t * node) {
	assert(node);
	return node->successor;
}

struct list_node_t * get_predecessor(const struct list_node_t * node) {
	assert(node);
	return node->predecessor;
}

void set_list_node_data(struct list_node_t * node, void * new_data) {
	assert(node);
	node->data = new_data;
}

void set_successor(struct list_node_t * node, struct list_node_t * new_successor) {
	assert(node);
	node->successor = new_successor;
}

void set_predecessor(struct list_node_t * node, struct list_node_t * new_predecessor) {
	assert(node);
	node->predecessor = new_predecessor;
}

/********************************************************************
 * list_t (Double-Linked List)
 ********************************************************************/

struct list_t * new_list() {
	struct list_t * L = malloc(sizeof(struct list_t));
	L->head = NULL;
	L->tail = NULL;
	L->size = 0;
	return L;
}

int list_is_empty(const struct list_t * L) {
	assert(L);
	if (get_list_size(L) == 0) {
		return 1;
	}
	return 0;
}

unsigned int get_list_size(const struct list_t * L) {
	assert(L);
	return L->size;
}

struct list_node_t * get_list_head(const struct list_t * L) {
	assert(L);
	return L->head;
}

struct list_node_t * get_list_tail(const struct list_t * L) {
	assert(L);
	return L->tail;
}

void increase_list_size(struct list_t * L) {
	assert(L);
	L->size++;
}

void decrease_list_size(struct list_t * L) {
	assert(L);
	if (get_list_size(L) == 0) {
		ShowMessage("Erreur : decrease_list_size -> list_t ne peut pas être inférieur à 0", 1);
	}
	L->size--;
}

void set_list_size(struct list_t * L, unsigned int new_size) {
	assert(L);
	L->size = new_size;
}

void set_list_head(struct list_t * L, struct list_node_t * new_head) {
	assert(L);
	L->head = new_head;
}

void set_list_tail(struct list_t * L, struct list_node_t * new_tail) {
	assert(L);
	L->tail = new_tail;
}

void delete_list(struct list_t * L, void (*freeData)(void *)) {
	assert(L);
	struct list_node_t * M = get_list_head(L);
	for (unsigned int i = 1; i <= get_list_size(L); i++) {
		if (freeData != NULL) {
			freeData(get_list_node_data(M));
		}
		struct list_node_t * N = get_successor(M);
		free(M);
		M = N;
	}
	free(L);
}

void view_list(const struct list_t * L, void (*viewData)(const void *)) {
	assert(L);
	struct list_node_t * M = get_list_head(L);
	for (unsigned int i = 1; i <= get_list_size(L); i++) {
		viewData(get_list_node_data(M));
		printf("\n");
		M = get_successor(M);
	}
	printf("\n");
}

void list_insert_first(struct list_t * L, void * data) {
	assert(L);
	struct list_node_t * M = new_list_node(data);
	if (list_is_empty(L) == 1) {
		set_list_tail(L, M);
	}
	else {
		struct list_node_t * N = get_list_head(L);
		set_predecessor(N, M);
		set_successor(M, N);
	}
	set_list_head(L, M);
	increase_list_size(L);
}

void list_insert_last(struct list_t * L, void * data) {
	assert(L);
	struct list_node_t * M = new_list_node(data);
	if (list_is_empty(L) == 1) {
		set_list_head(L, M);
	}
	else {
		struct list_node_t * N = get_list_tail(L);
		set_successor(N, M);
		set_predecessor(M, N);
	}
	set_list_tail(L, M);
	increase_list_size(L);
}

void list_insert_after(struct list_t * L, void * data, struct list_node_t * node) {
	assert(L);
	assert(node);
	struct list_node_t * N = list_find_node(L, get_list_node_data(node));
	if (N != node) {
		ShowMessage("Warning : list_insert_after -> node non trouvé", 0);
	}
	if (N == node) {
		if (N == get_list_tail(L)) {
			list_insert_last(L, data);
		}
		else {
			struct list_node_t * M = new_list_node(data);
			struct list_node_t * O = get_successor(N);
			set_successor(N, M);
			set_predecessor(M, N);
			set_successor(M, O);
			set_predecessor(O, M);
			increase_list_size(L);
		}
	}
}

void * list_remove_first(struct list_t * L) {
	assert(L);
	void * D = NULL;
	struct list_node_t * N = get_list_head(L);
	if (list_is_empty(L) == 1) {
		ShowMessage("Error : list_remove_first -> La liste est déjà vide",0);
	}
	else {
		if (get_list_size(L) == 1) {
			set_list_head(L, NULL);
			set_list_tail(L, NULL);
		}
		else {
			struct list_node_t * M = get_successor(N);
			set_predecessor(M, NULL);
			set_list_head(L, M);
		}
		D = get_list_node_data(N);
		free(N);
		decrease_list_size(L);
	}
	return D;
}

void * list_remove_last(struct list_t * L) {
	assert(L);
	void * D = NULL;
	struct list_node_t * N = get_list_tail(L);
	if (list_is_empty(L) == 1) {
		ShowMessage("Error : list_remove_last -> La liste est déjà vide",0);
	}
	else {
		if (get_list_size(L) == 1) {
			set_list_head(L, NULL);
			set_list_tail(L, NULL);
		}
		else {
			struct list_node_t * M = get_predecessor(N);
			set_successor(M, NULL);
			set_list_tail(L, M);
		}

		D = get_list_node_data(N);
		free(N);
		decrease_list_size(L);
	}
	return D;
}

void * list_remove_node(struct list_t * L, struct list_node_t * node) {
	assert(L);
	void * D = NULL;
	if (list_is_empty(L) == 1) {
		ShowMessage("Error : list_remove_node -> La liste est déjà vide",0);
	}
	else {
		struct list_node_t * N = list_find_node(L, get_list_node_data(node));
		if (N != node) {
			ShowMessage("Warning : list_remove_node -> node non trouvé", 0);
		}
		else {
			if (N == get_list_head(L)) {
				D = list_remove_first(L);
			}
			else if (N == get_list_tail(L)) {
				D = list_remove_last(L);
			}
			else {
				D = get_list_node_data(N);
				struct list_node_t * M = get_predecessor(N);
				struct list_node_t * O = get_successor(N);
				free(N);
				set_successor(M, O);
				set_predecessor(O, M);
				decrease_list_size(L);
			}
		}
	}
	return D;
}

struct list_node_t * list_find_node(struct list_t * L, void * data) {
	assert(L);
	void * N = NULL;
	N = get_list_head(L);
	unsigned int i = 1;
	while (i <= get_list_size(L) && get_list_node_data(N) != data) {
		N = get_successor(N);
		i++;
	}
	return N;
}

void list_swap_nodes_data(struct list_node_t * node1, struct list_node_t * node2) {
	assert(node1);
	assert(node2);
	void * tmp = get_list_node_data(node1);
	set_list_node_data(node1, get_list_node_data(node2));
	set_list_node_data(node2, tmp);
}
#include "tree.h"

#include <assert.h>
#include <list.h>
#include <stdio.h>
#include <stdlib.h>

#include "util.h"

/********************************************************************
 * tree_node_t
 ********************************************************************/

/**
 * Construit et initialise un nouveau nœud d'un arbre binaire de recherche.
 * Le facteur d'équilibre est initialisé à zero.
 * 
 * @param[in] key Clé du nouveau nœud.
 * @param[in] data Donnée à affecter au nouveau nœud.
 * @return le nouveau nœud créé
 */
static struct tree_node_t * new_tree_node(void * key, void * data) {
	struct tree_node_t * node = malloc(sizeof(struct tree_node_t));
	node->key = key;
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	return node;
}

void * get_tree_node_key(const struct tree_node_t * node) {
	assert(node);
	return node->key;
}

void * get_tree_node_data(const struct tree_node_t * node) {
	assert(node);
	return node->data;
}

struct tree_node_t * get_left(const struct tree_node_t * node) {
	assert(node);
	return node->left;
}

struct tree_node_t * get_right(const struct tree_node_t * node) {
	assert(node);
	return node->right;
}

void set_tree_node_key(struct tree_node_t * node, void * new_key) {
	assert(node);
	node->key = new_key;
}

void set_tree_node_data(struct tree_node_t * node, void * new_data) {
	assert(node);
	node->data = new_data;
}

void set_left(struct tree_node_t * node, struct tree_node_t * new_left) {
	assert(node);
	node->left = new_left;
}

void set_right(struct tree_node_t * node, struct tree_node_t * new_right) {
	assert(node);
	node->right = new_right;
}

/*********************************************************************
 * tree_t
 *********************************************************************/

struct tree_t * new_tree() {
	struct tree_t * tree = malloc(sizeof(struct tree_t));
	tree->root = NULL;
	tree->size = 0;
	return tree;
}

int tree_is_empty(const struct tree_t * T) {
	assert(T);
	if(get_tree_size(T) == 0) {
		return 1;
	}
	return 0;
}

unsigned int get_tree_size(const struct tree_t * T) {
	assert(T);
	return T->size;
}

struct tree_node_t * get_root(const struct tree_t * T) {
	assert(T);
	return T->root;
}

void increase_tree_size(struct tree_t * T) {
	assert(T);
	T->size++;
}

void decrease_tree_size(struct tree_t * T) {
	assert(T);
	T->size--;
}

void set_root(struct tree_t * T, struct tree_node_t * new_root) {
	assert(T);
	T->root = new_root;
}

/**
 * Libérer récursivement le sous-arbre raciné au nœud \p curr .
 * Dans le cas où le pointeur de fonction \p freeKey (respectivement
 * \p freeData ) n'est pas NULL, la mémoire de la clé (respectivement de la
 * donnée) du nœud actuel est aussi libérée.
 * NB : procédure récursive.
 * 
 * @param[in] curr
 * @param[in] freeKey 
 * @param[in] freeData 
 */
static void delete_tree_node(struct tree_node_t * curr, void (*freeKey)(void *), void (*freeData)(void *)) {

	if (curr != NULL) {
		struct tree_node_t * l = get_left(curr);
		struct tree_node_t * r = get_right(curr);
		if (freeKey != NULL) {
			freeKey(get_tree_node_key(curr));
		}
		if (freeData != NULL) {
			freeData(get_tree_node_data(curr));
		}
		free(curr);
		delete_tree_node(l, freeKey, freeData);
		delete_tree_node(r, freeKey, freeData);
	}
}

// NB : Utiliser la procédure récursive delete_tree_node.
void delete_tree(struct tree_t * T, void (*freeKey)(void *), void (*freeData)(void *)) {
	assert(T);
	struct tree_node_t * n = get_root(T);
	delete_tree_node(n, freeKey, freeData);
	free(T);
}

/**
 * Afficher récursivement le sous-arbre raciné au nœud \p curr en utilisant un
 * ordre infixe.
 * NB : procédure récursive.
 *
 * @param[in] curr 
 * @param[in] viewKey 
 * @param[in] viewData 
 */
static void view_tree_inorder(struct tree_node_t * curr, void (*viewKey)(const void *), void (*viewData)(const void *)) {
	if (curr != NULL) {
		struct tree_node_t *l = get_left(curr);
		struct tree_node_t *r = get_right(curr);
		view_tree_inorder(l, viewKey, viewData);
		viewKey(get_tree_node_key(curr));
		printf(" - ");
		viewData(get_tree_node_data(curr));
		printf("\n");
		view_tree_inorder(r, viewKey, viewData);
	}
}

// NB : Utiliser la procédure récursive view_tree_inorder.
void view_tree(const struct tree_t * T, void (*viewKey)(const void * key), void (*viewData)(const void * data)) {
	assert(T);
	struct tree_node_t * n = get_root(T);
	view_tree_inorder(n, viewKey, viewData);
}

/**
 * Insérer un nouveau nœud de clé \p key et de donnée \p data au sous-arbre
 * binaire de recherche raciné au nœud \p curr .
 * Les clés sont comparées en utilisant le pointeur de fonction \p precedes .
 * Le nœud curant \p curr est en entrée/sortie et doit être mis à jour.
 * NB : fonction récursive.
 * 
 * @param[in,out] curr
 * @param[in] key 
 * @param[in] data 
 * @param[in] precedes
 */
static void insert_tree_node(struct tree_node_t ** curr, void * key, void * data, int (*precedes)(const void *, const void *)) {
	struct tree_node_t *node;
	if (*curr != NULL) {
		if (precedes(get_tree_node_key(*curr), key) == 0) {
			node = get_left(*curr);
			insert_tree_node(&node, key, data, precedes);
			set_left(*curr, node);
		}
		else {
			node = get_right(*curr);
			insert_tree_node(&node, key, data, precedes);
			set_right(*curr, node);
		}
	}
	else {
		node = new_tree_node(key, data);
		*curr = node;
	}
}

// NB : Utiliser la fonction récursive insert_tree_node.
void tree_insert(struct tree_t * T, void * key, void * data, int (*precedes)(const void * a, const void * b)) {
	assert(T);
	struct tree_node_t *n;
	n = get_root(T);
	insert_tree_node(&n, key, data, precedes);
	if (get_root(T) == NULL) {
		set_root(T,n);
	}
	increase_tree_size(T);
}

struct tree_node_t * tree_find_min(struct tree_node_t * curr) {
	assert(curr);
	if (get_left(curr) != NULL) {
		return tree_find_min(get_left(curr));
	}
	return curr;
}

struct tree_node_t * tree_find_max(struct tree_node_t * curr) {
	assert(curr);
	if ((get_right(curr) != NULL)) {
		return tree_find_max(get_right(curr));
	}
	return curr;
}

struct tree_node_t * tree_find_node(struct tree_node_t * curr, const void * key, int (*precedes)(const void *, const void *)) {
	if (curr == NULL) {
		return NULL;
	}
	if (precedes(get_tree_node_key(curr), key) == 0 && precedes(key, get_tree_node_key(curr)) == 0) {
		return curr;
	}
	if (precedes(get_tree_node_key(curr), key) == 0) {
		struct tree_node_t * left = get_left(curr);
		return tree_find_node(left, key, precedes);
	}
	struct tree_node_t * right = get_right(curr);
	return tree_find_node(right, key, precedes);
}

struct tree_node_t * tree_find_predecessor(struct tree_node_t * curr, const void * key, int (*precedes)(const void *, const void *)) {
	assert(curr);
	if (precedes(get_tree_node_key(curr), key) == 0 && precedes(key, get_tree_node_key(curr)) == 0) {
		if (get_left(curr) == NULL) {
			return NULL;
		}
		return tree_find_max(get_left(curr));
	}
	if (precedes(get_tree_node_key(curr), key) == 0) {
		return tree_find_predecessor(get_left(curr), key, precedes);
	}
	struct tree_node_t * temp = tree_find_predecessor(get_right(curr), key, precedes);
	if (temp == NULL) {
		return curr;
	}
	return temp;
}

struct tree_node_t * tree_find_successor(struct tree_node_t * curr, const void * key, int (*precedes)(const void *, const void *)) {
	assert(curr);
	if (precedes(get_tree_node_key(curr), key) == 0 && precedes(key, get_tree_node_key(curr)) == 0) {
		if (get_right(curr) == NULL) {
			return NULL;
		}
		return tree_find_min(get_right(curr));
	}
	if (precedes(get_tree_node_key(curr), key) == 1) {
		return tree_find_successor(get_right(curr), key, precedes);
	}
	struct tree_node_t * temp = tree_find_successor(get_left(curr), key, precedes);
	if (temp == NULL) {
		return curr;
	}
	return temp;
}

/**
 * Supprimer le nœud de clé \p key du sous-arbre binaire de recherche raciné au
 * nœud \p curr . La donnée du nœud supprimé est restituée, tandis que la
 * mémoire du nœud avec clé \p key est libérée (mais pas la mémoire de la clé).
 * Les clés sont comparées en utilisant le pointeur de fonction \p precedes.
 * Le nœud curant \p curr est en entrée/sortie et doit être mis à jour.
 * NB : fonction récursive.
 * 
 * @param[in,out] curr
 * @param[in] key
 * @param[in] precedes
 * @return la donnée du nœud supprimé
 */
static void * remove_tree_node(struct tree_node_t ** curr, void * key, int (*precedes)(const void *, const void *)) {
	struct tree_node_t * temp;
	void * data;
	if (precedes(get_tree_node_key(*curr), key) == 0 && precedes(key, get_tree_node_key(*curr)) == 0) {
		data = get_tree_node_data(*curr);
		if (get_left(*curr) == NULL && get_right(*curr) == NULL) {
			free(*curr);
			*curr = NULL;
			return data;
		}
		if (get_left(*curr) == NULL) {
		temp = get_right(*curr);
			free(*curr);
			*curr = temp;
			return data;
		}
		if (get_right(*curr) == NULL) {
			temp = get_left(*curr);
			free(*curr);
			*curr = temp;
			return data;
		}
		temp = tree_find_successor(*curr, key, precedes);
		struct tree_node_t * newdata = get_tree_node_data(temp);
		struct tree_note_t * newkey = get_tree_node_key(temp);
		set_tree_node_data(*curr, newdata);
		set_tree_node_key(*curr, newkey);
		temp = get_right(*curr);
		remove_tree_node(&temp, newkey, precedes);
		set_right(*curr, temp);
		return data;
	}
	if (precedes(get_tree_node_key(*curr), key) == 1) {
		temp = get_right(*curr);
		data = remove_tree_node(&temp, key, precedes);
		set_right(*curr, temp);
		return data;
	}
	temp = get_left(*curr);
	data = remove_tree_node(&temp, key, precedes);
	set_left(*curr, temp);
	return data;
}

// NB : Utiliser la fonction récursive remove_tree_node.
void * tree_remove(struct tree_t * T, void * key, int (*precedes)(const void * a, const void * b)) {
	assert(T);
	void * data;
	struct tree_node_t * n = get_root(T);
	if (tree_find_node(n, key, precedes) == NULL) {
		ShowMessage("Warning -> tree_remove : le noeud qu'on souhaite supprimer n'existe pas dans l'arbre",0);
		data = NULL;
	}
	else {
		struct tree_node_t * m;
		if (get_left(get_root(T)) == NULL) {
			m = get_right(get_root(T));
		}
		else if (get_right(get_root(T)) == NULL) {
			m = get_left(get_root(T));
		}
		else {
			m = NULL;
		}
		data = remove_tree_node(&n, key, precedes);
		decrease_tree_size(T);
		if (n != get_root(T)) {
			set_root(T, m);
		}
	}
	return data;
}

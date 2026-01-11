#pragma once

/**
 * Arbre binaire de recherche générique.
 */

/**
 * Un nœud d'un arbre binaire de recherche contient
 * (+) une clé (\p key ),
 * (+) une donnée (\p data ),
 * (+) une référence (\p left ) vers le fils gauche, et
 * (+) une référence (\p right ) vers le fils droit.
 */
struct tree_node_t {
	void * key;
	void * data;
	struct tree_node_t * left;
	struct tree_node_t * right;
};

/**
 * Restitue la clé du nœud \p node .
 * Le nœud \p node ne peut pas être vide.
 * 
 * @param[in] node 
 * @return la clé du nœud \p node
 */
void * get_tree_node_key(const struct tree_node_t * node);

/**
 * Restitue la donnée du nœud \p node .
 * Le nœud \p node ne peut pas être vide.
 *
 * @param[in] node 
 * @return la donnée du nœud \p node
 */
void * get_tree_node_data(const struct tree_node_t * node);

/**
 * Restitue le fils gauche du nœud \p node .
 * Le nœud \p node ne peut pas être vide.
 *
 * @param[in] node 
 * @return le fils gauche du nœud \p node
 */
struct tree_node_t * get_left(const struct tree_node_t * node);

/**
 * Restitue le fils droit du nœud \p node .
 * Le nœud \p node ne peut pas être vide.
 *
 * @param[in] node 
 * @return le fils droit du nœud \p node
 */
struct tree_node_t * get_right(const struct tree_node_t * node);

/**
 * Remplace la clé du nœud \p node par \p new_key .
 * 
 * @param[in,out] node
 * @param[in] new_key
 */
void set_tree_node_key(struct tree_node_t * node, void * new_key);

/**
 * Remplace la donnée du nœud \p node par \p new_data .
 * 
 * @param[in,out] node
 * @param[in] new_data
 */
void set_tree_node_data(struct tree_node_t * node, void * new_data);

/**
 * Remplace le fils gauche du nœud \p node par \p new_left .
 * 
 * @param[in,out] node
 * @param[in] new_left
 */
void set_left(struct tree_node_t * node, struct tree_node_t * new_left);

/**
 * Remplace le fils droit du nœud \p node par \p new_right .
 * 
 * @param[in,out] node
 * @param[in] new_right
 */
void set_right(struct tree_node_t * node, struct tree_node_t * new_right);

/**
 * L'arbre binaire de recherche est une structure contenant :
 * (+) une référence (\p root ) sur sa racine, et
 * (+) le nombre de ses nœuds (\p size ).
 */
struct tree_t {
	struct tree_node_t * root;
	unsigned int size;
};

/**
 * Construire un arbre binaire de recherche vide.
 *
 * @return le nouveau arbre créé
 */
struct tree_t * new_tree();

/**
 * Renvoie 1 si l'arbre \p T est vide, sinon renvoie 0.
 * 
 * @param[in] T 
 * @return 1 si l'arbre \p T est vide, sinon 0
 */
int tree_is_empty(const struct tree_t * T);

/**
 * Restitue la taille (nombre d'éléments) de l'arbre \p T .
 * 
 * @param[in] T 
 * @return la taille de l'arbre \p T
 */
unsigned int get_tree_size(const struct tree_t * T);

/**
 * Restitue la racine de l'arbre \p T .
 * 
 * @param[in] T 
 * @return la racine de l'arbre \p T
 */
struct tree_node_t * get_root(const struct tree_t * T);

/**
 * Incrémente la taille de l'arbre \p T par 1.
 * 
 * @param[in,out] T
 */
void increase_tree_size(struct tree_t * T);

/**
 * Décrémente la taille de l'arbre \p T par 1.
 * 
 * @param[in,out] T
 */
void decrease_tree_size(struct tree_t * T);

/**
 * Remplace la racine de l'arbre \p T par \p new_root .
 * 
 * @param[in,out] T
 * @param[in] new_root
 */
void set_root(struct tree_t * T, struct tree_node_t * new_root);

/**
 * Plusieurs possibilités pour libérer la mémoire de l'arbre binaire de recherche \p T :
 * (+) Si le paramètre \p freeKey n'est pas NULL,
 *     alors le pointeur de fonction \p freeKey va servir à libérer la mémoire
 *     de toutes les clés (key) des nœuds de l'arbre \p T .
 * (+) Si le paramètre \p freeKey est NULL,
 *     alors la mémoire allouée pour les clés (key) des nœuds de l'arbre \p T ne sera pas supprimée.
 *
 * (+) Si le paramètre \p freeData n'est pas NULL,
 *     alors le pointeur de fonction \p freeData va servir à libérer la mémoire
 *     de toutes les données (data) des nœuds de l'arbre \p T .
 * (+) Si le paramètre \p freeData est NULL,
 *     alors la mémoire allouée pour les données (data) des nœuds de l'arbre \p T ne sera pas supprimée.
 *
 * Dans tous les cas, les nœuds de l'arbre et l'arbre lui même sont supprimés.
 * 
 * @param[in] T 
 * @param[in] freeKey
 * @param[in] freeData
 */
void delete_tree(struct tree_t * T, void (*freeKey)(void * key), void (*freeData)(void * data));

/**
 * Affiche les éléments de l'arbre binaire de recherche \p T .
 * Les clés et les données de chaque nœud sont affichées grâce aux pointeurs
 * de fonction \p viewKey et \p viewData , respectivement.
 *
 * @param[in] T 
 * @param[in] viewKey
 * @param[in] viewData
 */
void view_tree(const struct tree_t * T, void (*viewKey)(const void * key), void (*viewData)(const void * data));

/**
 * Ajouter dans l'arbre binaire de recherche \p T un élément de clé \p key et de donnée \p data .
 * Le pointeur de fonction \p precedes est utilisé pour comparer la nouvelle clé \p key avec les clés
 * de l'arbre \p T , c'est-à-dire pour définir l'ordre dans l'arbre ordonné.
 * 
 * @param[in,out] T
 * @param[in] key 
 * @param[in] data 
 * @param[in] precedes
 */
void tree_insert(struct tree_t * T, void * key, void * data, int (*precedes)(const void * a, const void * b));

/**
 * Trouver et renvoyer le nœud de clé minimum de l'arbre raciné au nœud \p curr .
 * Le nœud \p curr ne peut pas être vide.
 * NB : fonction récursive.
 *
 * @param[in] curr
 * @return le nœud de clé minimum de l'arbre raciné à \p curr
 */
struct tree_node_t * tree_find_min(struct tree_node_t * curr);

/**
 * Trouver et renvoyer le nœud de clé maximum de l'arbre raciné au nœud \p curr .
 * Le nœud \p curr ne peut pas être vide.
 * NB : fonction récursive.
 * 
 * @param[in] curr
 * @return le nœud de clé maximum de l'arbre raciné à \p curr
 */
struct tree_node_t * tree_find_max(struct tree_node_t * curr);

/**
 * Vérifie si la clé \p key existe dans le sous-arbre raciné au nœud \p curr .
 * Si oui, le nœud contenant la clé \p key est restitué.
 * Si non, la valeur NULL est restituée.
 * Le pointeur de fonction \p precedes donne l'ordre entre deux clés.
 * Le nœud \p curr ne peut pas être vide.
 * NB : fonction récursive.
 *
 * @param[in] curr
 * @param[in] key 
 * @param[in] precedes
 * @return le nœud de clé \p key s'il existe, sinon NULL
 */
struct tree_node_t * tree_find_node(struct tree_node_t * curr, const void * key, int (*precedes)(const void *, const void *));

/**
 * Chercher dans le sous-arbre raciné au nœud \p curr et renvoyer le prédécesseur du nœud avec clé \p key.
 * Le prédécesseur est le nœud qui contient la clé la plus grande qui est plus petite que la clé \p key.
 * Le pointeur de fonction \p precedes donne l'ordre entre deux clés.
 * Le nœud \p curr ne peut pas être vide.
 * NB1 : fonction récursive.
 * NB2 : on fait l'hypothèse que la clé \p key existe dans le sous-arbre raciné au nœud \p curr.
 *
 * @param[in] curr
 * @param[in] key
 * @param[in] precedes
 * @return le prédécesseur du nœud avec clé \p key
 */
struct tree_node_t * tree_find_predecessor(struct tree_node_t * curr, const void * key, int (*precedes)(const void *, const void *));

/**
 * Chercher dans le sous-arbre raciné au nœud \p curr et renvoyer le successeur du nœud avec clé \p key.
 * Le successeur est le nœud qui contient la clé la plus petite qui est plus grande que la clé \p key.
 * Le pointeur de fonction \p precedes donne l'ordre entre deux clés.
 * Le nœud \p curr ne peut pas être vide.
 * NB1 : fonction récursive.
 * NB2 : on fait l'hypothèse que la clé \p key existe dans le sous-arbre raciné au nœud \p curr.
 *
 * @param[in] curr
 * @param[in] key
 * @param[in] precedes
 * @return le successeur du nœud avec clé \p key
 */
struct tree_node_t * tree_find_successor(struct tree_node_t * curr, const void * key, int (*precedes)(const void *, const void *));

/**
 * Supprime le nœud avec clé \p key de l'arbre \p T et restitue sa donnée.
 * La clé \p key existe obligatoirement dans l'arbre \p T .
 * La mémoire du nœud supprimé est libérée mais pas la mémoire de sa donnée et de sa clé.
 * Le pointeur de fonction \p precedes est utilisé pour comparer la clé \p key avec les clés
 * de l'arbre \p T , c'est-à-dire pour définir l'ordre dans l'arbre ordonné.
 * 
 * @param[in,out] T
 * @param[in] key 
 * @return la donnée du nœud avec clé \p key
 */
void * tree_remove(struct tree_t * T, void * key, int (*precedes)(const void * a, const void * b));
#include "algo.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "util.h"
#include "rational.h"
#include "list.h"
#include "tree.h"
#include "geometry.h"

struct Segment * load_segments_step(long long x1, long long y1, long long x2, long long y2, long long x3, long long y3, long long x4, long long y4) {
	struct Rational a = {x1, y1};
	struct Rational b = {x2, y2};
	struct Rational c = {x3, y3};
	struct Rational d = {x4, y4};
	struct Point * p1 = new_point(a, b);
	struct Point * p2 = new_point(c, d);
	struct Segment * s;
	if (point_precedes(p1, p2) == 1) {
		s = new_segment(p1, p2);
	}
	else {
		s = new_segment(p2, p1);
	}
	return s;
}

// ATTENTION : Pour simplifier vos algorithmes, pensez à comparer les deux points
// de chaque segment à l'aide de la fonction point_precedes et enregistrer le point
// qui précède sur le membre endpoint1 de la struct Segment, tandis que l'autre
// point sur le membre endpoint2 de la struct Segment.
struct list_t * load_segments(const char * input_filename) {
	FILE * fichier = fopen(input_filename, "r");
	struct Segment * s = NULL;
	if (fichier == NULL) {
		ShowMessage("Erreur -> load_segments : le fichier n'existe pas", 1);
	}
	struct list_t * L = new_list();
	long long x1, y1, x2, y2, x3, y3, x4, y4;
	while (fscanf(fichier, "%lld/%lld,%lld/%lld %lld/%lld,%lld/%lld", &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4) != EOF) {
		s = load_segments_step(x1, y1, x2, y2, x3, y3, x4, y4);
		list_insert_last(L, s);
	}
	fclose(fichier);
	return L;
}

void save_intersections(const char * output_filename, const struct list_t * intersections) {
	FILE * fichier = fopen(output_filename, "w");
	if (fichier == NULL) {
		ShowMessage("Erreur -> save_intersections : le fichier n'existe pas", 1);
	}
	struct list_node_t * node = get_list_head(intersections);
	for (unsigned int i = 1; i <= get_list_size(intersections); i++) {
		fprintf(fichier, "%lld/%lld,%lld/%lld\n",get_numerator(get_x(get_list_node_data(node))), get_denominator(get_x(get_list_node_data(node))), get_numerator(get_y(get_list_node_data(node))), get_denominator(get_y(get_list_node_data(node))));
		node = get_successor(node);
	}
	fclose(fichier);
}

struct list_t * all_pairs(const struct list_t * segments) {
	assert(segments);
	struct list_t * result = new_list();
	struct list_node_t * node1 = get_list_head(segments);
	for (unsigned int i = 1; i <= get_list_size(segments); i++) {
		struct list_node_t * node2 = get_successor(node1);
		for (unsigned int j = i + 1; j <= get_list_size(segments); j++) {
			struct Point * p = get_intersection_point(get_list_node_data(node1), get_list_node_data(node2));
			if (p != NULL) {
				list_insert_last(result, p);
			}
			node2 = get_successor(node2);
		}
		node1 = get_successor(node1);
	}
	return result;
}

///////////////////////////////////////////////////////////////////////////////
//////////////////// ALGORITHME DE Bentley-Ottmann ///////////////////////////
///////////////////////////////////////////////////////////////////////////////

struct Event * new_event(int type, struct Point * event_point, struct Segment * s1, struct Segment * s2) {
	struct Event * e = malloc(sizeof(struct Event));
	e->type = type;
	e->event_point = event_point;
	e->s1 = s1;
	if(e->type == 0 ) {
		e->s2 = s2;
	}
	else {
		e->s2 = NULL;
	}
	return e;
}

int get_event_type(const struct Event * event) {
	assert(event);
	return event->type;
}

struct Point * get_event_point(const struct Event * event) {
	assert(event);
	return event->event_point;
}

struct Segment * get_event_segment1(const struct Event * event) {
	assert(event);
	return event -> s1;
}

struct Segment * get_event_segment2(const struct Event * event) {
	assert(event);
	return event -> s2;
}

/**
 * Initialise la structure des événements (arbre binaire de recherche) avec les
 * événements connus d'avance (début et fin des segments de la liste
 * \p segments ).
 * Pour rappel, l'arbre est ordonné selon l'ordre impliqué par la fonction
 * point_precedes.
 *
 * @param[in] segments
 * @return l'arbre des événements connus d'avance
 */

static struct tree_t * initialize_events(const struct list_t * segments) {
	assert(segments);
	struct tree_t * T = new_tree();
	struct list_node_t * node = get_list_head(segments);
	for (unsigned int i = 1; i <= get_list_size(segments); i++) {
		struct Event * E = new_event(1, get_endpoint1(get_list_node_data(node)), get_list_node_data(node), NULL);
		tree_insert(T, get_event_point(E), E, point_precedes);
		struct Event * F = new_event(2, get_endpoint2(get_list_node_data(node)), get_list_node_data(node), NULL);
		tree_insert(T, get_event_point(F), F, point_precedes);
		node = get_successor(node);
	}
	return T;
}

/**
 * Vérifie si les segments \p s1 et \p s2 s'intersectent après la position de
 * l'événement \p event . Si oui et si cette intersection n'est pas détectée
 * auparavant, elle sera ajoutée dans la structure des événements (\p events ),
 * ainsi que dans la liste des intersections (\p intersections ).
 *
 * @param[in] s1
 * @param[in] s2
 * @param[in] event
 * @param[in,out] events
 * @param[in,out] intersections
 */

static void test_and_set_intersection(struct Segment * s1, struct Segment * s2, struct Event * event, struct tree_t * events, struct list_t * intersections) {
	assert(s1);
	assert(s2);
	assert(event);
	assert(events);
	assert(intersections);
	struct Point * P = get_intersection_point(s1, s2);
	if (P != NULL && point_precedes(get_event_point(event), P) && !tree_find_node(get_root(events), P, point_precedes)) {
		struct Event * E = new_event(0, P, s1, s2);
		tree_insert(events,P, E, point_precedes);
		list_insert_last(intersections, P);
	}
	else {
		free(P);
	}
}

/**
 * Gestion de l'événement \p event de type intersection.
 * L'état de la ligne de balayage décrite par la liste \p status doit être mis
 * à jour. La structure des événements (\p events ) ainsi que la liste des
 * intersections (\p intersections ) seront éventuellement mises à jour si une
 * nouvelle intersection sera détectée (utilisez la procedure
 * test_and_set_intersection).
 *
 * @param[in] event
 * @param[in,out] status
 * @param[in,out] events
 * @param[in,out] intersections
 */

static void handle_intersection_event(struct Event * event, struct list_t * status, struct tree_t * events, struct list_t * intersections) {
	assert(event);
	assert(status);
	assert(events);
	assert(intersections);
	struct list_node_t * node = list_find_node(status, get_event_segment1(event));
	struct list_node_t * node2 = list_find_node(status, get_event_segment2(event));
	list_swap_nodes_data(node, node2);
	if (get_successor(node) == node2) {
		if (get_predecessor(node) != NULL) {
			test_and_set_intersection(get_list_node_data(get_predecessor(node)), get_list_node_data(node), event, events, intersections);
		}
		if (get_successor(node2) != NULL) {
			test_and_set_intersection(get_list_node_data(node2), get_list_node_data(get_successor(node2)), event, events, intersections);
		}
	}
	else {
		if (get_predecessor(node2) != NULL) {
			test_and_set_intersection(get_list_node_data(get_predecessor(node2)), get_list_node_data(node2), event, events, intersections);
		}
		if (get_successor(node) != NULL) {
			test_and_set_intersection(get_list_node_data(node), get_list_node_data(get_successor(node)), event, events, intersections);
		}
	}
}

/**
 * Gestion de l'événement \p event de type begin.
 * L'état de la ligne de balayage décrite par la liste \p status doit être mis
 * à jour. La structure des événements (\p events ) ainsi que la liste des
 * intersections (\p intersections ) seront éventuellement mises à jour si une
 * nouvelle intersection sera détectée (utilisez la procedure
 * test_and_set_intersection).
 *
 * @param[in] event
 * @param[in,out] status
 * @param[in,out] events
 * @param[in,out] intersections
 */

static void handle_begin_event(struct Event * event, struct list_t * status, struct tree_t * events, struct list_t * intersections) {
	assert(event);
	assert(status);
	assert(events);
	assert(intersections);
	unsigned int i = 1;
	struct list_node_t * node = get_list_head(status);
	while (i <= get_list_size(status) && segment_precedes(get_list_node_data(node), get_event_segment1(event), get_x(get_event_point(event)))) {
		node = get_successor(node);
		i++;
	}
	if (node == NULL) {
		list_insert_last(status, get_event_segment1(event));
		node = list_find_node(status, get_event_segment1(event));
	}
	else {
		list_insert_after(status, get_event_segment1(event), node);
		struct list_node_t * node2 = list_find_node(status, get_event_segment1(event));
		list_swap_nodes_data(node, node2);
	}
	if (get_predecessor(node) != NULL) {
		test_and_set_intersection(get_list_node_data(get_predecessor(node)), get_list_node_data(node), event, events, intersections);
	}
	if (get_successor(node) != NULL) {
		test_and_set_intersection(get_list_node_data(node), get_list_node_data(get_successor(node)), event, events, intersections);
	}
}

/**
 * Gestion de l'événement \p event de type end.
 * L'état de la ligne de balayage décrite par la liste \p status doit être mis
 * à jour. La structure des événements (\p events ) ainsi que la liste des
 * intersections (\p intersections ) seront éventuellement mises à jour si une
 * nouvelle intersection sera détectée (utilisez la procedure
 * test_and_set_intersection).
 *
 * @param[in] event
 * @param[in,out] status
 * @param[in,out] events
 * @param[in,out] intersections
 */

static void handle_end_event(struct Event * event, struct list_t * status, struct tree_t * events, struct list_t * intersections) {
	assert(event);
	assert(status);
	assert(events);
	assert(intersections);
	struct list_node_t * node = list_find_node(status, get_event_segment1(event));
	struct list_node_t * node2 = get_predecessor(node);
	list_remove_node(status, node);
	if (node2 != NULL && get_successor(node2) != NULL) {
		test_and_set_intersection(get_list_node_data(node2), get_list_node_data(get_successor(node2)), event, events, intersections);
	}
}

struct list_t * BentleyOttmann(const struct list_t * segments) {
	assert(segments);
	struct list_t * status = new_list();
	struct list_t * intersections = new_list();
	struct tree_t * events = initialize_events(segments);
	while (tree_is_empty(events) != 1) {
		struct Point * P = get_tree_node_key(tree_find_min(get_root(events)));
		struct Event * event = get_tree_node_data(tree_find_min(get_root(events)));
		switch (get_event_type(event)) {
			case 0:
				handle_intersection_event(event, status, events, intersections);
			break;
			case 1:
				handle_begin_event(event, status, events, intersections);
			break;
			case 2:
				handle_end_event(event, status, events, intersections);
			break;
			default:
				ShowMessage("Erreur : Algorithme de Bentley&Ottmann -> Evenement inconnu", 1);
			break;
		}
		free(tree_remove(events, P, point_precedes));
	}
	delete_list(status, free);
	delete_tree(events, free, free);
	return intersections;
}
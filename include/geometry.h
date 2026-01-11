#pragma once

#include "rational.h"

/**
 * Un point en 2 dimensions.
 */
struct Point {
	struct Rational x;  // abscisse
	struct Rational y;  // ordonnée
};

/**
 * Construit et initialise un point avec l'abscisse \p x et l'ordonnée \p y .
 *
 * @param[in] x
 * @param[in] y
 * @return le nouveau point créé
 */
struct Point * new_point(struct Rational x, struct Rational y);

/**
 * Restitue l'abscisse du point \p p .
 *
 * @param[in] p
 * @return l'abscisse de \p p
 */
struct Rational get_x(const struct Point * p);

/**
 * Restitue l'ordonnée du point \p p .
 *
 * @param[in] p
 * @return l'ordonnée de \p p
 */
struct Rational get_y(const struct Point * p);

/**
 * Remplace l'abscisse du point \p p par \p new_x .
 *
 * @param[in,out] p
 * @param[in] new_x
 */
void set_x(struct Point * p, struct Rational new_x);

/**
 * Remplace l'ordonnée du point \p p par \p new_y .
 *
 * @param[in,out] p
 * @param[in] new_y
 */
void set_y(struct Point * p, struct Rational new_y);

/**
 * Affiche le point \p p .
 *
 * Remarque : le type de l'argument est de void* et pas de struct Point* afin
 * d'éviter un "avertissement" dans la compilation quand ce sous-programme
 * sera utilisé.
 *
 * @param[in] p
 */
void print_point(const void * p);

/**
 * Un segment d'une ligne droite est défini par ses deux extrémités.
 */
struct Segment {
	struct Point * endpoint1;
	struct Point * endpoint2;
};

/**
 * Construit et initialise un segment avec ses deux extrémités \p endpoint1 et \p endpoint2 .
 *
 * @param[in] endpoint1
 * @param[in] endpoint2
 * @return le nouveau segment créé
 */
struct Segment * new_segment(struct Point * endpoint1, struct Point * endpoint2);

/**
 * Libère la mémoire du segment \p s ainsi que la mémoire de ses deux extrémités.
 *
 * @param[in] s
 */
void free_segment(void * s);

/**
 * Restitue la première extrémité du segment \p s .
 *
 * @param[in] s
 * @return la première extrémité de \p s
 */
struct Point * get_endpoint1(const struct Segment * s);

/**
 * Restitue la deuxième extrémité du segment \p s .
 *
 * @param[in] s
 * @return la deuxième extrémité de \p s
 */
struct Point * get_endpoint2(const struct Segment * s);

/**
 * Remplace la première extrémité du segment \p s par \p new_endpoint .
 *
 * @param[in,out] s
 * @param[in] new_endpoint
 */
void set_endpoint1(struct Segment * s, struct Point * new_endpoint);

/**
 * Remplace la deuxième extrémité du segment \p s par \p new_endpoint .
 *
 * @param[in,out] s
 * @param[in] new_endpoint
 */
void set_endpoint2(struct Segment * s, struct Point * new_endpoint);

/**
 * Affiche le segment \p s .
 *
 * Remarque : le type de l'argument est de void* et pas de struct Segment* afin
 * d'éviter un "avertissement" dans la compilation quand ce sous-programme
 * sera utilisé.
 *
 * @param[in] s
 */
void print_segment(const void * s);

/**
 * Soit deux points \p p1 et \p p2 . On dit que p1 précède p2 si :
 * (1) \p p1.x < \p p2.x, ou
 * (2) \p p1.x = \p p2.x et \p p1.y > \p p2.y
 *
 * Remarque : le type des arguments est de void* et pas de struct Point* afin
 * d'éviter un "avertissement" dans la compilation quand ce sous-programme
 * sera utilisé.
 *
 * @param[in] p1
 * @param[in] p2
 * @return 1 si \p p1 précède \p p2 , sinon 0
 */
int point_precedes(const void * p1, const void * p2);

/**
 * Soit deux segments \p s1 = (p1, p2) et \p s2 = (p3, p4),
 * ainsi qu'une abscisse \p x0 tel que \p x0 est entre p1.x et p2.x,
 * et \p x0 est entre p3.x et p4.x.
 * Soit (\p x0 , y1) et (\p x0 , y2) les points d'intersection de \p s1 et
 * \p s2 avec la droite x = \p x0 , respectivement.
 * On dit que \p s1 précède \p s2 dans l'abscisse \p x0 , si y1 > y2.
 *
 * @param[in] s1
 * @param[in] s2
 * @param[in] x0
 * @return 1 si \p s1 précède \p s2 , sinon 0
 */
int segment_precedes(const struct Segment * s1, const struct Segment * s2, struct Rational x0);

/**
 * Vérifie si les segments \p s1 et \p s2 s'intersectent ou pas.
 * On a trois cas :
 * (1) Si \p s1 et \p s2 ne s'intersectent pas, la valeur 0 est renvoyée.
 * (2) Si \p s1 et \p s2 s'intersectent et aucune extrémité du segment \p s1
 * (respectivement \p s2 ) n'est incluse dans le segment \p s2 (respectivement
 * \p s1 ), la valeur 1 est renvoyée.
 * (3) Si \p s1 et \p s2 s'intersectent et au moins une extrémité du segment
 * \p s1 (respectivement \p s2 ) est incluse dans le segment \p s2
 * (respectivement \p s1 ), la valeur 2 est renvoyée.
 *
 * Inspiré par https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/
 *
 * @param[in] s1
 * @param[in] s2
 * @return 1 ou 2 si \p s1 et \p s2 s'intersectent, sinon 0.
 */
int do_intersect(const struct Segment * s1, const struct Segment * s2);

/**
 * Restitue le point d'intersection de segments \p s1 et \p s2 .
 *
 * Remarque 1 : Si \p s1 et \p s2 ne s'intersectent pas, alors la valeur NULL
 * est renvoyée.
 * Remarque 2 : Si \p s1 et \p s2 s'intersectent mais au moins une extrémité
 * d'un de ces segments est incluse dans l'autre segment, le programme est
 * interrompu avec un message d'erreur (violation de l'hypothèse de notre
 * algorithme : pas plus qu'un événement sur un seul point).
 *
 * @param[in] s1
 * @param[in] s2
 * @return le point d'intersection entre \p s1 et \p s2, ou \p NULL si cela n'existe pas
 */
struct Point * get_intersection_point(const struct Segment * s1, const struct Segment * s2);
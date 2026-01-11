#pragma once

#include "list.h"

/**
 * Ranger dans une liste les segments stockés au fichier texte de nom
 * \p input_filename dont chaque ligne contient les coordonnées d'un segment.
 * Chaque segment est composé de deux parties séparées par une espace :
 * endpoint1.x.numerator/endpoint1.x.denominator,endpoint1.y.numerator/endpoint1.y.denominator
 * endpoint2.x.numerator/endpoint2.x.denominator,endpoint2.y.numerator/endpoint2.y.denominator
 * Exemple:
 * 1/3,5/4 2/2,2/3
 *
 * @param[in] input_filename
 * @return une liste avec tous les segments du fichier \p input_filename
 */
struct list_t * load_segments(const char * input_filename);

/**
 * Ranger dans un fichier texte de nom \p output_filename les points de la
 * liste \p intersections . Chaque ligne du fichier contient les coordonnées
 * d'un point. Le format des coordonnées est le même que pour les segments.
 * Exemple:
 * 1/3,5/4
 * 2/2,2/3
 *
 * @param[in] output_filename
 * @param[in] intersections
 */
void save_intersections(const char * output_filename, const struct list_t * intersections);

/**
* Exécute l'algorithme glouton sur les segments de la liste \p segments
* et restitue une liste avec les points d'intersection trouvés.
*
* @param[in] segments
* @return une liste contenant les points d'intersection
*/
struct list_t * all_pairs(const struct list_t * segments);

/*****************************************************************************
 * Algorithme de Bentley-Ottmann
 *****************************************************************************/

/**
 * Un événement dans l'exécution de l'algorithme de Bentley-Ottmann :
 * (*) \p type : le type de l'événement
 * 		(0 -- intersection, 1 -- begin, 2 -- end)
 * (*) \p event_point : la position de l'événement
 * (*) \p s1 et \p s2 : les segments concernés par l'événement :
 * 		Si \p type = intersection, alors l'événement correspond à
 * 		l'intersection de \p s1 et \p s2 au point \p event_point .
 * 		Si \p type = begin, alors l'événement correspond au début du segment
 * 		\p s1 (point \p event_point ), tandis que \p s2 a la valeur NULL.
 * 		Si \p type = end, alors l'événement correspond à la fin du segment
 * 		\p s1 (point \p event_point ), tandis que \p s2 a la valeur NULL.
 */
struct Event {
	int type;
	struct Point * event_point;
	struct Segment * s1;
	struct Segment * s2;
};

/**
 * Construit et initialise un nouvel événement.
 *
 * @param[in] type
 * @param[in] event_point
 * @param[in] s1
 * @param[in] s2
 * @return le nouvel événement créé
 */
struct Event * new_event(int type, struct Point * event_point, struct Segment * s1, struct Segment * s2);

/**
 * Restitue le type de l'événement \p event .
 *
 * @param[in] event
 * @return le type de l'événement \p event
 */
int get_event_type(const struct Event * event);

/**
 * Restitue la position de l'événement \p event .
 *
 * @param[in] event
 * @return la position de l'événement \p event
 */
struct Point * get_event_point(const struct Event * event);

/**
 * Restitue le premier segment concerné par l'événement \p event .
 *
 * @param[in] event
 * @return le premier segment de l'événement \p event
 */
struct Segment * get_event_segment1(const struct Event * event);

/**
 * Restitue le deuxième segment concerné par l'événement \p event .
 *
 * @param[in] event
 * @return le deuxième segment de l'événement \p event
 */
struct Segment * get_event_segment2(const struct Event * event);

/**
 * Exécute l'algorithme Bentley-Ottmann sur les segments de la liste
 * \p segments et restitue une liste avec les points d'intersection trouvés.
 *
 * @param[in] segments
 * @return une liste contenant les points d'intersection
 */
struct list_t * BentleyOttmann(const struct list_t * segments);
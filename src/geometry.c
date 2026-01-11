#include "geometry.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "rational.h"
#include "util.h"

struct Point * new_point(struct Rational x, struct Rational y) {
	struct Point * p = malloc(sizeof(struct Point));
	p->x = x;
	p->y = y;
	return p;
}

struct Rational get_x(const struct Point * p) {
	assert(p);
	return p->x;
}

struct Rational get_y(const struct Point * p) {
	assert(p);
	return p->y;
}

void set_x(struct Point * p, struct Rational new_x) {
	assert(p);
	p->x = new_x;
}

void set_y(struct Point * p, struct Rational new_y) {
	assert(p);
	p->y = new_y;
}

void print_point(const void * p) {
	assert(p);
	printf("{x : ");
	print_rational(get_x(p));
	printf("} {y : ");
	print_rational(get_y(p));
	printf("}");
}

struct Segment * new_segment(struct Point * endpoint1, struct Point * endpoint2) {
	assert(endpoint1);
	assert(endpoint2);
	struct Segment * seg = malloc(sizeof(struct Segment));
	seg->endpoint1 = endpoint1;
	seg->endpoint2 = endpoint2;
	return seg;
}

void free_segment(void * s) {
	assert(s);
	free(get_endpoint1(s));
	free(get_endpoint2(s));
	free(s);
}

struct Point * get_endpoint1(const struct Segment * s) {
	assert(s);
	return s->endpoint1;
}

struct Point * get_endpoint2(const struct Segment * s) {
	assert(s);
	return s->endpoint2;
}

void set_endpoint1(struct Segment * s, struct Point * new_endpoint) {
	assert(s);
	assert(new_endpoint);
	s->endpoint1 = new_endpoint;
}

void set_endpoint2(struct Segment * s, struct Point * new_endpoint) {
	assert(s);
	assert(new_endpoint);
	s->endpoint2 = new_endpoint;
}

void print_segment(const void * s) {
	assert(s);
	printf("{endpoint1 : ");
	print_point(get_endpoint1(s));
	printf("} {endpoint2 : ");
	print_point(get_endpoint2(s));
	printf("}\n");
}

int point_precedes(const void * p1, const void * p2) {
	assert(p1);
	assert(p2);
	if (lt(get_x(p1),get_x(p2)) || (eq(get_x(p1),get_x(p2)) && gt(get_y(p1),get_y(p2)))) {
		return 1;
	}
	return 0;
}


void get_equation(const struct Segment * s, struct Rational * a, struct Rational * b) {
	assert(s);
	*a = rdiv(rsub(get_y(get_endpoint2(s)),get_y(get_endpoint1(s))),rsub(get_x(get_endpoint2(s)),get_x(get_endpoint1(s))));
	*b = rsub(get_y(get_endpoint1(s)), rmul(*a, get_x(get_endpoint1(s))));
}

int segment_precedes(const struct Segment * s1, const struct Segment * s2, struct Rational x0){
	assert(s1);
	assert(s2);
	assert(lte(rmin(get_x(get_endpoint1(s1)), get_x(get_endpoint2(s1))), x0) &&
		   lte(x0, rmax(get_x(get_endpoint1(s1)), get_x(get_endpoint2(s1)))));
	assert(lte(rmin(get_x(get_endpoint1(s2)), get_x(get_endpoint2(s2))), x0) &&
		   lte(x0, rmax(get_x(get_endpoint1(s2)), get_x(get_endpoint2(s2)))));
	struct Rational a, b, c, d;
	struct Point * e = malloc(sizeof(struct Point));
	struct Point * f = malloc(sizeof(struct Point));
	get_equation(s1, &a, &c);
	get_equation(s2, &b, &d);
	set_y(e, radd(rmul(a, x0), c));
	set_y(f, radd(rmul(b, x0), d));
	if (gt(get_y(e),get_y(f))) {
		free(e);
		free(f);
		return 1;
	}
	if (lt(get_y(e), get_y(f))) {
		free(e);
		free(f);
		return 0;
	}
	free(e);
	free(f);
	struct Rational g = {1,100};
	x0 = radd(x0, g);
	return segment_precedes(s1, s2, x0);
}

/**
 * Vérifie l'orientation du point \p q par rapport au segment défini par les points \p p et \p r .
 *
 * @param[in] p
 * @param[in] q
 * @param[in] r
 * @return
 * 0 si les trois points sont colinéaires,
 * 1 si \p q se trouve dans le sens horaire (clockwise) par rapport au segment [\p p, \p r ],
 * -1 si \p q se trouve dans le sens anti-horaire (counterclockwise) par rapport au segment [\p p, \p r ].
 */
static int get_orientation(const struct Point * p, const struct Point * q, const struct Point * r) {
	assert(p);
	assert(q);
	assert(r);
	struct Rational val =
				rsub(
					rmul(
						rsub(get_y(q), get_y(p)),
						rsub(get_x(r), get_x(q))
						),
					rmul(
						rsub(get_x(q), get_x(p)),
						rsub(get_y(r), get_y(q))
						)
					);
	if (eq(val, (struct Rational) {0,1}))
		return 0;
	else if (gt(val, (struct Rational) {0,1}))
		return 1;
	else
		return -1;
}

/**
 * Vérifie si le point \p q est inclus dans le carré défini par les points \p p et \p r .
 * Si \p p , \p q , \p r sont colinéaires, alors \p q se trouve dans le segment [\p p, \p r ].
 *
 * Remarque : Si le point \p q se trouve dans le bord du carré défini par les points \p p et \p r ,
 * alors on considère que \p q est inclus dans le carré.
 *
 * @param[in] p
 * @param[in] q
 * @param[in] r
 * @return 1 si \p q est inclus dans le carré définit par les points \p p et \p r , sinon 0.
 */
static int is_included(const struct Point * p, const struct Point * q, const struct Point * r) {
	assert(p);
	assert(q);
	assert(r);
	if (lte(rmin(get_x(p), get_x(r)), get_x(q)) && lte(get_x(q), rmax(get_x(p), get_x(r))) &&
		lte(rmin(get_y(p), get_y(r)), get_y(q)) && lte(get_y(q), rmax(get_y(p), get_y(r))))
			return 1;
	return 0;
}

int do_intersect(const struct Segment * s1, const struct Segment * s2) {
	assert(s1);
	assert(s2);

	// Find the four orientations needed for general and special cases
	int o1 = get_orientation(get_endpoint1(s1), get_endpoint2(s1), get_endpoint1(s2));
	int o2 = get_orientation(get_endpoint1(s1), get_endpoint2(s1), get_endpoint2(s2));
	int o3 = get_orientation(get_endpoint1(s2), get_endpoint2(s2), get_endpoint1(s1));
	int o4 = get_orientation(get_endpoint1(s2), get_endpoint2(s2), get_endpoint2(s1));

	// General case
	if ((min(o1, o2) == -1 && max(o1, o2) == 1) && (min(o3, o4) == -1 && max(o3, o4) == 1)) return 1;

	// Special Cases
	// p1, q1 and p2 are co-linear and p2 lies on segment p1q1
	if (o1 == 0 && is_included(get_endpoint1(s1), get_endpoint1(s2), get_endpoint2(s1))) {
		return 2;
	}

	// p1, q1 and q2 are co-linear and q2 lies on segment p1q1
	if (o2 == 0 && is_included(get_endpoint1(s1), get_endpoint2(s2), get_endpoint2(s1))) {
		return 2;
	}

	// p2, q2 and p1 are co-linear and p1 lies on segment p2q2
	if (o3 == 0 && is_included(get_endpoint1(s2), get_endpoint1(s1), get_endpoint2(s2))) {
		return 2;
	}

	// p2, q2 and q1 are co-linear and q1 lies on segment p2q2
	if (o4 == 0 && is_included(get_endpoint1(s2), get_endpoint2(s1), get_endpoint2(s2))) {
		return 2;
	}

	return 0; // Doesn't fall in any of the above cases
}

struct Point * get_intersection_point(const struct Segment * s1, const struct Segment * s2) {
	assert(s1);
	assert(s2);
	struct Rational a, b, c, d;
	if (do_intersect(s1, s2) == 2) {
		ShowMessage("Erreur : get_intersection_point -> Les segments ne respectent pas une des conditions de bases du projet",1);
	}
	if (do_intersect(s1, s2) == 1) {
		get_equation(s1, &a, &c);
		get_equation(s2, &b, &d);
		struct Point * e = malloc(sizeof(struct Point));
		set_x(e, rdiv(rsub(d,c),rsub(a,b)));
		set_y(e, radd(rmul(a, get_x(e)), c));
		return e;
	}
	return NULL;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "rational.h"
#include "list.h"
#include "tree.h"
#include "geometry.h"
#include "algo.h"

/////////////////////////////////////////////////////////////////////////////
///////////////////////////////// TEST LIST /////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/*static int compare_lists(struct list_t * l1, void * l2[], unsigned int size) {
	if (get_list_size(l1) != size)
		return 0;

	if (get_list_size(l1) != 0 && get_list_head(l1) == NULL)
		return 0;

	if (get_list_head(l1) == NULL)
		return 1;

	struct list_node_t * curr = get_list_head(l1);
	unsigned int i = 0;
	while (curr != NULL && l2) {
		if (get_list_node_data(curr) != l2[i])
			return 0;
		curr = get_successor(curr);
		i++;
	}

	curr = get_list_tail(l1);
	i = size-1;
	while (curr != NULL && l2) {
		if (get_list_node_data(curr) != l2[i])
			return 0;
		curr = get_predecessor(curr);
		i--;
	}
	return 1;
}

void test_list_insert_last() {
	int * i1 = malloc(sizeof(int));
	int * i2 = malloc(sizeof(int));
	int * i3 = malloc(sizeof(int));
	*i1 = 1;
	*i2 = 2;
	*i3 = 3;

	struct list_t * L = new_list();
	int * tab[3];
	tab[0] = i1; tab[1] = i2; tab[2] = i3;
	list_insert_last(L, i1);
	if (compare_lists(L, (void*) tab, 1) == 0) printf("problème");
	list_insert_last(L, i2);
	if (compare_lists(L, (void*) tab, 2) == 0) printf("problème");
	list_insert_last(L, i3);
	if (compare_lists(L, (void*) tab, 3) == 0) printf("problème");
	view_list(L, viewInt);
}*/

///////////////////////////////////////////////////////////////////////
//////////////////////////////// MAIN /////////////////////////////////
///////////////////////////////////////////////////////////////////////

int main() {
	printf("TEST FONCTION RATIONAL\n");
	printf("----------------------\n");

	struct Rational a, b, c, d;

	a.numerator = 5;
	a.denominator = 2;

	printf("TEST GETTER\n");
	printf("---------------------\n");

	if (get_numerator(a) == a.numerator) {
		printf("Test get_numeratorOK\n");
	}
	else {
		printf("Test get_numeratorFailed\n");
	}

	if (get_denominator(a) == a.denominator) {
		printf("Test get_denominatorOK\n");
	}
	else {
		printf("Test get_denominatorFailed\n");
	}

	printf("---------------------\n");
	printf("TEST SETTER\n");
	printf("---------------------\n");

	set_numerator(&a, 10);
	if (a.numerator == 10) {
		printf("Test set_numeratorOK\n");
	}
	else {
		printf("Test set_numeratorFailed\n");
	}

	set_denominator(&a, 4);
	if (a.denominator == 4) {
		printf("Test set_denominatorOK\n");
	}
	else {
		printf("Test set_denominatorFailed\n");
	}

	printf("---------------------\n");
	printf("TEST SIMPLIFY\n");
	printf("---------------------\n");

	simplify(&a);

	if (a.numerator == 5 && a.denominator == 2) {
		printf("Test simplify1OK\n");
	}
	else {
		printf("Test simplify1Failed\n");
	}

	a.numerator = -6;
	a.denominator = -12;

	simplify(&a);

	if (a.numerator == 1 && a.denominator == 2) {
		printf("Test simplify2OK\n");
	}
	else {
		printf("Test simplify2Failed\n");
	}

	a.numerator = -12;
	a.denominator = 6;

	simplify(&a);

	if (a.numerator == -2 && a.denominator == 1) {
		printf("Test simplify3OK\n");
	}
	else {
		printf("Test simplify3Failed\n");
	}

	a.numerator = 6;
	a.denominator = -12;

	simplify(&a);

	if (a.numerator == -1 && a.denominator == 2) {
		printf("Test simplify4OK\n");
	}
	else {
		printf("Test simplify4Failed\n");
	}

	printf("---------------------\n");
	printf("TEST COMPARE\n");
	printf("---------------------\n");

	a.numerator = 5;
	a.denominator = 2;

	b.numerator = -10;
	b.denominator = 4;

	c.numerator = -6;
	c.denominator = -4;

	if (gt(a,b) == 1) {
		printf("Test GT1OK\n");
	}
	else {
		printf("Test GT1Failed\n");
	}

	if (gt(c,b) == 1) {
		printf("Test GT2OK\n");
	}
	else {
		printf("Test GT2Failed\n");
	}

	if (gt(a,c) == 1) {
		printf("Test GT3OK\n");
	}
	else {
		printf("Test GT3Failed\n");
	}

	if (lt(b,a) == 1) {
		printf("Test LT1OK\n");
	}
	else {
		printf("Test LT1Failed\n");
	}

	if (lt(b,c) == 1) {
		printf("Test LT2OK\n");
	}
	else {
		printf("Test LT2Failed\n");
	}

	if (lt(c,a) == 1) {
		printf("Test LT3OK\n");
	}
	else {
		printf("Test LT3Failed\n");
	}

	if (gte(a,b) == 1) {
		printf("Test GTE1OK\n");
	}
	else {
		printf("Test GTE1Failed\n");
	}

	if (gte(c,b) == 1) {
		printf("Test GTE2OK\n");
	}
	else {
		printf("Test GTE2Failed\n");
	}

	if (gte(a,c) == 1) {
		printf("Test GTE3OK\n");
	}
	else {
		printf("Test GTE3Failed\n");
	}

	if (lte(b,a) == 1) {
		printf("Test LTE1OK\n");
	}
	else {
		printf("Test LTE1Failed\n");
	}

	if (lte(b,c) == 1) {
		printf("Test LTE2OK\n");
	}
	else {
		printf("Test LTE2Failed\n");
	}

	if (lte(c,a) == 1) {
		printf("Test LTE3OK\n");
	}
	else {
		printf("Test LTE3Failed\n");
	}

	if (eq(a,b) == 0) {
		printf("Test EQ1OK\n");
	}
	else {
		printf("Test EQ1Failed\n");
	}

	if (eq(b,c) == 0) {
		printf("Test EQ2OK\n");
	}
	else {
		printf("Test EQ2Failed\n");
	}

	if (eq(c,a) == 0) {
		printf("Test EQ3OK\n");
	}
	else {
		printf("Test EQ3Failed\n");
	}

	if (neq(a,b) == 1) {
		printf("Test NEQ1OK\n");
	}
	else {
		printf("Test NEQ1Failed\n");
	}

	if (neq(b,c) == 1) {
		printf("Test NEQ2OK\n");
	}
	else {
		printf("Test NEQ2Failed\n");
	}

	if (neq(c,a) == 1) {
		printf("Test NEQ3OK\n");
	}
	else {
		printf("Test NEQ3Failed\n");
	}

	printf("---------------------\n");
	printf("TEST OPERATION\n");
	printf("---------------------\n");

	d.numerator = 0;
	d.denominator = 4;
	if (eq(radd(a,b), d) == 1) {
		printf("Test radd1OK\n");
	}
	else {
		printf("Test radd1Failed\n");
	}

	d.numerator = -1;
	d.denominator = 1;

	if (eq(radd(b,c), d) == 1) {
		printf("Test radd2OK\n");
	}
	else {
		printf("Test radd2Failed\n");
	}

	d.numerator = 4;
	d.denominator = 1;

	if (eq(radd(a,c), d) == 1) {
		printf("Test radd3OK\n");
	}
	else {
		printf("Test radd3Failed\n");
	}

	d.numerator = 5;
	d.denominator = 1;

	if (eq(rsub(a,b), d) == 1) {
		printf("Test rsub1OK\n");
	}
	else {
		printf("Test rsub1Failed\n");
	}

	d.numerator = -4;
	d.denominator = 1;

	if (eq(rsub(b,c), d) == 1) {
		printf("Test rsub2OK\n");
	}
	else {
		printf("Test rsub2Failed\n");
	}

	d.numerator = 1;
	d.denominator = 1;

	if (eq(rsub(a,c), d) == 1) {
		printf("Test rsub3OK\n");
	}
	else {
		printf("Test rsub3Failed\n");
	}

	d.numerator = -50;
	d.denominator = 8;

	if (eq(rmul(a,b), d) == 1) {
		printf("Test mul1OK\n");
	}
	else {
		printf("Test mul1Failed\n");
	}

	d.numerator = -60;
	d.denominator = 16;

	if (eq(rmul(b,c), d) == 1) {
		printf("Test mul2OK\n");
	}
	else {
		printf("Test mul2Failed\n");
	}

	d.numerator = 30;
	d.denominator = 8;

	if (eq(rmul(a,c), d) == 1) {
		printf("Test mul3OK\n");
	}
	else {
		printf("Test mul3Ffailed\n");
	}

	d.numerator = 20;
	d.denominator = -20;

	if (eq(rdiv(a,b), d) == 1) {
		printf("Test div1OK\n");
	}
	else {
		printf("Test div1Failed\n");
	}

	d.numerator = -40;
	d.denominator = 24;

	if (eq(rdiv(b,c), d) == 1) {
		printf("Test div2OK\n");
	}
	else {
		printf("Test div2Failed\n");
	}

	d.numerator = 20;
	d.denominator = 12;

	if (eq(rdiv(a,c), d) == 1) {
		printf("Test div3OK\n");
	}
	else {
		printf("Test div3Ffailed\n");
	}

	printf("---------------------\n");
	printf("TEST MINMAX\n");
	printf("---------------------\n");

	if (eq(rmin(a,b), b) == 1) {
		printf("Test rmin1OK\n");
	}
	else {
		printf("Test rmin1Failed\n");
	}

	if (eq(rmin(b,c), b) == 1) {
		printf("Test rmin2OK\n");
	}
	else {
		printf("Test rmin2Failed\n");
	}

	if (eq(rmin(a,c), c) == 1) {
		printf("Test rmin3OK\n");
	}
	else {
		printf("Test rmin3Ffailed\n");
	}

	if (eq(rmax(a,b), a) == 1) {
		printf("Test rmax1OK\n");
	}
	else {
		printf("Test rmax1Failed\n");
	}

	if (eq(rmax(b,c), c) == 1) {
		printf("Test rmax2OK\n");
	}
	else {
		printf("Test rmax2Failed\n");
	}

	if (eq(rmax(a,c), a) == 1) {
		printf("Test rmax3OK\n");
	}
	else {
		printf("Test rmax3Ffailed\n");
	}

	printf("---------------------\n");
	printf("TEST FONCTION LIST\n");
	printf("---------------------\n");

	int * i1 = malloc(sizeof(int));
	int * i2 = malloc(sizeof(int));
	int * i3 = malloc(sizeof(int));
	int * i4 = malloc(sizeof(int));
	int * i5 = malloc(sizeof(int));
	int * i6 = malloc(sizeof(int));
	int * i7 = malloc(sizeof(int));
	int * i9 = malloc(sizeof(int));
	int * i10 = malloc(sizeof(int));
	*i1 = 1;
	*i2 = 2;
	*i3 = 3;
	*i4 = 4;
	*i5 = 5;
	*i6 = 6;
	*i7 = 7;
	*i9 = 9;
	*i10 = 10;

	struct list_t * L = new_list();
	struct list_t * K = new_list();
	list_insert_last(L, i1);
	list_insert_last(L, i2);
	list_insert_last(L, i3);

	printf("TEST GETTER\n");
	printf("---------------------\n");

	if (get_list_node_data(get_list_head(L)) == i1) {
		printf("Test get_list_head1OK\n");
	}
	else {
		printf("Test get_list_head1Fail\n");
	}

	if (get_list_head(K) == NULL) {
		printf("Test get_list_head2OK\n");
	}
	else {
		printf("Test get_list_head2Fail\n");
	}

	if (get_list_node_data(get_list_tail(L)) == i3) {
		printf("Test get_list_tailOK\n");
	}
	else {
		printf("Test get_list_tailFail\n");
	}

	if (get_list_tail(K) == NULL) {
		printf("Test get_list_tail2OK\n");
	}
	else {
		printf("Test get_list_tail2Fail\n");
	}

	if (get_list_size(L) == 3) {
		printf("Test get_list_sizeOK\n");
	}
	else {
		printf("Test get_list_sizeFail\n");
	}

	if (get_list_size(K) == 0) {
		printf("Test get_list_size2OK\n");
	}
	else {
		printf("Test get_list_size2Fail\n");
	}

	if (list_is_empty(L) == 0) {
		printf("Test list_isEmptyOK\n");
	}
	else {
		printf("Test list_isEmptyFail\n");
	}

	if (list_is_empty(K) == 1) {
		printf("Test list_isEmpty2OK\n");
	}
	else {
		printf("Test list_isEmptyFail\n");
	}

	printf("---------------------\n");
	printf("TEST SETTER\n");
	printf("---------------------\n");

	set_list_head(K, get_list_head(L));
	if (get_list_node_data(get_list_head(K)) == i1) {
		printf("Test set_list_headOK\n");
	}
	else {
		printf("Test set_list_headFail\n");
	}

	set_list_tail(K, get_list_tail(L));
	if (get_list_node_data(get_list_tail(K)) == i3) {
		printf("Test set_list_tailOK\n");
	}
	else {
		printf("Test set_list_tailFail\n");
	}

	set_list_size(K, 0);
	if (get_list_size(K) == 0) {
		printf("Test set_list_sizeOK\n");
	}
	else {
		printf("Test set_list_sizeFail\n");
	}

	increase_list_size(K);
	if (get_list_size(K) == 1) {
		printf("Test increase_list_sizeOK\n");
	}
	else {
		printf("Test increase_list_sizeFail\n");
	}

	decrease_list_size(K);
	if (get_list_size(K) == 0) {
		printf("Test decrease_list_sizeOK\n");
	}
	else {
		printf("Test decrease_list_sizeFail\n");
	}

	printf("---------------------\n");
	printf("TEST VIEW\n");
	printf("---------------------\n");

	view_list(L, viewInt);

	printf("---------------------\n");
	printf("TEST INSERT\n");
	printf("---------------------\n");

	delete_list(K, NULL);
	K = new_list();

	list_insert_first(L, i4);
	if (get_list_node_data(get_list_head(L)) == i4) {
		printf("Test list_insert_firstOK\n");
	}
	else {
		printf("Test list_insert_firstFail\n");
	}

	list_insert_first(K, i10);
	if (get_list_node_data(get_list_head(K)) == i10 && get_list_node_data(get_list_tail(K)) == i10) {
		printf("Test list_insert_first2OK\n");
	}
	else {
		printf("Test list_insert_first2Fail\n");
	}

	delete_list(K, NULL);
	K = new_list();

	list_insert_last(L, i5);
	if (get_list_node_data(get_list_tail(L)) == i5) {
		printf("Test list_insert_lastOK\n");
	}
	else {
		printf("Test list_insert_lastFail\n");
	}

	list_insert_last(K, i9);
	if (get_list_node_data(get_list_tail(K)) == i9 && get_list_node_data(get_list_head(K)) == i9) {
		printf("Test list_insert_last2OK\n");
	}
	else {
		printf("Test list_insert_last2Fail\n");
	}

	delete_list(K, NULL);
	K = new_list();
	list_insert_first(K, i10);

	list_insert_after(L, i6, get_list_head(L));
	if (get_list_node_data(get_successor(get_list_head(L))) == i6) {
		printf("Test list_insert_afterOK\n");
	}
	else {
		printf("Test list_insert_afterFail\n");
	}

	list_insert_after(L, i7, get_list_tail(L));
	if (get_list_node_data(get_list_tail(L)) == i7) {
		printf("Test list_insert_after2OK\n");
	}
	else {
		printf("Test list_insert_after2Fail\n");
	}

	printf("---------------------\n");
	printf("TEST REMOVE\n");
	printf("---------------------\n");

	int * E = list_remove_first(L);
	if (E == i4) {
		printf("Test list_remove_firstOK\n");
	}
	else {
		printf("Test list_remove_firstFail\n");
	}

	E = list_remove_first(K);
	if (E == i10) {
		printf("Test list_remove_first2OK\n");
	}
	else {

		printf("Test list_remove_first2Fail\n");
	}

	list_insert_first(K, i10);

	E = list_remove_last(L);
	if (E == i7) {
		printf("Test list_remove_lastOK\n");
	}
	else {
		printf("Test list_remove_lastFail\n");
	}

	E = list_remove_last(K);
	if (E == i10) {
		printf("Test list_remove_last2OK\n");
	}
	else {
		printf("Test list_remove_last2Fail\n");
	}

	delete_list(K, NULL);

	E = list_remove_node(L, get_list_head(L));
	if (E == i6) {
		printf("Test list_remove_nodeOK\n");
	}
	else {
		printf("Test list_remove_nodeFail\n");
	}

	E = list_remove_node(L, get_list_tail(L));
	if (E == i5) {
		printf("Test list_remove_node2OK\n");
	}
	else {
		printf("Test list_remove_node2Fail\n");
	}

	E = list_remove_node(L,get_successor(get_list_head(L)));
	if (E == i2) {
		printf("Test list_remove_node3OK\n");
	}
	else {
		printf("Test list_remove_node3Fail\n");
	}

	printf("---------------------\n");
	printf("TEST SWAP\n");
	printf("---------------------\n");

	list_swap_nodes_data(get_list_head(L), get_list_tail(L));
	if (get_list_node_data(get_list_head(L)) == i3 && get_list_node_data(get_list_tail(L)) == i1) {
		printf("Test list_swap_nodesOK\n");
	}
	else {
		printf("Test list_swap_nodesFail\n");
	}


	printf("---------------------\n");
	printf("TEST FONCTION GEOMETRY\n");
	printf("---------------------\n");
	printf("TEST POINT\n");
	printf("---------------------\n");

	simplify(&a);
	simplify(&b);
	simplify(&c);
	simplify(&d);

	struct Point * p1 = new_point(b, a);
	if (get_numerator(get_x(p1)) == b.numerator && get_denominator(get_x(p1)) == b.denominator) {
		printf("Test get_xOK\n");
	}
	else {
		printf("Test get_xFail\n");
	}

	if (get_numerator(get_y(p1)) == a.numerator && get_denominator(get_y(p1)) == a.denominator) {
		printf("Test get_yOK\n");
	}
	else {
		printf("Test get_yFail\n");
	}
	set_x(p1, a);

	if (get_numerator(get_x(p1)) == a.numerator && get_denominator(get_x(p1)) == a.denominator) {
		printf("Test set_xOK\n");
	}
	else {
		printf("Test set_xFail\n");
	}

	set_y(p1, b);
	if (get_numerator(get_y(p1)) == b.numerator && get_denominator(get_y(p1)) == b.denominator) {
		printf("Test set_yOK\n");
	}
	else {
		printf("Test set_yFail\n");
	}

	printf("---------------------\n");
	printf("TEST SEGMENT\n");
	printf("---------------------\n");

	struct Point * p2 = new_point(c,d);
	struct Segment * s = new_segment(p1, p2);

	if (get_numerator(get_x(get_endpoint1(s))) == a.numerator) {
		printf("Test get_endpoint1OK\n");
	}
	else {
		printf("Test get_endpoint1Fail\n");
	}

	if (get_denominator(get_y(get_endpoint2(s))) == d.denominator) {
		printf("Test get_endpoint2OK\n");
	}
	else {
		printf("Test get_endpoint2Fail\n");
	}

	set_endpoint1(s, p2);
	if (get_numerator(get_x(get_endpoint1(s))) == c.numerator) {
		printf("Test set_endpoint1OK\n");
	}
	else {
		printf("Test set_endpoint1Fail\n");
	}

	set_endpoint2(s, p1);
	if (get_denominator(get_y(get_endpoint2(s))) == b.denominator) {
		printf("Test set_endpoint2OK\n");
	}
	else {
		printf("Test set_endpoint2Fail\n");
	}

	struct Rational e = {1, 1};
	struct Rational f = {1, 2};
	struct Point * p3 = new_point(e,f);

	struct Rational g = {4, 1};
	struct Rational h = {2, 3};
	struct Point * p4 = new_point(g,h);

	struct Segment * s2 = new_segment(p3, p4);
	struct Point * p5 = get_intersection_point(s, s2);

	if (get_numerator(get_x(p5)) == 269 && get_denominator(get_x(p5)) == 152 && get_numerator(get_y(p5)) == 165 && get_denominator(get_y(p5)) == 304) {
		printf("Test get_intersectionOK\n");
	}
	else {
		printf("Test get_intersectionFail\n");
	}

	struct Rational o = {260, 152};
	struct Rational p = {269, 152};

	if (segment_precedes(s,s2,o) == 1) {
		printf("Test segment_precedesOK\n");
	}
	else {
		printf("Test segment_precedesFail\n");
	}

	if (segment_precedes(s,s2,p) == 0) {
		printf("Test segment_precedes2OK\n");
	}
	else {
		printf("Test segment_precedes2Fail\n");
	}
/*
	printf("---------------------\n");
	printf("TEST ALGORITHME GLOUTON\n");
	printf("---------------------\n");
	delete_list(L,freeInt);
	K = load_segments("./data/input");
	view_list(K, print_segment);
	L = all_pairs(K);
	save_intersections("./data/output",L);
	printf("input --> input_ui\n");
*/
	printf("---------------------\n");
	printf("TEST ARBRE\n");
	printf("---------------------\n");

	int * z = malloc(sizeof(int));
	*z = 5;
	int * z2 = malloc(sizeof(int));
	*z2 = 10;
	int * z3 = malloc(sizeof(int));
	*z3 = 8;
	int * z4 = malloc(sizeof(int));
	*z4 = 2;
	int * z5 = malloc(sizeof(int));
	*z5 = 1;
	int * z6 = malloc(sizeof(int));
	*z6 = 0;
	int * y = malloc(sizeof(int));
	*y = 5;
	int * y2 = malloc(sizeof(int));
	*y2 = 10;
	int * y3 = malloc(sizeof(int));
	*y3 = 8;
	int * y4 = malloc(sizeof(int));
	*y4 = 2;
	int * y5 = malloc(sizeof(int));
	*y5 = 1;
	struct tree_t * T = new_tree();
	struct tree_t * T2 = new_tree();
	tree_insert(T, z4, y4, intSmallerThan);
	tree_insert(T, z2, y2, intSmallerThan);
	tree_insert(T, z5, y5, intSmallerThan);
	tree_insert(T, z, y, intSmallerThan);
	tree_insert(T, z3, y3, intSmallerThan);

	printf("TEST GETTER\n");
	printf("---------------------\n");

	if (get_tree_node_key(get_root(T)) == z4) {
		printf("Test get_rootOK\n");
	}
	else {
		printf("Test get_rootFail\n");
	}

	if (get_root(T2) == NULL) {
		printf("Test get_root2OK\n");
	}
	else {
		printf("Test get_root2Fail\n");
	}

	if (get_tree_size(T) == 5) {
		printf("Test get_tree_sizeOK\n");
	}
	else {
		printf("Test get_tree_sizeFail\n");
	}

	if (get_tree_size(T2) == 0) {
		printf("Test get_tree_size2OK\n");
	}
	else {
		printf("Test get_tree_sizeFail\n");
	}

	if (tree_is_empty(T) == 0) {
		printf("Test tree_is_emptyOK\n");
	}
	else {
		printf("Test tree_is_emptyFail\n");
	}

	if (tree_is_empty(T2) == 1) {
		printf("Test tree_is_empty2OK\n");
	}
	else {
		printf("Test tree_is_empty2Fail\n");
	}

	printf("---------------------\n");
	printf("TEST SETTER\n");
	printf("---------------------\n");

	increase_tree_size(T2);
	if (get_tree_size(T2) == 1) {
		printf("Test increase_tree_sizeOK\n");
	}
	else {
		printf("Test increase_tree_sizeFail\n");
	}

	decrease_tree_size(T2);
	if (get_tree_size(T2) == 0) {
		printf("Test decrease_tree_sizeOK\n");
	}
	else {
		printf("Test decrease_tree_sizeFail\n");
	}

	printf("---------------------\n");
	printf("TEST FIND\n");
	printf("---------------------\n");

	if (get_tree_node_key(tree_find_min(get_root(T))) == z5) {
		printf("Test tree_find_minOK\n");
	}
	else {
		printf("Test tree_find_minFail\n");
	}

	if (get_tree_node_key(tree_find_max(get_root(T))) == z2) {
		printf("Test tree_find_maxOK\n");
	}
	else {
		printf("Test tree_find_maxFail\n");
	}

	if (get_tree_node_key(tree_find_node(get_root(T), z3, intSmallerThan)) == z3) {
		printf("Test tree_find_nodeOK\n");
	}
	else {
		printf("Test tree_find_nodeFail\n");
	}

	if (tree_find_node(get_root(T), z6, intSmallerThan) == NULL) {
		printf("Test tree_find_node2OK\n");
	}
	else {
		printf("Test tree_find_node2Fail\n");
	}

	if (get_tree_node_key(tree_find_successor(get_root(T), z4, intSmallerThan)) == z) {
		printf("Test tree_find_successorOK\n");
	}
	else {
		printf("Test tree_find_successorFail\n");
	}

	if (get_tree_node_key(tree_find_successor(get_root(T), z3, intSmallerThan)) == z2) {
		printf("Test tree_find_successor2OK\n");
	}
	else {
		printf("Test tree_find_successor2Fail\n");
	}

	if (tree_find_successor(get_root(T), z2, intSmallerThan) == NULL) {
		printf("Test tree_find_successor3OK\n");
	}
	else {
		printf("Test tree_find_successor3Fail\n");
	}

	if (get_tree_node_key(tree_find_predecessor(get_root(T), z, intSmallerThan)) == z4) {
		printf("Test tree_find_predecessorOK\n");
	}
	else {
		printf("Test tree_find_predecessorFail\n");
	}

	if (get_tree_node_key(tree_find_predecessor(get_root(T), z2, intSmallerThan)) == z3) {
		printf("Test tree_find_predecessor2OK\n");
	}
	else {
		printf("Test tree_find_predecessor2Fail\n");
	}

	if (tree_find_predecessor(get_root(T), z5, intSmallerThan) == NULL) {
		printf("Test tree_find_predecessor3OK\n");
	}
	else {
		printf("Test tree_find_predecessor3Fail\n");
	}

	tree_remove(T, z4, intSmallerThan);

	printf("---------------------\n");
	printf("TEST ALGORITHME BENTLEY&OTTMAN\n");
	printf("---------------------\n");
	delete_list(L,freeInt);
	K = load_segments("./data/input");
	view_list(K, print_segment);
	L = BentleyOttmann(K);
	save_intersections("./data/output",L);
}
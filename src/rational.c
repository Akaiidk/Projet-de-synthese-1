#include "rational.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "util.h"

long long get_numerator(struct Rational r) {
	return r.numerator;
}

long long get_denominator(struct Rational r) {
	return r.denominator;
}

void set_numerator(struct Rational * r, long long new_numerator) {
	assert(r);
	r->numerator = new_numerator;
}

void set_denominator(struct Rational * r, long long new_denominator) {
	assert(r);
	r->denominator = new_denominator;
}

/**
 * Restitue le Plus Grand Diviseur Commun de \p a et \p b .
 *
 * @param[in] a
 * @param[in] b
 * @return PGCD(a,b)
 */
static long long gcd(long long a, long long b) {
	while (b != 0) {
		long long m = a % b;
		a = b;
		b = m;
	}
	return a;
}

void simplify(struct Rational * r) {
	assert(r);
	if (get_denominator(*r) == 0) {
		ShowMessage("Erreur : simplify -> r.denominateur égal à 0", 1);
	}
	long long m = gcd(get_numerator(*r), get_denominator(*r));
	if (m != 1) {
		set_numerator(r, get_numerator(*r)/m);
		set_denominator(r, get_denominator(*r)/m);
	}
	if (get_denominator(*r) < 0) {
		set_numerator(r, -get_numerator(*r));
		set_denominator(r, -get_denominator(*r));
	}
}
static void rputsamedenominator(struct Rational *a, struct Rational *b) {
	simplify(a);
	simplify(b);
	if (get_denominator(*a) != get_denominator(*b)) {
		set_numerator(a, get_numerator(*a) * get_denominator(*b));
		set_numerator(b, get_numerator(*b) * get_denominator(*a));
		set_denominator(a, get_denominator(*a) * get_denominator(*b));
		set_denominator(b, get_denominator(*a));
	}
}

int gt(struct Rational a, struct Rational b) {
	rputsamedenominator(&a, &b);
	if (get_numerator(a) > get_numerator(b)) {
		return 1;
	}
	return 0;
}

int lt(struct Rational a, struct Rational b) {
	rputsamedenominator(&a, &b);
	if (get_numerator(a) < get_numerator(b)) {
		return 1;
	}
	return 0;
}

int gte(struct Rational a, struct Rational b) {
	rputsamedenominator(&a, &b);
	if (get_numerator(a) >= get_numerator(b)) {
		return 1;
	}
	return 0;
}


int lte(struct Rational a, struct Rational b) {
	rputsamedenominator(&a, &b);
	if (get_numerator(a) <= get_numerator(b)) {
		return 1;
	}
	return 0;
}

int eq(struct Rational a, struct Rational b) {
	rputsamedenominator(&a, &b);
	if (get_numerator(a) == get_numerator(b)) {
		return 1;
	}
	return 0;
}

int neq(struct Rational a, struct Rational b) {
	rputsamedenominator(&a, &b);
	if (get_numerator(a) != get_numerator(b)) {
		return 1;
	}
	return 0;
}


// Pensez à simplifier le résultat.
struct Rational radd(struct Rational a, struct Rational b) {
	rputsamedenominator(&a, &b);
	set_numerator(&a, get_numerator(a) + get_numerator(b));
	simplify(&a);
	return a;
}

// Pensez à simplifier le résultat.
struct Rational rsub(struct Rational a, struct Rational b) {
	rputsamedenominator(&a, &b);
	set_numerator(&a, get_numerator(a) - get_numerator(b));
	simplify(&a);
	return a;
}


// Pensez à simplifier le résultat.
struct Rational rmul(struct Rational a, struct Rational b) {
	set_numerator(&a, get_numerator(a) * get_numerator(b));
	set_denominator(&a, get_denominator(a) * get_denominator(b));
	simplify(&a);
	return a;
}

static void rinv(struct Rational *a) {
	long long b = get_numerator(*a);
	set_numerator(a, get_denominator(*a));
	set_denominator(a, b);
}

// Pensez à simplifier le résultat.
struct Rational rdiv(struct Rational a, struct Rational b) {
	rinv(&b);
	return rmul(a,b);
}

struct Rational rmax(struct Rational a, struct Rational b) {
	rputsamedenominator(&a, &b);
	if (get_numerator(a) > get_numerator(b)) {
		return a;
	}
	return b;
}

struct Rational rmin(struct Rational a, struct Rational b) {
	rputsamedenominator(&a, &b);
	if (get_numerator(a) < get_numerator(b)) {
		return a;
	}
	return b;
}

void print_rational(struct Rational r) {
	printf("%lld / %lld", r.numerator, r.denominator);
}
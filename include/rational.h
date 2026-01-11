#pragma once

/**
 * Un nombre rationnel.
 */
struct Rational {
	long long numerator;  // numérateur
	long long denominator;  // dénominateur
};

/**
 * Restitue le numérateur du nombre rationnel \p r .
 *
 * @param[in] r
 * @return le numérateur de \p r
 */
long long get_numerator(struct Rational r);

/**
 * Restitue le dénominateur du nombre rationnel \p r .
 *
 * @param[in] r
 * @return le dénominateur de \p r
 */
long long get_denominator(struct Rational r);

/**
 * Remplace le numérateur du nombre rationnel \p r par \p new_numerator .
 *
 * @param[in,out] r
 * @param[in] new_numerator
 */
void set_numerator(struct Rational * r, long long new_numerator);

/**
 * Remplace le dénominateur du nombre rationnel \p r par \p new_denominator .
 *
 * @param[in,out] r
 * @param[in] new_denominator
 */
void set_denominator(struct Rational * r, long long new_denominator);

/**
 * Restitue une version simplifiée du nombre rationnel \p r en garantissant que :
 * (1) si \p r a une valeur negative, alors son numérateur est négatif, et
 * (2) le numérateur et le dénominateur sont premiers entre eux.
 *
 * @param[in,out] r
 */
void simplify(struct Rational * r);

/**
 * Comparer les nombres rationnels \p a et \p b .
 *
 * @param[in] a
 * @param[in] b
 * @return 1 si a > b, sinon 0
 */
int gt(struct Rational a, struct Rational b);

/**
 * Comparer les nombres rationnels \p a et \p b .
 *
 * @param[in] a
 * @param[in] b
 * @return 1 si a < b, sinon 0
 */
int lt(struct Rational a, struct Rational b);

/**
 * Comparer les nombres rationnels \p a et \p b .
 *
 * @param[in] a
 * @param[in] b
 * @return 1 si a >= b, sinon 0
 */
int gte(struct Rational a, struct Rational b);

/**
 * Comparer les nombres rationnels \p a et \p b .
 *
 * @param[in] a
 * @param[in] b
 * @return 1 si a <= b, sinon 0
 */
int lte(struct Rational a, struct Rational b);

/**
 * Comparer les nombres rationnels \p a et \p b .
 *
 * @param[in] a
 * @param[in] b
 * @return 1 si a == b, sinon 0
 */
int eq(struct Rational a, struct Rational b);

/**
 * Comparer les nombres rationnels \p a et \p b .
 *
 * @param[in] a
 * @param[in] b
 * @return 1 si a != b, sinon 0
 */
int neq(struct Rational a, struct Rational b);

/**
 * Restitue le résultat de l'addition \p a + \p b .
 *
 * @param[in] a
 * @param[in] b
 * @return a+b
 */
struct Rational radd(struct Rational a, struct Rational b);

/**
 * Restitue le résultat de la soustraction \p a - \p b .
 *
 * @param[in] a
 * @param[in] b
 * @return a-b
 */
struct Rational rsub(struct Rational a, struct Rational b);

/**
 * Restitue le résultat de la multiplication \p a * \p b .
 *
 * @param[in] a
 * @param[in] b
 * @return a*b
 */
struct Rational rmul(struct Rational a, struct Rational b);

/**
 * Restitue le résultat de la division \p a / \p b .
 * Le programme est interrompu si le dénominateur est zéro.
 *
 * @param[in] a
 * @param[in] b
 * @return a/b
 */
struct Rational rdiv(struct Rational a, struct Rational b);

/**
 * Restitue le maximum entre les deux nombres rationnels \p a et \p b .
 *
 * @param[in] a
 * @param[in] b
 * @return max{a,b}
 */
struct Rational rmax(struct Rational a, struct Rational b);

/**
 * Restitue le minimum entre les deux nombres rationnels \p a et \p b .
 *
 * @param[in] a
 * @param[in] b
 * @return min{a,b}
 */
struct Rational rmin(struct Rational a, struct Rational b);

/**
 * Affiche le nombre rationnel \p r .
 *
 * @param[in] r
 */
void print_rational(struct Rational r);
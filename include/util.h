#pragma once

/**
 * Fonction générique qui calcule et retourne le max entre
 * deux éléments de type numérique quelconque
 */
#define max(a,b) \
    ({ __typeof__ (a) _a = (a); \
        __typeof__ (b) _b = (b); \
        _a > _b ? _a : _b; })

/**
 * Fonction générique qui calcule et retourne le min entre
 * deux éléments de type numérique quelconque.
 */
#define min(a,b) \
    ({ __typeof__ (a) _a = (a); \
        __typeof__ (b) _b = (b); \
        _a < _b ? _a : _b; })

/**
 * Affiche le message d'erreur \p msg et
 * interrompt l'exécution du programme si le paramètre \p interrupt vaut 1.
 *
 * @param[in] msg
 * @param[in] interrupt
 */
void ShowMessage(char * msg, int interrupt);

/**
 * Affiche l'entier de l'adresse mémoire \p i .
 *
 * Remarque : le type de l'argument est de void* et pas de int*
 *          afin d'éviter un "avertissement" dans la compilation.
 *
 * @param[in] i
 */
void viewInt(const void * i);

/**
 * Libère la mémoire de l'entier indiqué par le pointeur \p i .
 *
 * Remarque : le type de l'argument est de void* et pas de int*
 *          afin d'éviter un "avertissement" dans la compilation.
 *
 * @param[in] i
 */
void freeInt(void * i);

/**
 * Compare les entiers \p a et \p b .
 *
 * Remarque : Le type des arguments est de void* et pas de int*
 * afin d'éviter un "avertissement" dans la compilation.
 *
 * @param[in] a
 * @param[in] b
 * @return 1 si \p a > \p b , sinon 0
 */
int intSmallerThan(const void * a, const void * b);

/**
 * Compare les entiers \p a et \p b .
 *
 * Remarque : Le type des arguments est de void* et pas de int*
 * afin d'éviter un "avertissement" dans la compilation.
 *
 * @param[in] a
 * @param[in] b
 * @return 1 si \p a > \p b , sinon 0
 */
int intGreaterThan(const void * a, const void * b);

/**
 * Compare les entiers \p a et \p b .
 *
 * Remarque : Le type des arguments est de void* et pas de int*
 * afin d'éviter un "avertissement" dans la compilation.
 *
 * @param[in] a
 * @param[in] b
 * @return 1 si \p a == \p b , sinon 0
 */
int intEqualTo(const void * a, const void * b);
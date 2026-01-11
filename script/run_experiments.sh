#!/bin/bash

# OBJECTIF :
#
# Réaliser une campagne expérimentale sur une collection des instances.

# PARAMÈTRES DU SCRIPT :
#
# $1 nom du répertoire contenant la collection des instances
# $2 nom du fichier avec les résultats


# GESTION DE PARAMÈTRES
#
# Testez si le nombre de paramètres est correct et affichez un message dans
# le cas contraire.
# Assurez vous que le premier paramètre correspond bien à un répertoire.

if [ "$#" -ne 2 ]
then
  echo "Error: number of parameters invalid" 1>&2
  exit
fi
if [ ! -d "$1" ]
then
  echo "Error: ""$1"" is not a repertory" 1>&2
  exit
fi

# Affectation des paramètres aux variables.

repertory="$1"
out_filename="$2"

# EXÉCUTION DE L'EXPÉRIENCE
#
# Pour toutes les instances de la collection, exécutez le programme "./expe".
# Il faut choisir comme sommet de depart le premier sommet du graphe
# (2eme ligne de chaque fichier).
# Pour chaque exécution, vous devez écrire une ligne dans le fichier
# $out_filename avec 6 colonnes :
# Colonne 1 : nombre des sommets du graphe
# Colonne 2 : paramètre concernant la densité du graphe
# Colonne 3 : numéro de l'instance avec ces paramètres
# Colonnes 4-5 : résultats obtenus par l'exécution du programme "./expe"
# Les colonnes sont séparées par une espace.

if [ -e "$out_filename" ]
then
  rm "$out_filename"
fi
touch "$out_filename"
for i in $(ls "$repertory")
do
  colonne1=$(echo "$i" |cut -d"_" -f1)
  colonne2=$(echo "$i" |cut -d"_" -f2)
  colonne3=$(echo "$i" |cut -d"_" -f3)
  colonne4=$(./expe "$repertory"/"$i")
  echo "$colonne1" "$colonne2" "$colonne3" "$colonne4" >> "$out_filename"
done
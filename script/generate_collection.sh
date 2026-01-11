#!/bin/bash

# OBJECTIF :
#
# Générer une collection d'instances aléatoires.

# PARAMÈTRES DU SCRIPT (optionnels) :
#
# -d Donner le nom du répertoire sur lequel les nouvelles instances vont
#	 être enregistrées.
# -n Les différentes instances générées avec ce script contiennent un nombre
#	 des segments différent. Ce paramètre précise le nombre des segments à
#	 utiliser dans un format MIN:MAX:PAS.
#	 Exemple : 20:50:10 va produire des instances avec 20, 30, 40 et 50
#	 segments.
# -r Il s'agit d'un paramètre lié à la génération aléatoire des abscisses et
#	 des ordonnées. Plus précisément, une abscisse ou une ordonnée prendra une
#	 valeur aléatoire entière entre 1 et ce paramètre. La valeur de ce
#	 paramètre varie pour les différentes instances qui seront générés et elle
#	 est donnée dans un format MIN:MAX:PAS.
#	 Exemple : 400:1000:200 va générer des instances avec des
#	 abscisses/ordonnées dans [1,400], [1,600], [1,800], et [1,1000].
# -i Décrive le nombre de différentes instances qui vont être générées
#	 pour chaque combinaison de paramètres n et r.


# FONCTION USAGE
#
# Affiche une aide sur l'utilisation du script et termine son exécution.

usage () {
	echo ""
	echo "NAME"
	echo -e "\t generate_collection\n"
	echo "DESCRIPTION"
	echo -e "\t Generates a collection of instances.\n"
	echo "USAGE"
	echo -e "\t bash generate_collection.sh [OPTIONS]\n"
	echo "OPTIONS"
	echo -e "\t -d DIR_NAME"
	echo -e "\t\t set the name of the created directory which will contain the collection;"
	echo -e "\t\t default value: collection\n"
	echo -e "\t -n MIN:MAX:STEP"
	echo -e "\t\t set the limites and the step concerning the number of segments that"
	echo -e "\t\t will be created in the generated instances;"
	echo -e "\t\t default values: 20:100:20\n"
	echo -e "\t -r MIN:MAX:STEP"
	echo -e "\t\t set the limites and the step concerning the range parameter that will be"
	echo -e "\t\t used in the generation of the coordinates of the points;"
	echo -e "\t\t default values: 200:1000:200\n"
	echo -e "\t -i NUM"
	echo -e "\t\t create NUM instances for each combination of the parameters n and r;"
	echo -e "\t\t default value: 10\n"
	echo -e "\t -h"
	echo -e "\t\t display this help and exit\n"
	echo "EXAMPLE"
	echo -e "\t bash generate_collection.sh -n 50:200:50 -d boo\n"
	echo -e "\t Creates in the directory boo 10 instances (default value) for each"
	echo -e "\t combination of parameters r={200,400,600,800,1000} (default value)"
	echo -e "\t and n={50,100,150,200}\n"
	exit 1
}


# DÉFINITION DE PARAMÈTRES PAR DÉFAUT
#
# On définit d'abord les valeurs par défaut des paramètres qui vont être
# utilisées dans le cas où l'utilisateur ne donne pas la valeur de certains
# ou de tous les paramètres.

dir="collection"
nb_segments_min=20
nb_segments_max=200
nb_segments_step=20
r_min=200
r_max=1000
r_step=200
nb_instances=10


# GESTION DE PARAMÈTRES DONNÉS PAR L'UTILISATEUR
#
# Cherchez et utilisez la commande "getopts" (et pas "getopt").
# L'objectif est de mettre éventuellement à jour les paramètres par défaut,
# si l'utilisateur a choisi d'utiliser des valeurs différentes.
#
# Supprimez le # dans les deux lignes suivantes :
#   usage
#		exit 0
# et ensuite enregistrez et exécutez le script avec la commande :
# 	bash generate_collection.sh
# afin d'avoir une idée des différents cas à traiter.
# N'oubliez pas à remettre les # dans les deux lignes !

while getopts 'hd:n:r:i:' option
do
  case "$option" in
    h)
      usage
      ;;
    d)
      dir="$OPTARG"
      ;;
    n)
      echo "$OPTARG" | grep -E "^[0-9]+:[0-9]+:[0-9]+$" > /dev/null
      if [ $? -eq 1 ]
      then
        echo "n - Error: MIN:MAX:STEP conditions not respected" 1>&2
        exit
      fi
      nb_segments_min=$(echo "$OPTARG" | cut -d":" -f1)
      nb_segments_max=$(echo "$OPTARG" | cut -d":" -f2)
      nb_segments_step=$(echo "$OPTARG" | cut -d":" -f3)
      if [ "$nb_segments_step" -le 0 ]
      then
        echo "n - Error: STEP must be over 0" 1>&2
        exit
      fi
      if [ "$nb_segments_max" -lt "$nb_segments_min" ]
      then
        echo "n - Error: MAX must be over MIN" 1>&2
      fi
      ;;
    r)
      echo "$OPTARG" | grep -E "^[0-9]+:[0-9]+:[0-9]+$" > /dev/null
      if [ $? -eq 1 ]
      then
        echo "r - Error: MIN:MAX:STEP conditions not respected" 1>&2
        exit
      fi
      r_min=$(echo "$OPTARG" | cut -d":" -f1)
      r_max=$(echo "$OPTARG" | cut -d":" -f2)
      r_step=$(echo "$OPTARG" | cut -d":" -f3)
      if [ "$r_min" -lt 100 ]
      then
        echo "r - Error: MIN must be over or equal to 100"
        exit
      fi
      if [ "$r_min" -lt 100 ]
      then
        echo "r - Error: MAX must be under or equal to 10000"
        exit
      fi
      if [ "$r_step" -lt 0 ]
      then
        echo "r - Error: STEP must be over 0" 1>&2
        exit
      fi
      if [ "$r_max" -lt "$r_min" ]
      then
        echo "r - Error: MAX must be over MIN" 1>&2
      fi
      ;;
    i)
      nb_instances="$OPTARG"
      if [ "$nb_instances" -le 0 ]
      then
        echo "i - Error: NUM must be over 0" 1>&2
        exit
      fi
      ;;
    ?)
      echo "parameter does not exist" 1>&2
  esac
done

# GÉNÉRATION DES INSTANCES ALÉATOIRES
#
# Créez dans le répertoire dir des instances aléatoires avec les paramètres
# déjà définis : pour chaque couple de valeurs ($nb_segments, $r), il faut créer
# $nb_instances instances en appelant le script generate_instance.sh.
#
# ATTENTION : NOM DU FICHIER DE CHAQUE INSTANCE
#
# Il faut obligatoirement respecter le format suivant :
#		nb_segments_r_instance
#
# Exemple : l'instance numéro 4 avec 20 segments et r=200 sera enregistrer
# au fichier (sans suffixe, des espaces ou d'autres caractères) :
#		20_200_4

mkdir "$dir"
i=1
for nb_segments in $(seq "$nb_segments_min" "$nb_segments_step" "$nb_segments_max")
do
  for r in $(seq "$r_min" "$r_step" "$r_max")
    do
      for i in $(seq "$nb_instances")
      do
        filename="$nb_segments"_"$r"_"$i"
        bash generate_instance.sh "$dir"/"$filename" "$nb_segments" "$r"
      done
  done
done
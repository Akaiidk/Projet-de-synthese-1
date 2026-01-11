# Détection d'Intersections de Segments (Moteur C & Interface JavaFX)

Ce projet est une solution logicielle spécialisée dans la **géométrie algorithmique**, dont l'objectif est d'identifier avec une précision absolue toutes les intersections au sein d'un ensemble de segments de droite dans un plan 2D.

## 🚀 Présentation Générale
Le projet repose sur un moteur de calcul haute performance écrit en **C**, piloté par une interface graphique interactive en **JavaFX** via **JNI** (Java Native Interface). Cette approche hybride combine la rigueur mathématique du C avec la souplesse de visualisation de Java.

## 🧠 Algorithmes de Détection
Le moteur de calcul propose deux approches distinctes pour résoudre le problème des intersections :

* **Algorithme Naïf (All-Pairs)** : Une méthode de force brute qui compare chaque segment à tous les autres. Sa complexité est de $O(n^2)$.
* **Algorithme de Bentley-Ottmann** : Une méthode avancée de **balayage de ligne** (sweep-line). Elle est beaucoup plus performante pour les grands ensembles de données avec une complexité de $O((n+k) \log n)$, où $k$ est le nombre d'intersections.

## 📊 Étude Expérimentale et Complexité
Le projet inclut une suite de scripts Bash conçus pour automatiser l'analyse de performance et valider les complexités théoriques ($O(n^2)$ vs $O(n \log n)$) :

* **`generate_instance.sh`** : Génère des jeux de données aléatoires (instances) en évitant les cas dégénérés (segments verticaux ou points superposés).
* **`generate_collection.sh`** : Produit massivement des échantillons de tailles variées (de 10 à 10 000 segments) pour tester les limites des algorithmes.
* **`run_experiments.sh`** : Véritable laboratoire de test qui exécute les algorithmes sur toute une collection, chronomètre les temps d'exécution et exporte les données pour tracer des courbes de performance.



Ces outils permettent de visualiser concrètement le "point de bascule" où l'algorithme de Bentley-Ottmann devient plus efficace que la méthode naïve.


## 🛠️ Caractéristiques Techniques

### 1. Précision Mathématique Absolue
Contrairement aux logiciels utilisant des nombres à virgule flottante (sujets aux erreurs d'arrondi), ce projet utilise une bibliothèque de calcul de **nombres rationnels** personnalisée :
* Chaque coordonnée est stockée sous forme de fraction (**numérateur / dénominateur**).
* Cela garantit une précision totale lors des tests géométriques (prédicats de gauche/droite), évitant les crashs ou les erreurs de détection sur les cas limites.

### 2. Structures de Données Optimisées
Pour supporter l'algorithme de balayage, le projet intègre :
* **Arbres de recherche équilibrés** : Pour maintenir l'ordre des segments actifs le long de la ligne de balayage.
* **Files d'événements** : Pour gérer la progression chronologique du balayage.
* **Listes chaînées** : Pour le stockage et la manipulation dynamique des intersections.

## 💻 Fonctionnement de l'Application
Le flux de traitement suit un cycle précis :
1.  **Entrée** : Lecture de fichiers de données (ex: `data/input`) contenant les coordonnées des segments.
2.  **Traitement** : Le moteur C traite les données selon l'algorithme choisi.
3.  **Visualisation** : 
    * Les segments originaux sont tracés en **bleu**.
    * Les points d'intersection détectés sont marqués par des cercles **rouges**.
## 📷 Aperçu
<img width="795" height="601" alt="Capture d’écran 2026-01-11 à 03 34 02" src="https://github.com/user-attachments/assets/80e7f3a1-330c-4d3e-afc3-f9b39633bb9c" />
<img width="798" height="600" alt="Capture d’écran 2026-01-11 à 03 34 30" src="https://github.com/user-attachments/assets/9c47ec00-d034-41e4-b25a-50ee145ac029" />

## 📁 Structure du Projet
* `/src` : Code source C (logique métier, algorithmes, structures de données).
* `/include` : Fichiers d'en-tête (.h).
* `/java/application` : Interface utilisateur JavaFX et pont JNI.
* * `/script` : Réalisation d'étude de performance sur les algorithmes employés
* `/data` : Fichiers d'exemples et de résultats.

---
*Projet adapté pour un fonctionnement natif sur **macOS**, **Linux** et **Windows**.*
















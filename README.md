# Exos-Iterators

Exercices en C++ sur les conteneurs de la STL : comparaison de `vector` et `list`, puis parcours en largeur (BFS) d'un arbre binaire avec une file `queue`.

Travaux pratiques de POO + Design Patterns, ILISI 2, FST Mohammedia.

## Contenu

```
Exos-Iterators/
├── Comparaison Des Iterateurs/
│   └── Cpp Codes/
│       ├── Vector-Liste-EnTete.cpp
│       ├── Vector-Liste-EnMilieu.cpp
│       └── Vector-Liste-EnQueue.cpp
├── Recherche BFS/
│   └── BFS.cpp
└── rapport_compar-centeneur-et-BFS.pdf
```

Le rapport [rapport_compar-centeneur-et-BFS.pdf](rapport_compar-centeneur-et-BFS.pdf) (9 pages) présente les deux travaux : la partie 1 compare `vector` et `list`, la partie 2 explique le parcours BFS.

## Travail 1 : vector contre list

Quel conteneur est le plus rapide pour insérer, supprimer, lire et modifier un élément ? Chaque programme mesure ces 4 opérations sur des `char`, à une position donnée, avec `steady_clock` de `<chrono>`. Les temps sont affichés en ms.

| Programme | Position | Éléments | Opérations |
|---|---|---|---|
| `Vector-Liste-EnTete.cpp` | tête | 100 000 | 100 000 insertions et suppressions, 10 000 000 lectures et modifications |
| `Vector-Liste-EnMilieu.cpp` | milieu | 1 000 000 | 1 000 de chaque |
| `Vector-Liste-EnQueue.cpp` | queue | 1 000 000 | 1 000 000 insertions et suppressions, 10 000 000 lectures et modifications |

### Résultats

Le conteneur le plus rapide, avec l'écart entre les deux temps (mesures sur la machine de l'étudiant, Windows, `g++ -O2`) :

| Position | Insertion | Suppression | Lecture | Modification |
|---|---|---|---|---|
| Tête | **list** ×26 | **list** ×430 | égalité | égalité |
| Milieu | **vector** ×420 | **vector** ×26 | **vector**, plus de ×1 000 000 | **vector**, plus de ×1 000 000 |
| Queue | **vector** ×18 | **vector**, quasi nul | égalité | égalité |

- En tête, le `vector` décale tous ses éléments, la `list` change seulement 2 pointeurs.
- Au milieu, la `list` doit d'abord parcourir ses nœuds pour atteindre la position.
- En queue, le `vector` écrit dans une case libre, la `list` crée ou détruit un nœud.

Les temps changent d'une machine à l'autre, mais l'ordre entre les deux conteneurs reste le même. Les détails, les tableaux complets et le graphique sont dans le rapport.

### Lancer (PowerShell)

```powershell
cd "Comparaison Des Iterateurs\Cpp Codes"
g++ -O2 -std=c++17 -o vector_vs_list Vector-Liste-EnTete.cpp
.\vector_vs_list
```

Pour les autres positions, remplacez le nom du fichier par `Vector-Liste-EnMilieu.cpp` ou `Vector-Liste-EnQueue.cpp`. Le test au milieu dure plusieurs secondes, car la `list` est lente à cet endroit. Gardez l'option `-O2` : sans elle, les temps du `vector` sont beaucoup plus longs.

## Travail 2 : parcours en largeur (BFS)

Le programme lit un arbre binaire saisi par l'utilisateur, le dessine dans le terminal, puis le parcourt niveau par niveau. Un tableau montre à chaque étape le nœud visité et l'état de la file.

La file est un `queue<Noeud*, deque<Noeud*>>` : `queue` est un adaptateur de conteneur construit sur un `deque`.

### Lancer (PowerShell)

```powershell
cd "Recherche BFS"
g++ -std=c++17 -o BFS BFS.cpp
.\BFS
```

Pour chaque nœud, le programme demande son fils gauche puis son fils droit. Tapez `-1` quand le fils n'existe pas.

### Exemple

Valeurs saisies : `1 2 3 4 5 -1 6 -1 -1 -1 -1 -1 -1`

```
        6
    3
1
        5
    2
        4
+-------+-------+--------------------+
| Etape | Noeud | File               |
+-------+-------+--------------------+
| 1     | 1     | [2, 3]             |
| 2     | 2     | [3, 4, 5]          |
| 3     | 3     | [4, 5, 6]          |
| 4     | 4     | [5, 6]             |
| 5     | 5     | [6]                |
| 6     | 6     | []                 |
+-------+-------+--------------------+
Parcours : 1 -> 2 -> 3 -> 4 -> 5 -> 6
```

## Prérequis

- `g++` avec C++17 (MinGW sous Windows).
- Les programmes de comparaison utilisent `asm volatile`, une instruction de GCC qui empêche le compilateur de regrouper les lectures.

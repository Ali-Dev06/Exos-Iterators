// Parcours en largeur (BFS) d'un arbre binaire.
// Le programme demande l'arbre a l'utilisateur, le dessine, puis le parcourt
// niveau par niveau en montrant l'etat de la file a chaque etape.

#include <iostream>
#include <queue>
#include <iomanip>
#include <deque>
#include <string>
using namespace std;






// Definition de la structure de notre arbre.
// Un noeud contient une valeur et deux pointeurs : le fils gauche et le fils droit.
// NULL veut dire que le fils n'existe pas.
struct Noeud {
    int val;
    Noeud *filsg, *filsd;
    Noeud(int v) : val(v), filsg(NULL), filsd(NULL) {}
};









// Saisie de l'arbre, niveau par niveau.
// Pour chaque noeud, on demande son fils gauche puis son fils droit.
// L'utilisateur tape -1 quand le fils n'existe pas.
// On utilise une file pour garder les noeuds dont on doit encore demander les fils.
// "queue" est un adaptateur de conteneur : une file (FIFO) construite sur un deque.
Noeud* saisirArbre() {
    int v;
    cout << "-1 = pas de noeud" << endl;
    cout << "Racine : ";
    cin >> v;
    if (v == -1) return NULL;   // arbre vide

    Noeud* racine = new Noeud(v);
    queue<Noeud*, deque<Noeud*>> f;
    f.push(racine);             // la racine est la premiere a attendre son tour

    while (!f.empty()) {
        Noeud* p = f.front();   // on prend le noeud qui attend depuis le plus longtemps
        f.pop();

        // Fils gauche : s'il existe, on le cree et on le met dans la file
        // pour lui demander ses propres fils plus tard.
        cout << "Gauche de " << p->val << " : ";
        cin >> v;
        if (v != -1) {
            p->filsg = new Noeud(v);
            f.push(p->filsg);
        }

        // Meme chose pour le fils droit.
        cout << "Droit de " << p->val << " : ";
        cin >> v;
        if (v != -1) {
            p->filsd = new Noeud(v);
            f.push(p->filsd);
        }
    }
    return racine;
}





// Transforme le contenu de la file en texte, par exemple [2, 3].
// La file est recue par copie : un queue n'a pas d'iterateurs, donc pour la lire
// on la vide. Comme on vide la copie, la vraie file reste intacte.
string fileEnTexte(queue<Noeud*> f) {
    string s = "[";
    while (!f.empty()) {
        s += to_string(f.front()->val);
        f.pop();
        if (!f.empty()) s += ", ";
    }
    return s + "]";
}






// Affiche une ligne de separation du tableau.
void ligne() {
    cout << "+-------+-------+--------------------+" << endl;
}






// Parcours en largeur (BFS) : on visite l'arbre niveau par niveau.
// La file contient les noeuds decouverts mais pas encore visites.
// A chaque tour : on retire le premier noeud de la file, on ajoute ses fils
// a la fin, puis on affiche une ligne du tableau.
// Comme les fils passent derriere les noeuds deja en attente, un niveau est
// termine avant de commencer le suivant.
void bfs(Noeud* racine) {
    if (!racine) return;
    queue<Noeud*, deque<Noeud*>> f;
    f.push(racine);
    int etape = 0;
    string suite = "";          // garde l'ordre de visite pour l'afficher a la fin
    cout << left;               // alignement a gauche dans les colonnes
    ligne();
    cout<<"  "<<endl;
    cout << "| Etape | Noeud | File               |" << endl;
    ligne();
    while (!f.empty()) {
        Noeud* p = f.front();   // noeud visite a cette etape
        f.pop();
        if (p->filsg) f.push(p->filsg);
        if (p->filsd) f.push(p->filsd);
        etape++;
        // setw(n) reserve n caracteres pour que les colonnes restent alignees.
        // La colonne File montre la file apres l'ajout des fils.
        cout << "| " << setw(5) << etape << " | " << setw(5) << p->val
             << " | " << setw(18) << fileEnTexte(f) << " |" << endl;
        if (suite != "") suite += " -> ";
        suite += to_string(p->val);
    }
    ligne();
    cout << "Parcours : " << suite << endl;
}








// Dessine l'arbre couche sur le cote, avec la racine a gauche.
// C'est un parcours recursif en profondeur dans l'ordre : fils droit, noeud, fils gauche.
// Le fils droit s'affiche donc en haut et le fils gauche en bas.
// "niveau" augmente de 1 a chaque descente et donne le decalage (4 espaces par niveau).
void afficherArbre(Noeud* p, int niveau = 0) {
    if (!p) return;
    afficherArbre(p->filsd, niveau + 1);
    for (int i = 0; i < niveau; i++) cout << "    ";
    cout << p->val << endl;
    afficherArbre(p->filsg, niveau + 1);
}








// Programme principal : saisie, dessin de l'arbre, puis parcours BFS.
int main() {
    Noeud* racine = saisirArbre();
    cout << "Arbre en ordre de profondeur : " << endl;
    afficherArbre(racine);
    bfs(racine);
    
    return 0;
}
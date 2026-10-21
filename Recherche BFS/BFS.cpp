#include <iostream>
#include <queue>
using namespace std;

struct Noeud {
    int val;
    Noeud *filsg, *filsd;
    Noeud(int v) : val(v), filsg(NULL), filsd(NULL) {}
};

Noeud* saisirArbre() {
    int v;
    cout << "-1 = pas de noeud" << endl;
    cout << "Racine : ";
    cin >> v;
    if (v == -1) return NULL;

    Noeud* racine = new Noeud(v);
    queue<Noeud*> f;
    f.push(racine);

    while (!f.empty()) {
        Noeud* p = f.front();
        f.pop();

        cout << "Gauche de " << p->val << " : ";
        cin >> v;
        if (v != -1) {
            p->filsg = new Noeud(v);
            f.push(p->filsg);
        }

        cout << "Droit de " << p->val << " : ";
        cin >> v;
        if (v != -1) {
            p->filsd = new Noeud(v);
            f.push(p->filsd);
        }
    }
    return racine;
}

void bfs(Noeud* racine) {
    if (!racine) return;
    queue<Noeud*> f;
    f.push(racine);
    while (!f.empty()) {
        Noeud* p = f.front();
        f.pop();
        if (p->filsg) f.push(p->filsg);
        if (p->filsd) f.push(p->filsd);
        cout << p->val;
        if (!f.empty()) cout << " -> ";
    }
    cout << endl;
}

int main() {
    Noeud* racine = saisirArbre();
    bfs(racine);
    return 0;
}
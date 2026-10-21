#include <chrono>
#include <iostream>
#include <iterator>
#include <list>
#include <vector>
using namespace std;
using namespace chrono;

const int N = 1000000;
const int OPERATIONS = 1000;

template <typename Operation>
double mesurer(Operation f) {
    auto debut = steady_clock::now();
    f();
    duration<double, milli> duree = steady_clock::now() - debut;
    return duree.count();
}

void afficher(const string& titre, double tVec, double tList) {
    cout << "--- " << titre << " ---" << endl;
    cout << "vector : " << tVec << " ms" << endl;
    cout << "list : " << tList << " ms" << endl << endl;
}

int main() {
    vector<char> v(N, 'a');
    list<char> l(N, 'a');
    volatile char lu = 0;

    double tVecLec = mesurer([&] {
        for (int i = 0; i < OPERATIONS; i++) { lu = v[v.size() / 2]; asm volatile("" ::: "memory"); }
    });
    double tListLec = mesurer([&] {
        for (int i = 0; i < OPERATIONS; i++) lu = *next(l.begin(), l.size() / 2);
    });

    double tVecMod = mesurer([&] {
        for (int i = 0; i < OPERATIONS; i++) { v[v.size() / 2] = 'b'; asm volatile("" ::: "memory"); }
    });
    double tListMod = mesurer([&] {
        for (int i = 0; i < OPERATIONS; i++) *next(l.begin(), l.size() / 2) = 'b';
    });

    double tVecIns = mesurer([&] {
        for (int i = 0; i < OPERATIONS; i++) v.insert(v.begin() + v.size() / 2, 'c');
    });
    double tListIns = mesurer([&] {
        for (int i = 0; i < OPERATIONS; i++) l.insert(next(l.begin(), l.size() / 2), 'c');
    });

    if (v.size() != N + OPERATIONS || l.size() != N + OPERATIONS) {
        cout << "ERREUR" << endl;
        return 1;
    }

    double tVecSup = mesurer([&] {
        for (int i = 0; i < OPERATIONS; i++) v.erase(v.begin() + v.size() / 2);
    });
    double tListSup = mesurer([&] {
        for (int i = 0; i < OPERATIONS; i++) l.erase(next(l.begin(), l.size() / 2));
    });

    afficher("Insertion au milieu", tVecIns, tListIns);
    afficher("Suppression au milieu", tVecSup, tListSup);
    afficher("Lecture au milieu", tVecLec, tListLec);
    afficher("Modification au milieu", tVecMod, tListMod);
    return 0;
}
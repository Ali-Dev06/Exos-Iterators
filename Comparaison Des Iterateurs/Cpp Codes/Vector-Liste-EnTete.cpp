#include <chrono>
#include <iostream>
#include <list>
#include <vector>
using namespace std;
using namespace chrono;

const int N = 100000;
const int LECTURES = 10000000;

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
    vector<char> v;
    list<char> l;
    volatile char lu = 0;

    double tVecIns = mesurer([&] {
        for (int i = 0; i < N; i++) v.insert(v.begin(), 'a');
    });
    double tListIns = mesurer([&] {
        for (int i = 0; i < N; i++) l.insert(l.begin(), 'a');
    });

    if (v.size() != N || l.size() != N) {
        cout << "ERREUR" << endl;
        return 1;
    }

    double tVecLec = mesurer([&] {
        for (int i = 0; i < LECTURES; i++) { lu = v[0]; asm volatile("" ::: "memory"); }
    });
    double tListLec = mesurer([&] {
        for (int i = 0; i < LECTURES; i++) { lu = *l.begin(); asm volatile("" ::: "memory"); }
    });

    double tVecMod = mesurer([&] {
        for (int i = 0; i < LECTURES; i++) { v[0] = 'b'; asm volatile("" ::: "memory"); }
    });
    double tListMod = mesurer([&] {
        for (int i = 0; i < LECTURES; i++) { *l.begin() = 'b'; asm volatile("" ::: "memory"); }
    });

    double tVecSup = mesurer([&] { while (!v.empty()) v.erase(v.begin()); });
    double tListSup = mesurer([&] { while (!l.empty()) l.erase(l.begin()); });

    afficher("Insertion en tete", tVecIns, tListIns);
    afficher("Suppression en tete", tVecSup, tListSup);
    afficher("Lecture en tete", tVecLec, tListLec);
    afficher("Modification en tete", tVecMod, tListMod);
    return 0;
}
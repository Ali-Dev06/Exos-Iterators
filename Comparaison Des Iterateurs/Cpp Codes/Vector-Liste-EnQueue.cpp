#include <chrono>
#include <iostream>
#include <list>
#include <vector>
using namespace std;
using namespace chrono;

const int N = 1000000;
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
        for (int i = 0; i < N; i++) v.push_back('a');
    });
    double tListIns = mesurer([&] {
        for (int i = 0; i < N; i++) l.push_back('a');
    });

    if (v.size() != N || l.size() != N) {
        cout << "ERREUR" << endl;
        return 1;
    }

    double tVecLec = mesurer([&] {
        for (int i = 0; i < LECTURES; i++) { lu = v.back(); asm volatile("" ::: "memory"); }
    });
    double tListLec = mesurer([&] {
        for (int i = 0; i < LECTURES; i++) { lu = l.back(); asm volatile("" ::: "memory"); }
    });

    double tVecMod = mesurer([&] {
        for (int i = 0; i < LECTURES; i++) { v.back() = 'b'; asm volatile("" ::: "memory"); }
    });
    double tListMod = mesurer([&] {
        for (int i = 0; i < LECTURES; i++) { l.back() = 'b'; asm volatile("" ::: "memory"); }
    });

    double tVecSup = mesurer([&] { while (!v.empty()) v.pop_back(); });
    double tListSup = mesurer([&] { while (!l.empty()) l.pop_back(); });

    afficher("Insertion en queue", tVecIns, tListIns);
    afficher("Suppression en queue", tVecSup, tListSup);
    afficher("Lecture en queue", tVecLec, tListLec);
    afficher("Modification en queue", tVecMod, tListMod);
    return 0;
}
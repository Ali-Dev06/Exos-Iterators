#include <chrono>
#include <iostream>
#include <list>
#include <vector>
using namespace std;
using namespace chrono;

const int N = 100000;

template <typename Operation>
double mesurer(Operation f) {
    auto debut = steady_clock::now();
    f();
    duration<double, milli> duree = steady_clock::now() - debut;
    return duree.count();
}

int main() {
    vector<char> v;
    list<char> l;

    double tVecIns = mesurer(
    [&] { 

         for (int i = 0; i < N; i++) 
         v.insert(v.begin(), 'a'); 

    });
    
    double tListIns = mesurer(
    [&] { 
            for (int i = 0; i < N; i++) 
            l.insert(l.begin(), 'a'); 
    });

    if (v.size() != N || l.size() != N) {
        cout << "ERREUR" << endl;
        return 1;
    }

    double tVecSup = mesurer([&] { while (!v.empty()) v.erase(v.begin()); });
    double tListSup = mesurer([&] { while (!l.empty()) l.erase(l.begin()); });

    cout << "--- Insertion en tete ---" << endl;
    cout << "vector : " << tVecIns << " ms" << endl;
    cout << "list : " << tListIns << " ms" << endl << endl;

    cout << "--- Suppression en tete ---" << endl;
    cout << "vector : " << tVecSup << " ms" << endl;
    cout << "list : " << tListSup << " ms" << endl;
    return 0;
}
/*

POUR LANCER : 


g++ -O2 -std=c++17 -o vector_vs_list vector-vs-list-insertion-suppression.cpp
.\vector_vs_list 


*/
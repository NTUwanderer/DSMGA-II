#ifndef PYRAMID
#define PYRAMID
/*
 *  PYRAMID
 *  
 *  Mess with pyramid structure like a boss
 */
#include <vector>
#include <map>
#include <assert.h>

#include "dsmga2.h"

class Pyramid {
public:
    Pyramid (int _ell, int _fffff): ell(_ell), fffff(_fffff) {   
        pHash.clear();
        add_one_layer();
    } 

    void doIt (bool);
    void printStatus();
public:
    vector<DSMGA2> layers;
    unordered_map<unsigned long, double> pHash;

    int ell;
    int fffff;

    bool shouldTerminate();

    // return true if successfully added
    bool add_unique (Chromosome&, size_t);

    bool doOneLayer (size_t, bool);

    void add_one_layer();
};

#endif

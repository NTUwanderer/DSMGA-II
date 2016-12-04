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
        add_one_layer();
    } 

    // return true if successfully added
    bool add_unique (Chromosome&, size_t);

    void doOneLayer (int, bool);

private:
    vector<DSMGA2> layers;
    unordered_map<unsigned long, double> pHash;

    int ell;
    int fffff;

    void add_one_layer();
};

#endif

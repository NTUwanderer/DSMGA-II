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
    Pyramid (int ell, int fffff) {   
        DSMGA2 init(ell, ell << 1 , 1, ell * ell / 3, fffff, &pHash);
        
        layers.push_back(init);
    } 

    // return true if successfully added
    bool add_unique (Chromosome&, size_t);

    void doOneLayer (int, bool);

private:
    vector<DSMGA2> layers;
    unordered_map<unsigned long, double> pHash;
    int ell;
        
};

#endif

#ifndef PYRAMID
#define PYRAMID
/*
 *  PYRAMID
 *  
 *  Mess with pyramid structure like a boss
 */
#include <vector>
#include <map>

#include "dsmga2.h"

class Pyramid{
	public:
		Pyramid(int ell, int fffff)
		{   DSMGA2 init(ell, ell << 1 , 1, ell * ell / 3, fffff, &pHash);
            
            layers.push_back(init);
		} 

        bool add_unique(const Chromosome& chromo, double score);
        

	private:
		vector<DSMGA2> layers;
		unordered_map<unsigned long, double> pHash;
		int ell;
		
};

#endif

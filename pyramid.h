#ifndef PYRAMID
#define PYRAMID
/*
 *  PYRAMID
 *  
 *  Mess with pyramid structure like a boss
 */
#include <vector>
#include <map>
#include <assert>

#include "dsmga2.h"

class Pyramid{
	public:
		Pyramid(int ell, int fffff)
		{   DSMGA2 init(ell, ell << 1 , 1, ell * ell / 3, fffff, &pHash);
            
            layers.push_back(init);
		} 

        // return true if successfully added
        bool add_unique(const Chromosome&, double);

        void doOneLayer(int numOfLayer, bool output) {
        	assert(numOfLayer < layers.size());
        	//* really learn model
        	DSMGA2 layer = layers[numOfLayer];

    		layer.buildFastCounting();
    		layer.buildGraph();
        	while (!layer.shouldTerminate()) {
        		pyramid_oneRun(output);
        	}
        }
        
        

	private:
		vector<DSMGA2> layers;
		unordered_map<unsigned long, double> pHash;
		int ell;
		
};

#endif

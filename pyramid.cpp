#include "pyramid.h"

// 
// ell is the answer length of problem, fffff is the function code.
// Construction of pyramid.
//
Pyramid::Pyramid(int ell, int fffff)
{   
    pHash = new unordered_map<unsigned long, double>;
	pHash->clear();  // Ensure the hash is cleared.
	
	DSMGA2* init = new DSMGA2(ell, (ell << 1), 1, ell*ell/3, fffff, pHash);
    layers.push_back(init);

	Chromosome::function = (Chromosome::Function)fffff;
	Chromosome::nfe = 0;
	Chromosome::lsnfe = 0;
	Chromosome::hitnfe = 0;
	Chromosome::hit = false;
}

Pyramid::~Pyramid()
{
    delete pHash;
    for (size_t i = 0; i < layers.size(); ++i)
    {
        delete layers[i];
    }
}

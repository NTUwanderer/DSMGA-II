#include <iostream> 

#include "pyramid.h"

// 
// ell is the answer length of problem, fffff is the function code.
// Construction of pyramid.
//
Pyramid::Pyramid(int ell, int fffff)
{   
    this->ell = ell;
    this->fffff = fffff;
    pHash = new unordered_map<unsigned long, double>;
	pHash->clear();  // Ensure the hash is cleared.
    cout << pHash << endl;
	
	DSMGA2* init = new DSMGA2(ell, (ell << 1), -1, ell*ell/3, fffff, pHash);
    DSMGA2::PYRA = 1;
    layers.push_back(init);

	Chromosome::function = (Chromosome::Function)fffff;
	Chromosome::nfe = 0;
	Chromosome::lsnfe = 0;
	Chromosome::hitnfe = 0;
	Chromosome::hit = false;
}

Pyramid::~Pyramid()
{
    std::cout << "destructor of pyramid" << std::endl;
    delete pHash;
    for (size_t i = 0; i < layers.size(); ++i)
    {
        delete layers[i];
    }
}

bool Pyramid::add_unique (Chromosome *ch, size_t size, size_t numOfLayer)
{
    assert(numOfLayer < layers.size());
    cout << "shouldTerminate: " << shouldTerminate() << endl;
    for (size_t i = 0; i < size; ++i)
        if (pHash->find(ch[i].getKey()) != pHash->end()) return false;
    
    return layers[numOfLayer]->add_unique(ch, size);
}

void Pyramid::add_one_layer()
{
    DSMGA2* newLayer = new DSMGA2(ell, (ell << 1), -1, ell*ell/3, fffff, pHash);

    layers.back()->setNextLayer(newLayer);

    layers.push_back(newLayer);
}

bool Pyramid::shouldTerminate() const
{
    bool term = false;
    for (size_t i = 0; !term && i < layers.size(); ++i) {
        term |= (layers[i]->shouldTerminate());
    }
    return term;
}

// General Debug purpose function
// Print out layers size and hash size
void Pyramid::printStatus() const
{   
    std::cout << "# of Layers : " << layers.size() << std::endl;
    std::cout << "# of Population : " << pHash->size() << std::endl;
}

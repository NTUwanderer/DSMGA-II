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
    
    Chromosome::function = (Chromosome::Function)fffff;
    Chromosome::nfe = 0;
    Chromosome::lsnfe = 0;
    Chromosome::hitnfe = 0;
    Chromosome::hit = false;

    DSMGA2* init = new DSMGA2(ell, (ell), -1, 100 * ell*ell, fffff, pHash);
    DSMGA2::PYRA = 1;
    layers.push_back(init);
}

Pyramid::~Pyramid()
{
    // std::co << "destructor of pyramid" << std::endl;
    delete pHash;
    for (size_t i = 0; i < layers.size(); ++i)
    {
        delete layers[i];
    }
}

void Pyramid::doIt() {
    // cout << "doIt" << endl;
    // while (!shouldTerminate()) {
    //     layers.front()->pyramid_oneRun();

    //     layers.front()->showStatistics();
    // }
    for (size_t i = 0, size = layers.size(); i < size; ++i) {
        cout << "Layer: " << i << ", ";
        layers[i]->showStatistics();
    }
    // add_one_layer();
    // layers[0]->pyramid_oneRun();
    while (!shouldTerminate()) {
        // Chromosome* ch = new Chromosome[ell];
        // for (int i = 0; i < ell; ++i) {
        //     ch[i].initR(ell);
        // }
        // add_unique(ch, ell, 0);

        add_one_layer();

        for (size_t i = 0, size = layers.size() - 1; i < size; ++i) {
            layers[i]->pyramid_oneRun();
        }
        for (size_t i = 0, size = layers.size(); i < size; ++i) {
            cout << "Layer: " << i << ", ";
            layers[i]->showStatistics();
        }
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
    DSMGA2* newLayer = new DSMGA2(ell, 0, -1, 100 * ell*ell, fffff, pHash);

    layers.back()->setNextLayer(newLayer);

    layers.push_back(newLayer);
}

bool Pyramid::shouldTerminate()
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
    std::cout << "# of Population[0] : " << layers.front()->population.size() << std::endl;
    
}

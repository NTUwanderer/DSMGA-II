#include "pyramid.h"

void Pyramid::doIt (bool output) {
    while (shouldTerminate()) {
        for (int i = 0; i < (ell << 1); ++i) {
            Chromosome c;
            c.initR(ell);

            layers.front().add_unique(c);
        }

        for (size_t i = 0, size = layers.size(); i < size; ++i) {
            if (doOneLayer(i, output))
                break;
        }
    }
}

bool Pyramid::shouldTerminate() {
    bool term = false;
    for (size_t i = 0; !term && i < layers.size(); ++i){
        term |= layers[i].shouldTerminate();
    }
    return term;
}

bool Pyramid::add_unique(Chromosome& chromosome, size_t numOfLayer) {
    if (numOfLayer >= layers.size()) {
        printf("add_unique, numOfLayer: %zu, layers.size(): %zu", numOfLayer, layers.size());
        return false;
    }

    return layers[numOfLayer].add_unique(chromosome);
}

bool Pyramid::doOneLayer(int numOfLayer, bool output) {
    assert(numOfLayer < layers.size());

    if (numOfLayer == layers.size() - 1)
        add_one_layer();

    //* really learn model
    DSMGA2 layer = layers[numOfLayer];

    layer.buildFastCounting();
    layer.buildGraph();
    
    bool success = layer.pyramid_oneRun(output);

    layers[numOfLayer + 1].refreshStats(output);

    return success;
}

void Pyramid::add_one_layer() {
    DSMGA2 init(ell, ell << 1 , 1, ell * ell / 3, fffff, &pHash);
        
    layers.push_back(init);
}

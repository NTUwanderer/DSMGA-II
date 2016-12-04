#include "pyramid.h"

bool Pyramid::add_unique(Chromosome& chromosome, size_t numOfLayer) {
    if (numOfLayer >= layers.size()) {
        printf("add_unique, numOfLayer: %zu, layers.size(): %zu", numOfLayer, layers.size());
        return false;
    }

    return layers[numOfLayer].add_unique(chromosome);
}

void Pyramid::doOneLayer(int numOfLayer, bool output) {
    assert(numOfLayer < layers.size());

    if (numOfLayer == layers.size() - 1)
        add_one_layer();

    //* really learn model
    DSMGA2 layer = layers[numOfLayer];

    layer.buildFastCounting();
    layer.buildGraph();
    while (!layer.shouldTerminate()) {
        layer.pyramid_oneRun(output);

        if (numOfLayer + 1 < layers.size())
            layers[numOfLayer + 1].refreshStats(output);
    }
}

void Pyramid::add_one_layer() {
    DSMGA2 init(ell, ell << 1 , 1, ell * ell / 3, fffff, &pHash);
        
    layers.push_back(init);
}

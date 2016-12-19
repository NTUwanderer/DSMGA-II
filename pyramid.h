#ifndef PYRAMID
#define PYRAMID

#include "dsmga2.h"

class Pyramid
{
    public:
        // Ell is the answer length of problem, fffff is the function code.
        Pyramid(int ell, int fffff);
        ~Pyramid();

        void doIt();

        void printStatus() const;

        bool add_unique(Chromosome*, size_t, size_t);

    private:
        int ell;
        int fffff;

        vector<DSMGA2*> layers;

        // The pHash variable shared by the whole pyramid
        // Solution : unsigned long, Fitness : Double
        // Changed to a static variable in DSMGA2 to avoid pointer usge
        unordered_map<unsigned long, double> *pHash;

        void add_one_layer();

        bool shouldTerminate() const;
};

#endif

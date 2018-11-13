/*
 * dsmga2.h
 *
 *  Created on: May 2, 2011
 *      Author: tianliyu
 */

#ifndef _DSMGA2_H_
#define _DSMGA2_H_

#include <list>
#include <algorithm>
#include "chromosome.h"
#include "statistics.h"
#include "trimatrix.h"
#include "doublelinkedlistarray.h"
#include "fastcounting.h"



class Group {
public:
    int ell = 0;
    int* ellCount = NULL;
    int num = 0;
    vector<pair<int, double> > chIndices;
    static bool cmpByFitness(const pair<int, double>& pi, const pair<int, double>& pj) {
        return (pi.second > pj.second);
    }

    Group () {
        num = 0;
        ell = 0;
        ellCount = NULL;
    }
    Group (int n_ell) {
        ellCount = NULL;
        init(n_ell);
    }
    Group (const Group& g) {
        if (ell != g.ell) {
            init(g.ell);
        }
        num = g.num;

        for (int i = 0; i < ell; ++i)
            ellCount[i] = 0;

        chIndices = g.chIndices;
    }
    Group& operator= (const Group& g) {
        if (ell != g.ell) {
            init(g.ell);
        }
        num = g.num;

        for (int i = 0; i < ell; ++i)
            ellCount[i] = 0;

        chIndices = g.chIndices;

        return *this;
    }
    void init(int n_ell) {
        num = 0;
        ell = n_ell;
        if (ellCount != NULL)
            delete []ellCount;

        ellCount = new int[ell];
        for (int i = 0; i < ell; ++i)
            ellCount[i] = 0;

        chIndices.clear();
    }
    ~Group () {
        if (ellCount != NULL)
            delete[] ellCount;
    }

    void add (int index, Chromosome& ch) {
        chIndices.push_back(make_pair(index, ch.getFitness()));
        ++num;
        for (int i = 0; i < ell; ++i)
            if (ch.getVal(i))
                ++(ellCount[i]);
    }

    double distance (const Chromosome& ch) {
        double d = 0.0;

        for (int i = 0; i < ell; ++i) {
            if (ch.getVal(i)) {
                d += 1.0 - (1.0 * ellCount[i]) / num;
            } else {
                d += (1.0 * ellCount[i]) / num;
            }
        }

        return d;
    }
    Chromosome getInstance () const {
        Chromosome ch;
        ch.init(ell);

        for (int i = 0; i < ell; ++i) {
            if (ellCount[i] > num/2)
                ch.setVal(i, 1);
            else
                ch.setVal(i, 0);
        }

        return ch;
    }
    void sortIndices() {
        std::sort(chIndices.begin(), chIndices.end(), cmpByFitness);
    }
};

class DSMGA2 {
public:
    DSMGA2 (int n_ell, int n_nInitial, int n_maxGen, int n_maxFe, int fffff);

    ~DSMGA2 ();

    void selection ();
    /** tournament selection without replacement*/
    void tournamentSelection();

    void oneRun (bool output = true);
    int doIt (bool output = true);

    void buildGraph ();
    void buildGraph (const Chromosome&, const Chromosome&);
    void mixing ();
    void restrictedMixing(Chromosome& ch, Chromosome& doner, int rec_GIdx = 0);
    bool restrictedMixing(Chromosome& ch, list<int>& mask);
    bool backMixing(Chromosome& source, list<int>& mask, Chromosome& des);
    bool backMixingE(Chromosome& source, list<int>& mask, Chromosome& des);

    bool shouldTerminate ();

    bool foundOptima ();

    int getGeneration () const {
        return generation;
    }

    bool isInP(const Chromosome& ) const;
    void genOrderN();
    void genOrderELL();

    void showStatistics ();

    bool isSteadyState ();
    double bestF();

//protected:
public:

    int ell;                                  // chromosome length
    int nCurrent;                             // population size
    bool EQ;
    unordered_map<unsigned long, double> pHash; // to check if a chromosome is in the population


    list<int> *masks;
    int *selectionIndex;
    int *orderN;                             // for random order
    int *orderELL;                             // for random order
    int selectionPressure;
    int maxGen;
    int maxFe;
    int repeat;
    int generation;
    int bestIndex;

    int rmSuccess;
    int rmFail;
    int bmSuccess;
    int bmFail;
    int groupSize = 0;
    vector<Group> groups;

    Chromosome* population;
    FastCounting* fastCounting;

    TriMatrix<double> graph;
    TriMatrix<double> orig_graph;

    double previousFitnessMean;
    Statistics stFitness;

    // methods
    double computeMI(double, double, double, double) const;


    void findClique(int startNode, list<int>& result);
    void expandClique(list<int>& result);

    void buildGroup();
    int* groupIndices;
    void buildFastCounting();
    int countXOR(int, int) const;
    int countOne(int) const;

    size_t findSize(Chromosome&, list<int>&) const;
    size_t findSize(Chromosome&, list<int>&, Chromosome&) const;

    size_t distance(const Chromosome& ch1, const Chromosome& ch2) const;
};


#endif /* _DSMGA2_H_ */

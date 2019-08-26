//
// Created by houmo on 7/27/19.
//

#ifndef DP_BAGGING_H
#define DP_BAGGING_H

#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>

using namespace std;

class Bagging {
public:
    void ZeroOnePack(int cost, int weight, vector<int> & f, int V);
    void CompletePack(int cost, int weight, vector<int> & f, int V);
    void MultiplePack(int cost, int weight, vector<int> & f, int V, int amount);
    void run();
    void runFull();
    void runComplete();
    void runMultiple();
};


#endif //DP_BAGGING_H

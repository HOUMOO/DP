//
// Created by houmo on 19-8-16.
//

#ifndef DP_MAIN_H
#define DP_MAIN_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "Bagging.h"

using namespace std;

int getLcsLength(string s1, string s2);
int getLcsLengthLessSpace(string s1, string s2);
void runLCS();
void runLCSubSequence();
void getAllSequenceString(vector<vector<int>> & dp, vector<string> & SubString, string s1, string s2, int I, int J);
int getLCSubSequence(string s1, string s2);
int EditDistance(string s1, string s2);
void runEditDistance();

#endif //DP_MAIN_H

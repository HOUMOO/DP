//
// Created by houmo on 19-8-18.
//

#include "main.h"
/*
 * 编辑距离问题：两个字符串，每次仅仅通过 增 删 改 一个字符，一个变成另一个需要多少次这样的操作
 *
 * 首先我们可以递归地解决，从左往右s1[i],s2[j]如果相等，则编辑距离等于s1[i+1:]于s[j+1:]的编辑距离，
 * 否则，则增删改一次，编辑距离+1：
 *      add：    s1[i+1:] = s1[i:], s1[i] = s2[j]   Distance = EditDistance(s1[i:], s2[j+1:])
 *      del:     delete s1[i]                       Distance = EditDistance(s1[i+1:], s2[j:])
 *      change:  s1[i] = s2[j]                      Distance = EditDistance(s1[i+1:], s2[j+1:])
 *      增删改敲好对应三个dp的位置，但是由于依赖同一行的数据，所以不能再简化了
 * 接着以此为依据进行递归，最终返回最小的Distance；
 *
 * 但是，递归会重复计算大量相同量，我们可以使用动态规划进行简化
 *
        if(s1[i] == s2[j]){
            dp[i][j] = dp[i+1][j+1];
        }else{
            dp[i][j] = min(dp[i][j+1], min(dp[i+1][j], dp[i+1][j+1]))+1;
        }
 *
 *
 *
 */

int EditDistance(string s1, string s2){
    vector<vector<int>> dp(s1.size()+1, vector<int> (s2.size()+1, 0));

    for(int i=s1.size(); i>=0; i--){
        dp[i][s2.size()] = s1.size()-i;
    }
    for(int j=s2.size(); j>=0; j--){
        dp[s1.size()][j] = s2.size()-j;
    }

    for(int i=s1.size()-1; i>=0; i--){
        for(int j=s2.size()-1; j>=0; j--){
            if(s1[i] == s2[j]){
                dp[i][j] = dp[i+1][j+1];
            }else{
                dp[i][j] = min(dp[i][j+1], min(dp[i+1][j], dp[i+1][j+1]))+1;
            }
        }
    }
    return dp[0][0];
}

void runEditDistance(){
    string s1 = "";
    string s2 = "";

    cout << EditDistance(s1, s2) << endl;

}
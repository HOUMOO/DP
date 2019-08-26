//
// Created by houmo on 19-8-16.
//
#include "main.h"

/*
 * LCS : Longest Common Substring
 * Q1:两个字穿中最长连续相同的子串长度
 *
 */
void runLCS(){
    /*
     * 运行 最长子串的测试用例
     */
    string s1 = "abcabcdee";
    string s2 = "abbcdee";

    cout << getLcsLength(s1, s2) << endl;
    cout << getLcsLengthLessSpace(s1, s2) << endl;
}

int getLcsLength(string s1, string s2){
    /*
     * 通过动态规划获得最终的最长子串的长度
     * 维护一个动态规划矩阵dp[s1.size(][s2.size()],多出的一行用作填0，以应对边界情况
     * 动态规划的规则：
     *      1.  (s1[i] == s2[j])    {dp[i][j] = dp[i-1][j-1] + 1}
     *      2.  (s1[i] != s2[j])    {dp[i][j] = 0}
     * 物理意义：
     *      dp[i][j] 从头开始以s1[i],s2[j]为公共子串结尾的公共子串的最长长度
     *      当前的s1[i] == s2[j]时，如果之前的已经有连续的公共子串，则可以直接dp[i-1][j-1]+1，表示产生了更长的子串，如果之前没有子串，这现在的i,j为可一个新的子串的起点。
     *
     *
     */
    if(s1.empty() || s2.empty()){
        return 0;
    }
    vector<vector<int>> dp(s1.size(), vector<int> (s2.size(), 0));
    for(int i=0; i<s1.size();i++){
        if(s2[0] == s1[i]){
            dp[i][0] = 1;
        }
    }

    for(int i=0; i<s2.size();i++){
        if(s1[0] == s2[i]){
            dp[0][i] = 1;
        }
    }
    int MAX = dp[0][0];
    for(int i=1; i<s1.size(); i++){
        for(int j=1; j<s2.size(); j++){
            if(s1[i] == s2[j]){
                dp[i][j] = dp[i-1][j-1] + 1;
                MAX = max(MAX, dp[i][j]);
            }
        }
    }
    return MAX;
}

int getLcsLengthLessSpace(string s1, string s2){
    /*
     * 在基本的做法中，使用的存储空间是O(m*n)级别的，但是，其实完全不需要这么多的空间，
     * 每次仅仅关注dp[i-1][j-1],而且以i为进行逐行遍历，i的每个轮次，仅仅调整j上的值，
     * 所以仅仅需要O(n)级别的存储空间就足够了。注意每次从右向左进行遍历，先跟新j，后更新j-1，j依赖于j-1.
     */
    if(s1.empty() || s2.empty()){
        return 0;
    }
    vector<int > dp (s2.size(),0);

    for(int i=0; i<s2.size();i++){
        if(s1[0] == s2[i]){
            dp[i] = 1;
        }
    }
    int MAX = 0;
    for(int i=1; i<s1.size(); i++){
        for(int j=s2.size()-1; j>0; j--){
            if(s1[i] == s2[j]){
                dp[j] = dp[j-1] + 1;
                MAX = max(MAX, dp[j]);
            } else{
                dp[j] = 0;
            }
        }

        if(s2[0] == s1[i]){
            dp[0] = 1;
        } else{
            dp[0] = 0;
        }
    }
    return MAX;
}

/*
 * LCS : Longest Common SubSequence
 * Q1:两个字符串中中最长公共子序列长度，这个子序列仅要求先后顺序对应，不要求连续
 */


void runLCSubSequence(){
    string s1 = "BDCABA";
    string s2 = "ABCBDAB";
    cout << getLCSubSequence(s1, s2) << endl;
}

void getAllSequenceString(vector<vector<int>> & dp, vector<string> & SubString, string s1, string s2, int I, int J){
    if(I==0 || J==0){
        return;
    }else if(s1[I-1] == s2[J-1]){
        getAllSequenceString(dp, SubString, s1, s2, I-1, J-1);
        for(int i=0;i<SubString.size();i++){
            SubString[i] = SubString[i] + s1[I-1];
        }

    }else{
        if(dp[I-1][J] > dp[I][J-1]){
            getAllSequenceString(dp, SubString, s1, s2, I-1, J);
        }else if(dp[I-1][J] < dp[I][J-1]){
            getAllSequenceString(dp, SubString, s1, s2, I, J-1);
        }else{
            getAllSequenceString(dp, SubString, s1, s2, I-1, J);
            vector<string> SubString2 = {""};
            getAllSequenceString(dp, SubString2, s1, s2, I, J-1);
            SubString.insert(SubString.end(), SubString2.begin(), SubString2.end());
        }
    }
}

int getLCSubSequence(string s1, string s2){
    vector<vector<int>> dp (s1.size()+1, vector<int> (s2.size()+1,0));
//    vector<vector<int>> SubSquence(s1.size(), vector<int>(s2.size(), 0));

    for(int i=1; i<=s1.size(); i++){
        for(int j=1; j<=s2.size(); j++){
            if(s1[i-1] == s2[j-1]){
                dp[i][j] = dp[i-1][j-1]+1;
            }else{
                dp[i][j] = max(dp[i][j-1], dp[i-1][j]);
            }
        }
    }

    cout << dp[s1.size()][s2.size()] << endl;

    vector<string> SubString = {""};
    getAllSequenceString(dp, SubString, s1, s2, s1.size(), s2.size());

    for(int i=0; i<SubString.size(); i++){
        cout << SubString[i] << endl;
    }

    return dp[s1.size()][s2.size()];
}

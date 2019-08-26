//
// Created by houmo on 7/27/19.
//

#include "Bagging.h"
void Bagging::ZeroOnePack(int cost, int weight, vector<int> & f, int V){
    for(int i=V; i>=cost; i--){
        f[i] = max(f[i], f[i-cost]+weight);
    }
}

void Bagging::CompletePack(int cost, int weight, vector<int> &f, int V) {
    for(int i=cost; i<=V; i++){
        f[i] = max(f[i], f[i-cost]+weight);
    }
}

void Bagging::MultiplePack(int cost, int weight, vector<int> &f, int V, int amount) {
    if(cost * amount >= V){
        CompletePack(cost, weight, f, V);
    }else{
        int k = 1;
        // 以2^k倍，指数的成倍优化固定种类的商品，加快商品倍迭代的时间
        while(k < amount){
            ZeroOnePack(k*cost, k*weight, f, V);
            amount = amount - k;
            k = k*2;
        }
        ZeroOnePack(amount * cost, amount * weight, f, V);
    }
}

void Bagging::run(){
    /*
     * 普通背包问题（01背包问题；不限制）：
     * 有N件物品和一个容量为V的背包。第i件物品的费用（空间）是volume[i]，价值是value[i]。
     * 求解将哪些物品装入背包可使价值总和最大。
     *
     * 如果最大的情况下，恰巧可以装满，则没有什么可以担心的了，最后一个具有多少价值，背包就能装多少价值。
     *
     * 但是，事情显然不会这么凑巧。
     * 如果不要求装满，那么，我们继续使用这个Run()就可以求解。
     * 如果要求装满，那么就需要一些小技巧了，见：void runFull();
     *
     */
    int num = 5;
    int V = 10;
    vector<int> volume = {3,5,2,1,4};
    vector<int> value = {3,1,4,5,2};
    vector<int> f(V+1);


    for(int i=0; i<num; i++){
        ZeroOnePack(volume[i], value[i], f, V);
    }

//        while()
    cout << f[V] << endl;
}

void Bagging::runFull(){
    /*
     * 必须装满的背包问题：
     * 一旦要求必须装满，就意味着哪怕不满的时候有最大的价值，也要舍弃价值，追求优先装满
     *
     * 这个问题的关键在于，f记录的信息如何让它更丰富？
     * run()中，我们看到f的最终记录是：[0,5,5,9,9,9,12,12,12,12,14];
     * 显然有很多连续的“最优值”，这些连续的最优值的意义是：
     * 在第一个最优值被填好最高价的物品后，剩下的空间即使空置，也不会获得更好的价值
     * 这些连续的相同的值可以加以使用，做法如下：
     * 修改的地方只有一点：
     * f初始值的设定：除了第一个为0，剩下的全部为负无穷在例子volume = {2,2,3}， value = {5,5,3}中
     * f的三次更行：‘-’代表负无穷
     * [0, -, 5, -, - , -]
     * [0, -, 5, -, 10, -]
     * [0, -, 5, 3, 10, 8]
     * 这样，在每个位置上，就都是当前位置代表的空间全部使用时，产生的最大价值
     * 当然，这会使得这个矩阵的每行不是递增的，有所起伏，同时，一些是负无穷的位置，就是代表无法填充满导致的空洞
     * 观察值由负无穷变到正直，主要是通过之前刚好被填满的位置，加上自己的空间消耗确定的位置，是一种以填满到填满的自然过度
     * 而所有的关键在于，f[0]这个位置上是0,由此意味着，每一种物品都可以在背包全空的时候，加载上自己的价值而不至于被负无穷吞掉
     * 有负无穷的方案，更像是跳棋，没有填上子的地方就会有个窟窿，只能踩着被天上的点往前推演，
     * 好在所有物品都可以从大本营出发f[0],但是能不能占据一个点，还是要看能不能在这个点装满的时候，具有最高的价值
     *
     * 如果用12345的数据，我们可以得到这样的f
     * [0,5,4,9,8,7,12,11,10,9,14]
     *
     */
    int num = 3;
    int V = 5;
    vector<int> volume = {2,2,3};
    vector<int> value = {5,5,3};
    vector<int> f(V+1, INT16_MIN);
    f[0] = 0;

    for(int i=0; i<num; i++){
        ZeroOnePack(volume[i], value[i], f, V);
    }

//        while()
    cout << f[V] << endl;
}

void Bagging::runComplete() {
    /*
     * 完全背包问题：
     * 有N种物品和一个容量为V的背包，每种物品都有无限件可用。第i种物品的费用（空间）是volume[i]，价值是value[i]。
     * 求解将哪些物品装入背包可使这些物品的费用（空间）总和不超过背包容量，且价值总和最大。
     *
     * 对于完全背包问题，我们可以直接套用01背包问题，每件物品的数量设置一个完全可以装满背包的量。[V/value]+1
     * 接下来就变成多种每种多件商品的背包问题，按照之前的经验，可以很好的处理掉，就是，需要比较大的时间复杂度。
     *
     * 这不够高效，我们还可以再进一步，这个时候，我们看ZeroOnePack这个函数，这个循环为什么是递减循环呢？
     * 原因在于：这个函数要提供一件商品的优化，这个时候，优化必须从后往前，为了使得更改过的f不影响后面依赖它的f
     * 那么，我们要是不限制“仅一件”，我们完全可以递增循环，按照空间从大到小，安排当下这类商品对f的优化，
     * 同样的这件商品，优化的效果可以积累，一件优化完了，另一件也可以立刻开始优化，达到无数量限制的目的
     *
     * 所以，我们可以仅仅修改这个pack函数，就可以获得不限制数量的优化方法：CompletePack
     * 仅仅修改循环的顺序，就可以得到这样的效果。
     *
     */
    int num = 3;
    int V = 9;
    vector<int> volume = {1,2,3};
    vector<int> value = {1,4,3};
    vector<int> f(V+1);
    f[0] = 0;

    for(int i=0; i<num; i++){
        CompletePack(volume[i], value[i], f, V);
    }

//        while()
    cout << f[V] << endl;
}

void Bagging::runMultiple() {
    /*
     * 多重背包问题：
     * 完全背包问题的一个变种，完全背包问题，对数量无限制，多重背包问题就是一种对数量有限制的背包问题
     * 有N种物品和一个容量为V的背包。第i种物品的费用（空间）是volume[i]，价值是value[i]，最多有n[i]件可用。
     * 求解将哪些物品装入背包可使这些物品的费用（空间）总和不超过背包容量，且价值总和最大。
     *
     * 这个问题，照旧我们可以拆分，拆成n[0]+n[1],...,n[N]个01背包问题，但是不高效
     * 高效一点，我们可以吧里面满足完全背包的商品： n[i]*volume[i] >= V 的拿出来，他们走完全背包，剩下的走01背包
     * 再高效一点，我们就要对重复的01背包问题动手了，因为每次的更新都是一样的，那么连续更新两次和一次(2*volume,2*value)的更新效果一样
     * 所以我们可以从1倍开始，每次用翻倍的商品去更新，索性二进制可以表示任何整数，只要逐步翻倍，就能表示任何小等于2^k的数量,
     * 最终，翻倍后的n和之前的n的和，会超过所有的n[i]，这个时候停止翻倍，把剩下n乘个倍数，一并更新，算法结束
     *
     * 通过这样的逐步优化，问题的规模从O(V * n[0]+n[1],...,n[N]),变到O(V * log(n[0]+n[1],...,n[N]) ),提升巨大
     *
     * 为此，巫妖重写更新函数MultiplePack，按照是否可以完全背包问题分成两种情况
     *
     */
    int num = 2;
    int V = 9;
    vector<int> volume = {3,2};
    vector<int> value = {4,3};
    vector<int> count = {3,4};
    vector<int> f(V+1);
    f[0] = 0;

    for(int i=0; i<num; i++){
        MultiplePack(volume[i], value[i], f, V, count[i]);
    }

//        while()
    cout << f[V] << endl;
}






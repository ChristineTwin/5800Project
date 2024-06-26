// citations
// https://www.youtube.com/watch?v=hagBB17_hvg
// https://www.geeksforgeeks.org/0-1-knapsack-problem-dp-10/
// graph of run time https://docs.google.com/spreadsheets/d/1o2jzQsc2TNVixR7Ce9QnOZ_9RcavlURibMvNX3Anl2A/edit?usp=sharing

//The below re-uses the DP approach code from KSRecon.cpp
//Testing to get run times for various C's
//See graph above for the #bits to represent C vs runtime

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <climits>

using namespace std;

// Function to find the max value
int knapsack(int C, vector<int> &weights,
             vector<int> &values, int n){
    vector<vector<int> > dp(n+1, vector<int>(C+1, 0));
    for (int item = 0; item <= weights.size(); item++){
        for (int capacity = 0; capacity <= C; capacity++){
            if (item == 0 || capacity == 0){
                dp[item][capacity] = 0;
            }
            else if (weights[item - 1] <= capacity){
                dp[item][capacity] = max(values[item - 1] +
                                             dp[item - 1][capacity - weights[item - 1]],
                                         dp[item - 1][capacity]);
            }
            else{
                dp[item][capacity] = dp[item - 1][capacity];
            }
        }
    }
    return dp[weights.size()][C];
}

void runif(vector<int> &x, int C){
    // generate n random ints less than C
    int n = x.size();
    srand(time(0));
    for (int i = 0; i < n; i++){
        x[i] = rand() % C;
    }
    return;
}

int main(){
//re-using Wes' timer code
    
    int C1 = 100000;
    int C2 = 1000000;
    int C3 = 10000000;
    int C4 = 100000000;
    int n = 100;
    vector<int> weight(n), value(n);
    runif(weight, C1);//weights less than C
    runif(value, 10);//values less than 10
    
    // for(int i = 0; i < n; i++){
    //     cout << value[i] << ", ";
    //     weight[i] = 1;
    // }
    // cout << endl;

    clock_t t1;
    t1 = clock();
    int test1 = knapsack(C1, weight, value, n);
    t1 = clock() - t1;
    //

    clock_t t2;
    t2 = clock();
    int test2 = knapsack(C2, weight, value, n);
    t2 = clock() - t2;

    clock_t t3;
    t3 = clock();
    int test3 = knapsack(C3, weight, value, n);
    t3 = clock() - t3;

    clock_t t4;
    t4 = clock();
    int test4 = knapsack(C4, weight, value, n);
    t4 = clock() - t4;

    
    cout << endl << "Results for C1 " << C1 << endl << "Max value is " << test1;
    cout << endl << "log C1: " << log2(C1) << endl << "run time: " << float(t1) / CLOCKS_PER_SEC << " seconds";
    cout << endl;

    cout << endl;
    cout << "Results for C2 " << C2 << endl << "Max value is " << test2;
    cout << endl << "log 2 C2: " << log2(C2) << endl << "run time: " << float(t2) / CLOCKS_PER_SEC << "seconds";
    cout << endl;

    cout << endl;
    cout << "Results for C3 " << C3 << endl << "Max value is " << test3;
    cout << endl << "log 2 C3: " << log2(C3) << endl << " run time: "<<  float(t3) / CLOCKS_PER_SEC << " seconds";
    cout << endl;

    cout << endl;
    cout << "Results for C4 " << C4 << endl << "Max value is " << test4;
    cout << endl << "log 2 C4: " << log2(C4) << endl << " run time: " << float(t4) / CLOCKS_PER_SEC << "seconds";
    cout << endl;

    return 0;
}

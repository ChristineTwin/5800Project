
// https://www.youtube.com/watch?v=hagBB17_hvg
// bottom up
// dp approach
// memoization
// we want to reconstruct the solution

//array of capacity X items
//traverse each row row incremeenting the capacity
//record the greatest value that can be included 
//in the container at that capacity for the included items 
//up to that row

//final result is bottom right of the table

#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

int knapsack(int C, vector<int> &weights, 
            vector<int> &values, vector<vector<int> > &dp){
    for(int item = 0; item <= weights.size(); item++){
        for(int capacity = 0; capacity <= C; capacity++){
            if(item == 0 || capacity == 0){
                dp[item][capacity] = 0;
            }
            //if the weight of the current item is <= current capacity
            //max value is the max of the the value of bag with the item vs bag w/o item
            else if(weights[item-1] <= capacity){
                dp[item][capacity] = max(values[item-1] + 
                                    dp[item-1][capacity-weights[item-1]], 
                                    dp[item-1][capacity]);
            }
            //if current item is too large, max value is the value in table above
            else{
                dp[item][capacity] = dp[item - 1][capacity];
            }
        }
    }
    //return max in bottom right corner of table
    return dp[weights.size()][C];
}

//reconstruct the solution
vector<string> solution(int n, int maxCapacity,vector<int>& weights, 
                        vector<int>& values, vector<string> recipes, 
                        vector< vector<int> > &dp){
    int i = n;//num items
    int j = maxCapacity;

    while (i > 0 && j > 0){
        if(dp[i][j] == dp[i-1][j]){
            recipes[i-1] = "";//we didn't include this
        }
        else{//if we did include this recipe
            j = j-weights[i-1];
        }
        i--;
    }
    return recipes;
}


//We are using a DP approach to knapsack to find highest "value" recipes
//when the recipes have a shared, limiting ingredient
//This would have to be repeated for all limiting ingredients
//Then would have to choose optimale subset from the set of viable recipes
//That final choosing could be done with a greedy approach, rather than knapsack
//Or the meal planning app user could "swipe right/left" too choose from the viable set
int main(){
    vector<string> recipes;
    recipes.push_back("fried chicken");
    recipes.push_back("chili and cornbread");
    recipes.push_back("pizza");
    recipes.push_back("polenta");
    recipes.push_back("enchiladas");
    recipes.push_back("friend okra");
    recipes.push_back("chicken and dumplings");
    recipes.push_back("quiche");
    recipes.push_back("lasagna");
    recipes.push_back("spaghetti and meatballs");
    recipes.push_back("shepherds pie");
    recipes.push_back("fried pork chops");
    recipes.push_back("tofu stirfry");
    recipes.push_back("coconut curry");
    
    vector<int> value; // a metric based how it's contributing to grocery list
    value.push_back(5);
    value.push_back(13);
    value.push_back(5);
    value.push_back(6);
    value.push_back(14);
    value.push_back(5);
    value.push_back(12);
    value.push_back(7);
    value.push_back(11);
    value.push_back(4);
    value.push_back(2);
    value.push_back(7);
    value.push_back(1);
    value.push_back(3);
    
    vector<int> weight;//weight the recipe uses for that ingredient
    weight.push_back(10);
    weight.push_back(10);
    weight.push_back(23);
    weight.push_back(12);
    weight.push_back(16);
    weight.push_back(25);
    weight.push_back(15);
    weight.push_back(9);
    weight.push_back(19);
    weight.push_back(8);
    weight.push_back(12);
    weight.push_back(4);
    weight.push_back(2);
    weight.push_back(3);

    int C = 20; // this will be the current weight of the
                 // currently being considered ingredient
    
    vector<vector<int> > dp(weight.size() + 1, vector<int>(C + 1));
    cout << knapsack(C, weight, value, dp) << endl;

    //getting a new vector with just the recipes to use for max value
    vector<string> toUse = solution(weight.size(), C, weight, value, recipes, dp);

    //print the DP table
    for (int i = 0; i < weight.size()+1; i++){
        for (int j = 0; j < C+1; j++){
            cout<< dp[i][j] << ", ";
        }
        cout << endl;
    }
    cout << endl;

    //print the final choice of recipes
    for (int i = 0; i < toUse.size(); i++){
        if (toUse[i].length()>1){
            cout << toUse[i] << ", ";
        }
    }
    cout << endl;

    return 0;
}
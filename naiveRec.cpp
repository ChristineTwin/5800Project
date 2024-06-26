// Modified from https://www.geeksforgeeks.org/0-1-knapsack-problem-dp-10/
/* A Naive recursive implementation of
 0-1 Knapsack problem */
#include<cstdlib>
#include<iostream>
#include<vector>
using namespace std;

// Returns the maximum value that
// can be put in a knapsack of capacity C
//given a vector of weights
//vector of values and n items
int knapSack(int C, int wt[], int val[], int n, string recipes[]){
    // Base Case
    //0 items to consider

    if (n == 0 || C == 0){
        return 0;
    }
    // If weight of the nth item is more than capacity W, then
    // this item cannot be included
    // in the optimal solution
    if (wt[n-1] > C){
        int solution = knapSack(C, wt, val, n - 1, recipes);
        return solution;
    }
    // Return the maximum of two cases:
    // (1) nth item included
    // (2) not included
    else{
        int sol1 = val[n - 1] + knapSack(C - wt[n - 1], wt, val, n - 1, recipes);
        int sol2 = knapSack(C, wt, val, n - 1, recipes);
        if (sol1 < sol2){
            return sol2;
        }
        return sol1;
    }
}

// Resolving conflicts with limiting ingredients
// Meal planner ranks recipes based on fewest # of ingredients
// that it adds to the grocery list
// Choose the top n recipes (user inputs n)
// If recipes use up same ingredients,
// need to resolve which one to put in the meal plan
// when recipe removed from the meal plan based on this result
// go back to original ranking, choose next, resolve new conflicts
// continue until no conflicts arise
//or all recipes tested, add ingredient to list
int main(){
    string recipes[] = {"fried chicken", "chili and cornbread", "pizza", "polenta", "enchiladas", "chicken and dumplings", "friend okra"};
    int value[] = {7, 3, 5, 6, 4, 5, 2};//a metric based how it's contributing to grocery list
    int weight[] = {180, 100, 230, 120, 60, 250, 50};
    int C = 300;//this will be the current weight of the
                //currently being considered ingredient
    int n = sizeof(value) / sizeof(value[0]);
    cout << knapSack(C, weight, value, n, recipes) <<endl;
    cout << endl;
    return 0;
}

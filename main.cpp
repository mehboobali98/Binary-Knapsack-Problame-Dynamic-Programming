#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

int bottomUp(vector<int> weights, vector<int> values, int W);

int topDown(vector<int> weights, vector<int> values, int W, int n);

int recursive(vector<int> weights, vector<int> values, int W, int n);

#define  ROWS 100
#define  COLS 100
int dp[ROWS][COLS];

int main() {

    vector<int> weights;
    vector<int> values;
    int W, n;

    weights.push_back(4);
    weights.push_back(3);
    weights.push_back(2);
    weights.push_back(5);

    values.push_back(10);
    values.push_back(5);
    values.push_back(2);
    values.push_back(6);

    W = 4;
    n = weights.size();
    cout << "Recursive: " << recursive(weights, values, W, n) << endl;

    memset(dp, -1, sizeof(dp));

    cout << "Top Down: " << topDown(weights, values, W, n) << endl;

    cout << "Bottom Up: " << bottomUp(weights, values, W) << endl;

    return 0;
}

int bottomUp(vector<int> weights, vector<int> values, int W) {
    int n = weights.size();
    int dp[n + 1][W + 1];

    for (int i = 0; i < W + 1; i++)
        dp[0][i] = 0;

    for (int j = 0; j < n + 1; j++)
        dp[j][0] = 0;

    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j < W + 1; j++) {
            if (weights.at(i - 1) > j) {
                dp[i][j] = dp[i - 1][j];
            } else {
                dp[i][j] = max(values.at(i - 1) + dp[i][j - weights.at(i - 1)], dp[i - 1][j]);
            }
        }
    }

    int i = n, j = W, maximum; //n=4, W=6 in this case
    vector<int> items;
    while (i and j) {
        if (dp[i][j] != dp[i - 1][j]) //if the item was included.
        {
            items.push_back(values.at(i - 1));
            i = i - 1;
            j = j - weights.at(i - 1);
        } else {
            i--;
        }
        /*
        if (weights.at(i - 1) >
            j) //means we did not add this item as weight of ith item is greater than total capacity.
        {
            i--;
        } else { //i=3,W=6
            maximum = max(values.at(i - 1) + dp[i][j - weights.at(i - 1)], dp[i - 1][j]);
            if (maximum == dp[i - 1][j]) {
                i--; // item was not added even though capacity was not violated.
            } else {
                items.push_back(values.at(i - 1));
                j -= weights.at(i - 1);
            }
        }
         */
    }
    cout << "Item Size: " << items.size() << endl;
    for (int i = 0; i < items.size(); i++) {
        cout << items.at(i) << " ";
    }
    cout << endl;
    return dp[n][W];
}

int topDown(vector<int> weights, vector<int> values, int W, int n) {
    if (n == 0 | W == 0)
        return 0;

    int value = 0;
    if (dp[n][W] != -1) {
        return dp[n][W];
    }

    if (weights[n - 1] > W) { // weight of last item is greater than the total capacity.
        dp[n][W] = recursive(weights, values, W, n - 1);
        value += dp[n][W];
    } else {
        dp[n][W] = max(values.at(n - 1) + recursive(weights, values, W - weights.at(n - 1), n),
                       recursive(weights, values, W, n - 1));
        value += dp[n][W];
    }

    return value;
}

int recursive(vector<int> weights, vector<int> values, int W, int n) {
    if (n == 0 | W == 0)
        return 0;

    int value = 0;

    if (weights[n - 1] > W) {
        value += recursive(weights, values, W, n - 1);
    } else {
        value += max(values.at(n - 1) + recursive(weights, values, W - weights.at(n - 1), n),
                     recursive(weights, values, W, n - 1));
    }
    return value;
}
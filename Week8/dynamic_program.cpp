#include<iostream>
#include<vector>

using namespace std;

int main() {
    int weightofbag, n_objects;
    cin >> weightofbag >> n_objects;
    vector <pair<int,int>> items;
    int dp[n_objects + 1][weightofbag + 1];

    for (int i = 0; i < n_objects; i++) {
        int first,second;
        cin >> first >> second;
        items.push_back(make_pair(first, second));
    }

    for (int i = 0; i <= n_objects; i++)
        dp[i][0] = 0;

    for (int j = 0; j <= weightofbag; j++)
        dp[0][j] = 0;

    for (int i = 1; i <= n_objects; i++) {
        for (int j = 1; j <= weightofbag; j++) {
            dp[i][j] = dp[i-1][j];
            if (j >= items[i].second)
                dp[i][j] = max(dp[i][j], dp[i-1][j - items[i].second] + items[i].first);
        }
    }
    cout << dp[n_objects][weightofbag];
    return 0;
}

/*
12 5
6 3
4 2
7 9
5 4
8 12
*/

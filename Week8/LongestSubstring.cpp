#include <bits/stdc++.h>
using namespace std;
int main() {
    string x1, x2;
    cin >> x1 >> x2;
    int s1 = x1.length(), s2 = x2.length();
    int dp[s1 + 1][s2 + 1];
    memset(dp, 0, sizeof(dp));
    for(int i = 1; i <= s1; i++) {
        for(int j = 1; j <= s2; j++) {
            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            if(s1[i - 1] == s2[j - 1]) {
                dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1);
            }
        }
    }
    cout << dp[s1][s2] << endl;
}

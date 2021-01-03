class Solution {
public:
    int numDistinct(string s, string t) {
        vector<long long> dp(t.size()+1,0);
        dp[0] = 1;
        for(int i=0; i < s.size(); i++) {
            for(int j=t.size(); j > 0; j--) {
                if(s[i] == t[j-1]) {
                    dp[j] += dp[j-1];
                }
            }
        }
        return (int)dp.back();
    }
};
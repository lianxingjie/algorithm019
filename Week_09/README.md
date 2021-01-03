# 字符串匹配暴力法代码
```C++
int forceSearch(string text, string pattern) {    
    int len_txt = text.length();    
    int len_pat = pattern.length();    
    for (int i = 0; i <= len_txt - len_pat; i++) {        
        int j = 0;        
        for (j = 0; j < len_pat; j++) {            
            if (text[i + j] != pattern[j]) 
            break;        
        }        
        if (j == len_pat) {           
            return i;        
        }    
    }   
    return -1;
}
```

# Rabin-Karp 代码
```C++
const int D = 256;
const int Q = 9997;
int RabinKarpSerach(string txt, string pat) {    
    int M = pat.length();    
    int N = txt.length();    
    int i, j;    
    int patHash = 0, txtHash = 0;    
    for (i = 0; i < M; i++) {        
        patHash = (D * patHash + pat[i]) % Q;        
        txtHash = (D * txtHash + txt[i]) % Q;    
    }    
    int highestPow = 1;  // pow(256, M-1)    
    for (i = 0; i < M - 1; i++)         
    highestPow = (highestPow * D) % Q;    
    for (i = 0; i <= N - M; i++) { // 枚举起点        
        if (patHash == txtHash) {            
            for (j = 0; j < M; j++) {                
                if (txt[i + j] != pat[j])                    
                break;            
            }            
            if (j == M)                
                return i;        
        }        
        if (i < N - M) {           
            txtHash = (D * (txtHash - txt[i] * highestPow) + txt[i + M]) % Q;           
            if (txtHash < 0)                
                txtHash += Q;       
        }    
        
    }    
    return -1;
}
```

# 正则表达式匹配
```C++
class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.size();
        int n = p.size();

        auto matches = [&](int i, int j) {
            if (i == 0) {
                return false;
            }
            if (p[j - 1] == '.') {
                return true;
            }
            return s[i - 1] == p[j - 1];
        };

        vector<vector<int>> f(m + 1, vector<int>(n + 1));
        f[0][0] = true;
        for (int i = 0; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (p[j - 1] == '*') {
                    f[i][j] |= f[i][j - 2];
                    if (matches(i, j - 1)) {
                        f[i][j] |= f[i - 1][j];
                    }
                }
                else {
                    if (matches(i, j)) {
                        f[i][j] |= f[i - 1][j - 1];
                    }
                }
            }
        }
        return f[m][n];
    }
};
```
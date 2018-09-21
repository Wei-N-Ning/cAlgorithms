//
// Created by wein on 21/09/18.
//

// source
// https://www.geeksforgeeks.org/count-palindrome-sub-strings-string/

#include <stdio.h>
#include <string.h>
#include <stddef.h>


// Return the total number of palindrome substring of
// length greater then equal to 2
int CountPS(const char* str, size_t n) {
    if (! n) {
        return 0;
    }

    // creat empty 2-D matrix that counts all palindrome
    // substring. dp[i][j] stores counts of palindromic
    // substrings in st[i..j]
    int dp[n][n];
    memset(dp, 0, sizeof(dp));

    // P[i][j] = 1 if substring str[i..j] is palindrome,
    // else 0
    int P[n][n];
    memset(P, 0, sizeof(P));

    // palindrome of single lenght
    for (int i = 0; i < n; i++)
        P[i][i] = 1;

    // palindrome of length 2
    for (int i = 0; i < n - 1; i++) {
        if (str[i] == str[i + 1]) {
            P[i][i + 1] = 1;
            dp[i][i + 1] = 1;
        }
    }

    // Palindromes of length more then 2. This loop is similar
    // to Matrix Chain Multiplication. We start with a gap of
    // length 2 and fill DP table in a way that gap between
    // starting and ending indexes increases one by one by
    // outer loop.
    for (int gap = 2; gap < n; gap++) {
        // Pick starting point for current gap
        for (int i = 0; i < n - gap; i++) {
            // Set ending point
            int j = gap + i;

            // If current string is palindrome
            if (str[i] == str[j] && P[i + 1][j - 1])
                P[i][j] = 1;

            // Add current palindrome substring ( + 1)
            // and rest palinrome substring (dp[i][j-1] + dp[i+1][j])
            // remove common palinrome substrings (- dp[i+1][j-1])
            if (P[i][j] == 1)
                dp[i][j] = dp[i][j - 1] + dp[i + 1][j] + 1 - dp[i + 1][j - 1];
            else
                dp[i][j] = dp[i][j - 1] + dp[i + 1][j] - dp[i + 1][j - 1];
        }
    }

    // return total palindromic substrings
    return dp[0][n - 1];
}

void RunTinyTests();

void test_short_sequence() {
    printf("%d ", CountPS("", 0));
    printf("%d ", CountPS("1", 1));
    printf("%d ", CountPS("11", 2));
    printf("%d ", CountPS("12", 2));
    printf("%d ", CountPS("121", 3));

    const char* str = "HDQHQDQHDH";
    printf("%d\n", CountPS(str, strlen(str)));
}

void test_longer_sequence() {
    const char* str = "abaabababaabababaabababababaaabaababbbaaabababababaaabbbbbbab";
    printf("%d\n", CountPS(str, strlen(str)));
}

void test_ridiculous_sequence() {
    const char* str = "YEYQYYEQYYEYYQYYYEYEYEY"
                      "HDHEHQHEHHQHEHQHEHHQHHH"
                      "EHHDUHH12345HH54321QHUY"
                      "EHHYYHQEEHHEQYHEHHQHHEH"
                      "12345HH54321@HH!H!@H~HH"
                      "EHHDUHH12345HH54321QHUY";
    printf("%d\n", CountPS(str, strlen(str)));
}

int main() {
    RunTinyTests();
    return 0;
}
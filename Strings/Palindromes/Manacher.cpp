// Input: string s of size n
// Output: vector R of size 2 * n - 1
// R[i] - radius of the longest palindrome with center in i for string ss
// ss = s[0] + 'S' + s[1] + 'S' + ... + '$' + s[n - 1]
// Example:
// s: a   b   a   a   b   a   a   c   a   a   b   b   b   b   a   a   c   a   c
//ss: a $ b $ a $ a $ b $ a $ a $ c $ a $ a $ b $ b $ b $ b $ a $ a $ c $ a $ c
// R: 0 0 1 0 0 3 0 0 2 0 0 1 0 0 3 0 0 1 0 0 0 1 1 6 1 1 0 0 0 1 0 0 1 0 1 0 0
// Radius of even palindrome with center in s[i]: R[2 * i - 1]
// Radius of odd palindrome with center in s[i]: R[2 * i]
// Complexity: O(|s|)
// Source: Marek Sommer


vector<int> Manacher(string &s, int n)
{
    vector<int> R(2 * n - 1);
    // l, r - left and right end of the palindrome with center in i; i and m defined below
    int l = 0, r = 0, i = 0, m = 0;
    while (i < 2 * n - 1)
    {
        // Compares letter by letter
        while (l > 0 && r + 1 < n && s[l - 1] == s[r + 1])
        {
            l--;
            r++;
        }
        R[i] = (r - l + 1) / 2;
        m = i - 1;
        i++;
        l++;

        // Let C be the index for which we calculated the radius in the loop above.
        // We can compute the radiuses for indexes i = C + l by using radiuses
        // computed beforehand for indexes m = C - l while l < R[C] - 1
        // or the left end of the palindrome with center in m won't meet the left
        // end of the palindrome with center in C
        while (l < r && i / 2 + R[m] != r)
        {
            // If the palindrome with center in m is completely covered by the
            // palindrome with center in C then R[i] = R[m].
            // If it reaches over the left end of the palindrome with center in C
            // then, by knowing that in this case the right end of the palindrome
            // with center in i cannot reach over the right end of the palindrome
            // with center in C (because the palindrome in C would be longer),
            // we can say that both of these right ends will be in the same place.
            R[i] = min(R[m], (r - l + 1) / 2);
            i++;
            m--;
            l++;
        }
    }
    return R;
}

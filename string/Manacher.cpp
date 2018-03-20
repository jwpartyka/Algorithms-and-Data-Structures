//Przekazujesz słowo s długości n, a funkcja zwraca wektor R długości 2 * n - 1.
//R[i] - długość promienia najdłuższego palindromu o środku w i dla słowa ss.
//ss = s[0] + '$' + s[1] + '$' + ... + '$' + s[n - 1]
//Przykład:
// s: a   b   a   a   b   a   a   c   a   a   b   b   b   b   a   a   c   a   c
//ss: a $ b $ a $ a $ b $ a $ a $ c $ a $ a $ b $ b $ b $ b $ a $ a $ c $ a $ c
// R: 0 0 1 0 0 3 0 0 2 0 0 1 0 0 3 0 0 1 0 0 0 1 1 6 1 1 0 0 0 1 0 0 1 0 1 0 0
//Środek parzystego palindromu dla litery s[i]: R[2 * i - 1]
//Środek nieparzystego palindromu dla litery s[i]: R[2 * i]
//Złożoność: O(|s|)
//Source: Marek Sommer

//Pierwszą pętlę while wraz z tym co po niej następuje można zamienić z drugą.
vector<int> Manacher(string &s, int n)
{
    vector<int> R(2 * n - 1);
    //l, r - lewy i prawy koniec palindromu o środku w i, i, m - zdefiniowane poniżej
    int l = 0, r = 0, i = 0, m = 0;
    while (i < 2 * n - 1)
    {
        //Liczymy brutalnie wynik porównując literka po literce:
        while (l > 0 && r + 1 < n && s[l - 1] == s[r + 1])
        {
            l--;
            r++;
        }
        R[i] = (r - l + 1) / 2;
        m = i - 1;
        i++;
        l++;

        //Oznaczmy przez C indeks, dla którego promień policzyliśmy w pętli powyżej.
        //Możemy wyznaczać długości promieni dla indeksów i = C + l na podstawie wyników
        //dla indeksów m = C - l dopóki l < R[C] - 1 lub lewy koniec palindromu
        //o środku w indeksie m nie pokryje się z lewym końcem palindromu
        //o środku w indeksie C.
        while (l < r && i / 2 + R[m] != r)
        {
            //Jeżeli palindrom o środku w m całkowicie zawiera się
            //w palindromie o środku w C to R[i] = R[m].
            //Jeżeli wystaje on poza lewy koniec palindromu o środku w C to wiedząc,
            //że wtedy prawy koniec palindromu o środku w i nie może wystawać poza
            //prawy koniec palindromu w C (bo inaczej palindrom w C byłby dłuższy)
            //możemy stwierdzić, że te dwa prawe końce będą w tym samym miejscu.
            R[i] = min(R[m], (r - l + 1) / 2);
            i++;
            m--;
            l++;
        }
    }
    return R;
}

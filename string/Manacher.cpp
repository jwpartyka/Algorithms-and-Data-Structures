//Przekazujesz słowo s długości n, a funkcja zwraca wektor R długości 2 * n - 1
//R[i] - długość promienia najdłuższego palindromu o środku w i dla słowa
//ss = s[0] + '$' + s[1] + '$' + ... + '$' + s[n-1]
//Przykład:
// s: a   b   a   a   b   a   a   c   a   a   b   b   b   b   a   a   c   a   c
//ss: a $ b $ a $ a $ b $ a $ a $ c $ a $ a $ b $ b $ b $ b $ a $ a $ c $ a $ c
// r: 0 0 1 0 0 3 0 0 2 0 0 1 0 0 3 0 0 1 0 0 0 1 1 6 1 1 0 0 0 1 0 0 1 0 1 0 0
//Środek parzystego palindromu dla litery s[i]: R[2*i-1]
//Środek nieparzystego palindromu dla litery s[i]: R[2*i]
//***Podziękowania dla Marka Sommera, od którego ściągnąłem trochę kodu***

//Długa, szczegółowa wersja
//Pierwszą pętlę while wraz z tym co po niej następuje można zamienić z drugą
vector<int> Manacher(string s, int n)
{
    vector<int> R(2 * n - 1);
    int p = 0, k = 0, i = 0, m = 0;
    while (i < 2 * n - 1)
    {
        //Liczymy brutalnie wynik porównując literka po literce:
        while (p > 0 && k + 1 < n && s[p - 1] == s[k + 1])
        {
            p--;
            k++;
        }
        R[i] = (k + 1 - p) / 2;
        p++;
        m = i - 1;
        i++;

        //Oznaczmy przez C indeks, dla którego promień policzyliśmy w pętli powyżej.
        //Możemy wyznaczać długości promieni dla indeksów i = C + l na podstawie wyników
        //dla indeksów m = C - l dopóki l < R[C] - 1 lub lewy koniec palindromu
        //o środku w indeksie m nie pokryje się z lewym końcem palindromu
        //o środku w indeksie C.
        while (p < k && i / 2 + R[m] != k)
        {
            //Jeżeli palindrom o środku w m całkowicie zawiera się
            //w palindromie o środku w C to R[i] = R[m].
            //Jeżeli wystaje on poza lewy koniec palindromu o środku w C to wiedząc,
            //że wtedy prawy koniec palindromu o środku w i nie może wystawać poza
            //prawy koniec palindromu w C (bo inaczej palindrom w C byłby dłuższy)
            //możemy stwierdzić, że te dwa prawe końce będą w tym samym miejscu.
            R[i] = min(R[m], (k + 1 - p) / 2);
            i++;
            m--;
            p++;
        }
    }
    return R;
}

//Krótszy kod:
vector<int> Manacher(string s, int n)
{
    vector<int> R(2 * n - 1);
    int p = 0, k = 0, i = 0, m = 0;
    while (i < 2 * n - 1)
    {
        while (p < k && i / 2 + R[m] != k)
        {
            R[i++] = min(R[m--], (k + 1 - p++) / 2);
        }
        while (p > 0 && k + 1 < n && s[p - 1] == s[k + 1])
        {
            p--;
            k++;
        }
        R[i] = (k + 1 - p++) / 2;
        m = i++ - 1;
    }
    return R;
}

//i jeszcze krótszy:
vector<int> Manacher(string s, int n)
{
    vector<int> R(2 * n - 1);
    for (int i = 0, m = 0, p = 0, k = 0; i < 2 * n - 1; m = i++ - 1)
    {
        while (p < k && i / 2 + R[m] != k)
        {
            R[i++] = min(R[m--], (k + 1 - p++) / 2);
        }
        while (p > 0 && k + 1 < n && s[p - 1] == s[k + 1])
        {
            p--, k++;
        }
        R[i] = (k + 1 - p++) / 2;
    }
    return R;
}

//Zwraca tablicę Z dla słowa S
//Żeby wuszukać wzorzec P w tekście T: S = P + '$' + T;
//Złożoność: O(|S|)

//Dłuższa, może bardziej czytelna wersja:
vector<int> Z_Function(string s)
{
    vector<int> Z(s.size());
    int i = 1, m = 1, len = 0, n = s.size();
    while (i < n)
    {
        m = i;

        //Dopóki słowo s[i...i+len] nie wychodzi poza słowo s
        //oraz jest równe prefiksowi s[0...len]:
        while (i + len < n && s[i + len] == s[len])
        {
            len++;
        }
        Z[i] = len;
        i++;
        //Dopóki można uzupełnić Z[i] w zależności od poprzednio obliczoncyh wartości:
        while (i + Z[i - m] < m + len)
        {
            Z[i] = Z[i - m];
            i++;
        }

        //Zaktualizowanie długości aktualnie najdłuższego pasującego prefiksu
        //Jeżeli (i - m > len) -> len = 0, w przeciwnym wypadku len -= i - m
        len -= min(len, i - m);
    }
    return Z;
}

//Krótka wersja:
vector<int> Z_Function(string s)
{
    //Dodanie znaku niewystępującego w alfabecie, aby skrócić warunek w pierwszym while
    s += '#';
    vector<int> Z(s.size());
    for (int i = 1, m = 1, len = 0; i < s.size(); len -= min(len, i-m), m = i)
    {
        //Dopóki słowo s[i...i+len] jest równe prefiksowi s[0...len]:
        while (s[i + len] == s[len])
        {
            len++;
        }
        Z[i++] = len;
        //Dopóki można uzupełnić Z[i] w zależności od poprzednio obliczoncyh wartości:
        while (i + Z[i - m] < m + len)
        {
             Z[i++] = Z[i - m];
        }
    }
    //Usuwa wartość dla znaku '#'
    Z.pop_back();
    return Z;
}

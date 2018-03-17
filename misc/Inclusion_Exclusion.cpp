//Przykładowe zastosowanie zasady włączeń i wyłączeń
//Udostępnia operacje:
//1) Dodaj liczbę do multizbioru
//2) Usuń liczbę z multizbioru
//3) Ile jest liczb względnie pierwszych w multizbiorze

using ll = long long;

const int MAXN = 5e5 + 5;

int d[MAXN], mu[MAXN]; //d[i] - Liczba liczb podzielnych przez i,  m[] - funkcja Mobiusa
ll coprime; //Liczba liczb względnie pierwszych
vector<int> p[MAXN]; //p[i] - lista dzielników i

//Wyznacza dzielniki pierwsze liczb z przedziału [1...n] oraz liczy funkcję Mobiusa
void sieve(int n)
{
    for (int i = 1; i <= n; i++)
    {
        mu[i] = i;
    }

    for (int i = 2; i <= n; i++)
    {
        if (p[i].empty())
        {
            for (int j = i; j <= n; j += i)
            {
                p[j].push_back(i);
                mu[j] /= -i;
            }
        }
    }
}

//Zwraca liczbę liczb w multizbiorze względnie pierwszych z v
int solve(int v, int co)
{
    ll sum = 0;
    for (int mask = 0; mask < (1 << p[v].size()); mask++)
    {
        int x = 1;
        for (int j = 0; j < p[v].size(); j++)
        {
            if (mask & (1 << j)) x *= p[v][j];
        }
        if (co == -1) d[x] += co;
        sum += d[x] * mu[x];
        if (co == 1) d[x] += co;
    }
    return sum;
}

//Dodaje liczbe v do multizbioru:
inline void add(int v)
{
    coprime += solve(v, 1);
}

//Usuwa liczbę v z multizbioru:
inline void erase(int v)
{
    coprime -= solve(v, -1);
}

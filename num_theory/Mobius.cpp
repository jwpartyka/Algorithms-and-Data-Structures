//Funkcja Mobiusa:
//mob[1] = 1
//mob[n] = 0 jeżeli n jest podzielne przez kwadrat liczby pierwszej
//mob[n] = (-1)^k jeżeli liczba n jest iloczynem k różnych liczb pierwszych
//Jeżeli n = p1 * p2 * ... * pk to n / -p1 / -p2 / ... / -pk = (-1)^k
//Suma po mob[d] dla wszystkich dzielników d liczby n jest równa 0.
//Jeżeli NWD(a, b) = 1 to mob[a * b] = mob[a] * mob[b] 

const int MAXN = 1e7+5;

int mob[MAXN], sieve[MAXN];

void Mobius(int n)
{
    for (int i = 1; i <= n; i++)
    {
        mob[i] = i;
    }

    for (int i = 2; i <= n; i++)
    {
        if (mob[i] == i)
        {
            for (int j = i; j <= n; j += i)
            {
                mob[j] /= -i;
            }
        }
    }

    for (int i = 1; i <= n; i++)
    {
        if (abs(mob[i]) != 1)
        {
            mob[i] = 0;
        }
    }
}

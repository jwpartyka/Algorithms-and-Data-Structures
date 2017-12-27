//Funkcja Mobiusa:
//mob[1] = 1
//mob[n] = 0 jeżeli n jest podzielne przez kwadrat liczby pierwszej
//mob[n] = (-1)^k jeżeli liczba n jest iloczynem k różnych liczb pierwszych
//Suma po mob[d] dla wszystkich dzielników d liczby n jest równa 0.
//Jeżeli NWD(a, b) = 1 to mob[a] * mob[b] = mob[a * b]

const int MAXN = 1e7+5;

int mob[MAXN], sieve[MAXN];

void Mobius(int n)
{
    for (int i = 1; i <= n; i++)
    {
        mob[i] = 1;
    }
    for (int i = 2; i <= n; i++)
    {
        if (!sieve[i])
        {
            mob[i] = -1;
            for (int j = 2 * i; j <= n; j += i)
            {
                if (!sieve[j]) sieve[j] = i;
                if (j % (i * i) == 0)
                {
                    mob[j] = 0;
                    continue;
                }
                mob[j] *= -1;
            }
        }
    }
}

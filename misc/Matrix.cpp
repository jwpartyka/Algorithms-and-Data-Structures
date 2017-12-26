//Szybkie potęgowanie macierzy
//Macierze potrzebne do zadania uzupełniać w Base

using namespace std;
using ll = long long;

const int MAXN = 4;

ll mod = 1e9+7;
ll Base[4][MAXN][MAXN] = { {}, //Pusta  macierz
                            {{1, 0, 0}, {0, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}, //Macierz pełniąca rolę "1"
                            {{1, 1, 0, 1}, {3, 0, 1, 3}, {2, 0, 1, 2}, {0, 0, 0, 1}}, //Macierz do zadania
                            {{1, 0, 0, 1}} }; //Wektor do zadania
struct Matrix
{
    vector<vector<ll>> Data;
    int N;
    ll res[MAXN];

    Matrix(int N, int x) : N(N), Data(N, vector<ll>(N, 0))
    {
        init(x);
    }

    Matrix operator*(const Matrix &B)const
    {
        assert(N == B.N);
        Matrix Result(N, 0);
        for (int k = 0; k < N; k++)
        {
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    Result.Data[i][j] = (Result.Data[i][j] + (long long)Data[i][k] * (long long)B.Data[k][j])%mod;
                }
            }
        }
        return Result;
    }

    //Inicjowanie wartosci w macierzy
    void init(int x)
    {
        if (x == 0) return ;
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                Data[i][j] = Base[x][i][j];
            }
        }
    }

    //Podniesienie macierzy do potęgi k
    Matrix pow(ll k)const
    {
        //cout << k << "\n";
        Matrix Result(N, 1), Coef = *this;
        while (k > 0)
        {
            if (k&1) Result = Result * Coef;
            k /= 2;
            Coef = Coef * Coef;
        }
        return Result;
    }

    //Wymnozenie macierzy z wektorem
    void calcRes(int x)
    {
        for (int i = 0; i < N; i++)
        {
            res[i] = 0;
            for (int k = 0; k < N; k++)
            {
                res[i] = (res[i] + Base[x][0][k] * Data[k][i])%mod;
            }
        }
    }
};

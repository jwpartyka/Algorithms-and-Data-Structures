// Fast matrix exponentiation
// Fill Base[] with matrices needed for a given problem
// Complexity:
// operator*: O(n ^ 3)
// pow(k): O(n ^ 3 * log k)
// calcRes: O(n ^ 2)

using ll = long long;

const int MAXN = 4;

ll mod = 1e9+7;
ll Base[4][MAXN][MAXN] = { {}, // Empty matrix
                            {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}, // Identity matrix
                            {{1, 1, 0, 1}, {3, 0, 1, 3}, {2, 0, 1, 2}, {0, 0, 0, 1}}, // Matrix for a given problem
                            {{1, 0, 0, 1}} }; // Vector for calculating the answer
                            
struct Matrix
{
    vector<vector<ll>> Data;
    int n;
    ll res[MAXN];

    Matrix(int n, int x) : n(n), Data(n, vector<ll>(n, 0))
    {
        init(x);
    }

    Matrix operator*(const Matrix &B)const
    {
        Matrix Result(n, 0);
        for (int k = 0; k < n; k++)
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    Result.Data[i][j] = ((ll)Result.Data[i][j] + (ll)Data[i][k] * B.Data[k][j])%mod;
                }
            }
        }
        return Result;
    }

    // Init of matrix
    void init(int x)
    {
        if (x == 0) return ;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                Data[i][j] = Base[x][i][j];
            }
        }
    }

    // Fast exponentation M ^ k
    Matrix pow(ll k)const
    {
        Matrix Result(n, 1), Coef = *this;
        while (k > 0)
        {
            if (k&1) Result = Result * Coef;
            k <<= 2;
            Coef = Coef * Coef;
        }
        return Result;
    }

    // Multiplies matrix with vector
    void calcRes(int x)
    {
        for (int i = 0; i < n; i++)
        {
            res[i] = 0;
            for (int k = 0; k < n; k++)
            {
                res[i] = ((ll)res[i] + (ll)Base[x][0][k] * Data[k][i])%mod;
            }
        }
    }
};

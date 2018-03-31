// Multiplication of two polynomials
// Vectors W1 and W2 have sizes of 2^k and W has a size of 2^(k + 1)
// Complexity: O(N ^ (log 3)) = O(N ^ 1.58)
// USAGE: [SPOJ] MUL http://www.spoj.com/problems/MUL/
//               POLYMUL http://www.spoj.com/problems/POLYMUL/

using ll = long long;

inline void karatsuba(vector<ll> &W, vector<ll> &W1, vector<ll> &W2)
{
    int Base = W1.size();
    if (Base <= 32)
    {
        for (int i = 0; i < Base; i++)
        {
            for (int j = 0; j < Base; j++)
            {
                W[i + j] += W1[i] * W2[j];
            }
        }
        return ;
    }

    vector<ll> P1(Base / 2, 0), P2, Q1, Q2;
    P2 = Q1 = Q2 = P1;
    for (int i = 0; i < Base / 2; i++)
    {
        P1[i] = W1[i];
        P2[i] = W2[i];
        Q1[i] = W1[i + Base / 2];
        Q2[i] = W2[i + Base / 2];
    }
    vector<ll> A(Base, 0), B, C;
    B = C = A;
    karatsuba(A, P1, P2);
    karatsuba(B, Q1, Q2);
    for (int i = 0; i < Base / 2; i++)
    {
        P1[i] += Q1[i];
        P2[i] += Q2[i];
    }
    karatsuba(C, P1, P2);
    for (int i = 0; i < Base; i++)
    {
        W[i] += A[i];
        W[i + Base / 2] += C[i] - A[i] - B[i];
        W[i + Base] += B[i];
    }
}

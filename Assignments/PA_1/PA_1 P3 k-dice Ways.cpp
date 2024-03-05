/* PA_1 P3 k-dice Ways */
/* Name : Nevish Pathe */
/* Roll No. 220757*/
/* Handle : npqrrr */

#include<iostream>
using namespace std;

#define MAXN 100000
#define MAXK 20
#define MOD 998244353
typedef long long int ll;

/* Functions for Matrix Multiplication; (k,k) by (k,1) and (k,k) by (k,k) respectively */
ll* kkk1(int k, ll **m1, ll *m2) {
    ll *m3 = new ll[MAXK];
    for (int i = 0; i < k; ++i) {
        m3[i] = 0;
        for (int j = 0; j < k; ++j) {
            m3[i] += ((m1[i][j] % MOD) * (m2[j] % MOD)) % MOD;
            m3[i] %= MOD;
        }
    }
    return m3;
}

ll** kkkk(int k, ll **m1, ll **m2) {
    ll **m3 = new ll*[MAXK];
    for(int i = 0; i < k; i++)
    {
        m3[i] = new ll[MAXK];
    }
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < k; ++j) {
            m3[i][j] = 0;
            for(int m = 0; m < k; ++m)
            {
            m3[i][j] += ((m1[i][m] % MOD) * (m2[m][j] % MOD)) % MOD;
            m3[i][j] %= MOD;
            }
        }
    }
    return m3;
}

/* Matrix Exponentiation (fast) */
ll** matpow(int k, ll **base, ll pow) {
    ll **mull = new ll*[MAXK];
    for(int i = 0; i < k; i++)
    {
        mull[i] = new ll[MAXK];
    }
    if (pow == 1) {
        for (int i = 0; i < k; ++i) {
            for (int j = 0; j < k; ++j) {
                mull[i][j] = (base[i][j] % MOD);
            }
        }
        return mull;
    }

    ll **temp = new ll*[MAXK];
    for(int i = 0; i < k; i++)
    {
        temp[i] = new ll[MAXK];
    }
    temp = matpow(k, base, pow / 2);
    mull = kkkk(k, temp, temp);

    if (pow % 2 == 1) {
        mull = kkkk(k, mull, base);
    }

    return mull;
}

/* Naive approach for smaller values of N using the recurrence presented below */
ll GetWaysNaive(ll d, ll f, ll N)
{
    /* G(T) = Sum S_k(T, r)  */
    /* S_k (T,n) = S_k(T-1, n-1) + S_k (T-2, n-2) + ... + S_k(T-k, n-k) */
    ll dp[d+1][N+1] = {0};
    for(ll i = 0; i < d+1; i++)
    {
        for(ll j = 0; j < N + 1; j++) dp[i][j] = 0;
    }
    dp[0][0] = 1;
    for (ll i = 1; i <= d; i++) {
            for (ll j = 0; j <= N; j++) {
                for (ll k = 1; k <= f; k++) {
                    if (j >= k) {
                        dp[i][j] = ( (dp[i][j] % MOD) + (dp[i - 1][j - k] % MOD) ) % MOD;
                    } else {
                        break;
                    }
                }
            }
        }
    
    return dp[d][N];
}

void GetWays()
{
    ll N, k;
    cin >> N >> k;

    /* Trivial Case*/
    if(N <= k) {ll pp = 1 << (N-1); cout << pp << "\n"; return;}

    /* Optimized using Matrix Exponentiation (similar to Clever_Algo_Fib) */
    /* Memory Allocations */
    ll **A = new ll*[MAXK];
    for(int i = 0; i < k; i++) A[i] = new ll[MAXK];

    ll *G = new ll[MAXK];
    for(int i = 0; i < k; i++) G[i] = 0;

    ll **D = new ll*[MAXK];
    for(int i = 0; i < k; i++) D[i] = new ll[MAXK];

    ll *H = new ll[MAXK];

    /* 
    
    We require (say), G_k(T) = Sum(r : 1 to T) S_k(T,r)
    S_k(T,r) = GetWaysNaive(r, k, T) is given by the recurrence:
    S_k(T,r) = S_k(T-1,r) + S_k(T-2,r) + S_k(T-3,r) + ... + S_k(T-k,r) 
    So, G_k(T) = Sum(m : 1 to k) G_k(T-m) 
    Which yields us a matrix equation of the form 
    
    G(T)          /  1 1 1 1 ... 1 1  \   G(T-1)
    G(T-1)        |  1 0 0 0 ... 0 0  |   G(T-2)
    G(T-2)     =  |  0 1 0 0 ... 0 0  |   G(T-3)
    ...           |  ...         ...  |   ...
    G(T-k)        \  0 0 0 0 0 0 1 0  /   G(T-k-1)

    which further gives us (assuming bottom element as reference)

    G_(T-k) = A^(N-k) * G_(0)   
    first entry of which; is the required value

    */

    /* Building up A */
    for(int i = 1; i < k; i++)
    {
        for(int j = 0; j < k; j++) A[i][j] = 0;

        A[i][i-1] = 1;
    }
    for(int j = 0; j < k; j++) A[0][j] = 1;

    /* Pre-processing G[i] since 2 <= k <= 20 */
    for(int i = 0; i < k; i++)
    {
        for(ll j = 1; j <= k; j++)
        {
            G[i] += (GetWaysNaive(j, k, k-i) % MOD);
            G[i] %= MOD;
        }
    }

    /* D = A^(N-k), H = D * G, We need H[0] */
    D = matpow(k, A, N-k);
    H = kkk1(k, D, G);
    cout << (H[0] % MOD) << "\n";
    
}

int main(){
    ll T;
    cin >> T;

    while(T--) GetWays();

    return 0;
}
/* PA_1 P1 MaxCraft */
/* Name : Nevish Pathe */
/* Roll No. 220757*/
/* Handle : npqrrr */

#include<iostream>
using namespace std;

#define MAXN 100000
typedef long long int ll;

void GetMaxSumSubArray()
{
    int N;
    ll a[MAXN], S[MAXN];

    cin >> N;
    for(int i = 0; i < N; i++) cin >> a[i];

    /* Modifying the Max-sum-subarray Algorithm by evaluating backwards.
    Max-sum-subarray till i'th index now translates to starting from i'th index */
    S[N-1] = a[N-1];
    for(int i = N-2; i >= 0; i--)
    {
        if(S[i + 1] > 0) S[i] = S[i+1] + a[i];
        else S[i] = a[i];
    }
    
    for(int i = 0; i < N; i++) cout << S[i] << " ";

    cout << "\n";
}

int main(){
    int T;
    cin >> T;

    while(T--) GetMaxSumSubArray();

    return 0;
}
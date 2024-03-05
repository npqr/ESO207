/* PA_2 P1 Number of Inversions */
/* Name : Nevish Pathe */
/* Roll No. 220757*/
/* Handle : npqrrr */

#include <iostream>
#include <vector>
using namespace std;
typedef long long int ll;

/* Merge and Count Inversions*/
ll MaCI(vector<int>& A, vector<int>& C, int l, int mid, int r) {
    ll cnt = 0;
    int i = l;        
    int j = mid + 1;   
    int k = l;        

    while (i <= mid && j <= r) {
        if (A[i] <= A[j]) {
            C[k++] = A[i++];
        } else {
            cnt += (mid - i + 1);
            C[k++] = A[j++];
        }
    }

    while (i <= mid) {
        C[k++] = A[i++];
    }
    while (j <= r) {
        C[k++] = A[j++];
    }

    for (int x = l; x <= r; x++) {
        A[x] = C[x];
    }

    return cnt;
}

/* Sort and Count Inversions */
ll SaCI(vector<int>& A, vector<int>& C, int l, int r) {
    ll cnt = 0;
    if (l < r) {
        int mid = (l + r) / 2;

        cnt += SaCI(A, C, l, mid);
        cnt += SaCI(A, C, mid + 1, r);
        
        cnt += MaCI(A, C, l, mid, r);
    }
    return cnt;
}

void GetInversions(){
    int N, gg;
    cin >> N;

    vector<int> A;
    for(int i = 0; i < N; i++) {cin >> gg; A.push_back(gg);}

    vector<int> C(N);

    cout << SaCI(A, C, 0, N-1) << "\n";
}

int main(){
    ll T;
    cin >> T;
    
    while(T--) GetInversions();

    return 0;
}

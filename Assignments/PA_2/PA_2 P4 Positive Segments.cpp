/* PA_2 P4 Positive Segments */
/* Name : Nevish Pathe */
/* Roll No. 220757*/
/* Handle : npqrrr */

#include <iostream>
#include <vector>

using namespace std;
typedef long long int ll;

void kPositiveSegments() {
    int n, s, gg, kk, q, k;
    cin >> n >> s;

    /* -1 in indices to convert into 0-based indexing from 1-based */
    vector<int> A;
    for(int i = 0; i < n; i++) {cin >> gg; A.push_back(gg);}
    vector<int> L, R;
    for(int i = 0; i < s; i++) {cin >> gg >> kk; L.push_back(gg-1); R.push_back(kk-1);}
    cin >> q >> k;
    vector<int> Qe;
    for(int i = 0; i < q; i++) {cin >> gg; Qe.push_back(gg-1);}

    /* Binary Search on possible number of queries */
    /* Min possible = 0, Max = q (+1 if impossible) */
    int pref[n+1];
    int Lo = 0, Hi = q+1, mid = -1;
        while(Lo < Hi){
            /* Maintaining count of positive segments */
            int f = 0;

            mid = (Lo + Hi)/2;

            /* Querying and modifying the array only till 'mid' number of queries */
            int temp[n];
            for(int i=0; i<n; i++) temp[i] = A[i];
            for(int i=0; i<mid; i++) {temp[Qe[i]] = 1;}
            
            pref[0] = temp[0];
            for(int i=1; i<n; i++) {pref[i] = pref[i-1] + temp[i];}
            // for(int i=0; i<n; i++) {cout << " " << A[i];}
            // cout << "\n";
            
            /* Iterating over all segments to get count of positive ones */
            for(int i = 0; i < s; i++) 
            {
                if(L[i] > 0) {if((pref[R[i]] - pref[L[i]-1]) > 0) {f++;}}
                else if(pref[R[i]] > 0) f++;
            }
            if(f < k) {Lo = mid+1;}
            else Hi = mid;
        }
        cout << ((Lo == q+1)? -1 : Hi) << "\n";
}

int main(){
    int T;
    cin >> T;
    
    while(T--) kPositiveSegments();

    return 0;
}

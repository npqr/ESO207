/* PA_1 P2 Bob the Destroyer */
/* Name : Nevish Pathe */
/* Roll No. 220757*/
/* Handle : npqrrr */

#include<iostream>
using namespace std;

#define MAXN 100000
typedef long long int ll;

/* Merge Sort Implementation */

void merge(int arr[], int p, int q, int r) {

int n1 = q - p + 1;
int n2 = r - q;

int L[n1], M[n2];

for (int i = 0; i < n1; i++)
    L[i] = arr[p + i];
for (int j = 0; j < n2; j++)
    M[j] = arr[q + 1 + j];

int i, j, k;
i = 0;
j = 0;
k = p;

while (i < n1 && j < n2) {
    if (L[i] >= M[j]) {
    arr[k] = L[i];
    i++;
    } else {
    arr[k] = M[j];
    j++;
    }
    k++;
}

while (i < n1) {
    arr[k] = L[i];
    i++;
    k++;
}

while (j < n2) {
    arr[k] = M[j];
    j++;
    k++;
}
}

void mergeSort(int arr[], int l, int r) {
if (l < r) {
    int m = l + (r - l) / 2;

    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);

    merge(arr, l, m, r);
}
}

void GetMinMaxHeight()
{
    int N;
    ll K;
    cin >> N >> K;

    int a[MAXN];
    for(int i = 0; i < N; i++) cin >> a[i];

    mergeSort(a, 0, N-1);

    ll maxh = a[0], minh = 0; //Possible extrema of min_max_height
    ll result = 0, mid = 0;

    while (minh <= maxh) {
        mid = minh + (maxh - minh) / 2;
        ll tc = 0;

        /* The cost required to destroy the floors of buildings till height 'mid' is computed below */
        /* For a particular building of height h, we need the summation h + h-1 + h-2 + ... + mid+1 = Sum(1 to h) - Sum(1 to mid) */

        for (int i = 0; i < N; ++i) {
            ll diff = a[i] - mid;
            if(diff > 0){
                ll costt = (ll)((a[i] + mid + 1) * (a[i] - mid))/2;
                tc += costt;
            }
        }

        /* Applying Binary Search to get the optimal height to fit in cost K */
        
        if (tc <= K) {
            result = mid;
            maxh = mid - 1;  
        } else {
            minh = mid + 1;  
        }
    }
    
    cout << result << "\n";

}


int main(){
    int T;
    cin >> T;

    while(T--) GetMinMaxHeight(); 

    return 0;
}
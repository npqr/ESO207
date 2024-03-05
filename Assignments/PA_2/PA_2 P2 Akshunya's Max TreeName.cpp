/* PA_2 P2 Akshunya's Max Tree */
/* Name : Nevish Pathe */
/* Roll No. 220757*/
/* Handle : npqrrr */

#include <iostream>
#include <vector>

using namespace std;
typedef long long int ll;

/* For getting the index of maximum element in a range */
int findMaxIndex(vector<int>& arr, int start, int end) {
    int maxIndex = start;
    for (int i = start + 1; i <= end; i++) {
        if (arr[i] > arr[maxIndex]) {
            maxIndex = i;
        }
    }
    return maxIndex;
}

/* Find Max Elements and get their depths recursively */
void findMaxRecursive(vector<int>& arr, int start, int end, int depth, vector<int>& depths) {
    if (start > end) {
        return;
    }

    int maxIndex = findMaxIndex(arr, start, end);

    /* Maintaining this to print the depths in the original order*/
    depths[maxIndex] = depth; 

    /* depth + 1 as level increases further */
    /* Dividing the tree/array into two parts excluding current max element */
    findMaxRecursive(arr, start, maxIndex - 1, depth + 1, depths);
    findMaxRecursive(arr, maxIndex + 1, end, depth + 1, depths);
}

void GetDepths() {
    int N, gg;
    cin >> N;

    vector<int> A;
    for(int i = 0; i < N; i++) {cin >> gg; A.push_back(gg);}

    int initialDepth = 0;
    vector<int> depths(N, 0);

    findMaxRecursive(A, 0, N - 1, initialDepth, depths);

    for (int i = 0; i < N; i++) {
        cout << depths[i] << " ";
    }
    cout << "\n";
}


int main(){
    ll T;
    cin >> T;
    
    while(T--) GetDepths();

    return 0;
}
#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
using namespace std;

int n;
int numbers[5000];
vector <int> sumAt (5000,1); //length of subsequence starting at this index

int recur(int loc) {
    int re = 1;

    // LISS starting at this index already found (use it)
    if (sumAt[loc] != 1)
        return sumAt[loc];

    for (int i = loc+1; i < n; i++) {
        if (numbers[i] > numbers[loc])
            re = max(recur(i)+1,re);    // Take this number
    }
    sumAt[loc] = re;
    return re;
}
int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
        scanf("%d", &numbers[i]);

    // Find LISS starting at each number
    for (int i = 0; i < n; i++)
        recur(i);
    cout << *max_element(sumAt.begin(),sumAt.end());
}

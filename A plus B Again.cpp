#include <iostream>
#include <stack>
#include <algorithm>
using namespace std;

// change (s) Takes a number represented by s and turn it
//   into the number that must be added to become 9 (nine-less version)
// requires: s represents a number
// Example: change("123") -> "876"
string change (string s) {
    for (int i = 0; i < s.length(); i++)
        s[i] = 10 - (s[i]-'0'+1) + '0';
    return s;
}

int main() {

    stack <int> r;
    string preA,preB;
    string a,b;
    int s,holder = 0;
    int top;
    bool negA = false, negB = false;
    bool aGreater = false, bGreater = false;

    cin >> preA >> preB;    // input as strings
    a = preA;
    b = preB;

    // Take absolute value of preA and preB
    if (preA[0] == '-') {
        negA = true;
        a = preA.substr(1);
    }
    if (preB[0] == '-') {
        negB = true;
        b = preB.substr(1);
    }

    //Same sign - just add
    if (negA == negB) {

        // Add digits starting with the ones column
        // Chars are turned into ints (- '0')
        for (int i = 1; i <= max(a.length(),b.length()); i++) {
            if (i > a.length())
                s = b[b.length()-i] - '0';
            else if (i > b.length())
                s = a[a.length()-i] - '0';
            else
                s = a[a.length()-i] + b[b.length()-i] - 2*'0';

            // Each final digit is saved in a stack
            if (s+holder >= 10) {       //Placeholder (carry the 1)
                r.push((s+holder)%10);
                holder = 1;
            }
            else {
                r.push(s+holder);
                holder = 0;
            }
        }
    }
    else {
    //Different signs, nine-less greater:
    //The sum of a positive and negative number can be found by adding the nine-less
    //form of the greater number (9 minus each digit of a number for each digit) with the
    //absolute value of the other number, and then turning the sum back
    //e.g. -987 + 3
    //      = 012* + 3 (nineless version of 987; sign ignored)
    //      = 015
    //      = 984*  (nineless version of 015)

        // Determine whether a or b is greater
        if (a.length() > b.length())
            aGreater = true;
        else if (a.length() < b.length())
            bGreater = true;
        else {
            for (int i = 0; i < a.length(); i++) {
                if (a[i] > b[i])
                    aGreater = true;
                else if (a[i] < b[i])
                    bGreater = true;
                if (aGreater || bGreater)
                    break;
            }
            if (aGreater == false && bGreater == false) {
                cout << 0;  // a = -b so sum is 0
                goto done;
            }
        }

        // Take nine-less of greater number
        if (aGreater)
            a = change(a);
        else
            b = change(b);

        // Add digits starting with the ones column
        // Chars are turned into ints (- '0')
        for (int i = 1; i <= max(a.length(),b.length()); i++) {
            if (i > a.length())
                s = b[b.length()-i] - '0';
            else if (i > b.length())
                s = a[a.length()-i] - '0';
            else
                s = a[a.length()-i] + b[b.length()-i] - 2*'0';

            if (s+holder >= 10) {
                r.push(10-((s+holder)%10+1)); //Change back from nine-less
                holder = 1;
            }
            else {
                r.push(10-(s+holder+1));    //Change back from nine-less
                holder = 0;
            }
        }
    }

    // Determine if a negative sign is needed
    if (negA && negB || (aGreater)&&(negA) || (bGreater)&&(negB))
        cout << '-';

    if (holder > 0)
        r.push(holder);

    top = r.top();
    // Get rid of leading ones
    while (top == 0) {
        r.pop();

        if (r.empty()) {
            cout << 0;  //Answer was 0
            break;
        }
        top = r.top();
    }

    done:;
    // Output answer (was saved in stack)
    while (!r.empty()) {
        cout << r.top();
        r.pop();
    }

}

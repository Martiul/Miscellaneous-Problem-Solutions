#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

vector <vector <int> > v(100001);  // Adjacency list
vector <int> country_sizes;    // Number of people in the index-th country
int prefix[100001];      // Prefix sum to calculate number of combinations
bool d[100001];          // Astronaut's country has been determined

int main()
{
    int n,lines,a,b;

    int people;
    int total_people = 0;
    int cur_country = 0;
    int cur, next;
    queue <int> q;

    cin >> n >> lines;

    // Input
    for (int i = 0; i < lines; i++) {
        scanf("%d%d",&a,&b);
        v[a].push_back(b);
        v[b].push_back(a);
    }

    // Start DFS with each astronaut
    for (int i = 0; i < n; i++) {
        if (d[i])
            continue;

        q.push(i);
        d[i] = true;
        people = 1;

        while (!q.empty()) {

            cur = q.front();
            q.pop();

            // Go to each astronaut known to be of the same country
            for (int j = 0; j < v[cur].size(); j++) {
                next = v[cur][j];
                if (!d[next]) {
                    people++;
                    q.push(next);
                    d[next] = true;
                }
            }
        }
        country_sizes.push_back(people); //Num people for this country

        // Update prefix sum array
        if (cur_country == 0)
            prefix[cur_country] = people;
        else
            prefix[cur_country] = prefix[cur_country-1] + people;

        cur_country++;
    }


    long long output = 0;
    for (int i = 0; i < country_sizes.size(); i++)
        output += country_sizes[i] * (n-prefix[i]);

    //if (n == 1)
   //     cout << 0 << endl;
   // else
        cout << output;

}

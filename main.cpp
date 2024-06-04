#include <bits/stdc++.h>
#include "constructible.h"
#include "fraction.h"

using namespace std;
// vieta's formula
// aka the quadratic formula but fancy
pair<constructible, constructible> vieta(constructible sum, constructible prod)
{
    constructible res1, res2;
    res1 = (sum + sqrt(sum*sum - prod*fraction(4, 1))) * fraction(1, 2);
    res2 = (sum - sqrt(sum*sum - prod*fraction(4, 1))) * fraction(1, 2);
    return {res1, res2};
}
const int n = 4;
int a[1<<n]; //3^i mod 2^n+1
constructible c[n][1<<n];
set<int> s[n][1<<n];
map<set<int>, pair<int, int> > mp;
void construct_set(int i, int msk)
{
    for(int j = 0; j < (1<<n); j++)
    {
        if((j&((1<<i)-1)) == msk)
        {
            s[i][msk].insert(a[j]);
        }
    }
    mp[s[i][msk]] = {i, msk};
}
int main()
{
    // too lazy to explain how this thing works but it's slow as shit
    // and i'm gonna redo the whole thing anyway
    // works for 17 but would take too long for 65537
    a[0] = 1;
    s[0][0].insert(1);
    for(int i = 1; i < (1<<n); i++)
    {
        a[i] = (a[i-1]*3)%((1<<n)+1);
        s[0][0].insert(a[i]);
    }
    c[0][0] = constructible(fraction(-1, 1));
    for(int i = 1; i < n; i++)
    {
        for(int msk = 0; msk < (1<<i); msk++)
        {
            for(int j = 0; j < (1<<n); j++)
            {
                if((j&((1<<i)-1)) == msk)
                {
                    s[i][msk].insert(a[j]);
                }
            }
            mp[s[i][msk]] = {i, msk};
        }
    }
    for(int i = 0; i < n-1; i++)
    {
        for(int msk = 0; msk < (1<<i); msk++)
        {
            set<int> st;
            for(auto j: s[i+1][msk])
            {
                for(auto k: s[i+1][msk+(1<<(i))])
                {
                    st.insert((j+k)%((1<<n)+1));
                }
            }
            pair<int, int> p = mp[st];
            pair<constructible, constructible> pp = vieta(c[i][msk], c[p.first][p.second]*fraction(s[i+1][msk].size()*s[i+1][msk+(1<<(i))].size(), st.size()));
            //160 characters wide!!!
            c[i+1][msk] = pp.first;
            c[i+1][msk+(1<<(i))] = pp.second;
        }
    }
    cout << c[n-1][0] * fraction(1, 2) << endl;
    cout << fixed << setprecision(50);
    cout << "MY VALUE:     " << (c[n-1][0] * fraction(1, 2)).eval() << endl;
    cout << "ACTUAL VALUE: " << cos(acos(-1)*2.0/17.0) << endl;
    return 0;
}
